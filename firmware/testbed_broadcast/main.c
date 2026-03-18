#include <stdio.h>
#include <string.h>
#include "msg.h"
#include "thread.h"
#include "xtimer.h"
#include "net/gnrc.h"
#include "net/gnrc/netif.h"
#include "net/gnrc/pktbuf.h"
#include "net/gnrc/netreg.h"
#include "net/gnrc/netapi.h"

#define TX_INTERVAL     (500000U)
#define MSG_QUEUE_SIZE  (16)

static msg_t _rx_msg_queue[MSG_QUEUE_SIZE];

/* Large stack to avoid HARD FAULT from GNRC + printf */
static char rx_stack[THREAD_STACKSIZE_MAIN + THREAD_EXTRA_STACKSIZE_PRINTF + 512];

static void *_rx_thread(void *arg)
{
    (void)arg;
    msg_init_queue(_rx_msg_queue, MSG_QUEUE_SIZE);

    gnrc_netreg_entry_t server;
    server.demux_ctx = GNRC_NETREG_DEMUX_CTX_ALL;
    server.target.pid = thread_getpid();
    gnrc_netreg_register(GNRC_NETTYPE_UNDEF, &server);

    while (1) {
        msg_t msg;
        msg_receive(&msg);

        if (msg.type != GNRC_NETAPI_MSG_TYPE_RCV) {
            continue;
        }

        gnrc_pktsnip_t *pkt = msg.content.ptr;

        /* Extract RSSI/LQI from netif header */
        gnrc_pktsnip_t *netif_hdr = gnrc_pktsnip_search_type(pkt, GNRC_NETTYPE_NETIF);
        int16_t rssi = 0;
        uint8_t lqi = 0;
        if (netif_hdr) {
            gnrc_netif_hdr_t *hdr = netif_hdr->data;
            rssi = hdr->rssi;
            lqi = hdr->lqi;
        }

        /* Search all snips for payload containing "LQE:" */
        gnrc_pktsnip_t *s = pkt;
        while (s) {
            if (s->type != GNRC_NETTYPE_NETIF && s->size > 4) {
                char buf[64];
                size_t len = s->size < 63 ? s->size : 63;
                memcpy(buf, s->data, len);
                buf[len] = '\0';
                if (strncmp(buf, "LQE:", 4) == 0) {
                    printf("RX;%s;%d;%u\n", buf, rssi, lqi);
                    break;
                }
            }
            s = s->next;
        }

        gnrc_pktbuf_release(pkt);
    }
    return NULL;
}

int main(void)
{
    gnrc_netif_t *netif = gnrc_netif_iter(NULL);
    if (!netif) {
        puts("ERROR: no network interface found");
        return 1;
    }

    uint16_t channel = 11;
    gnrc_netapi_set(netif->pid, NETOPT_CHANNEL, 0, &channel, sizeof(channel));

    uint16_t pan_id = 0x0023;
    gnrc_netapi_set(netif->pid, NETOPT_NID, 0, &pan_id, sizeof(pan_id));

    uint16_t src_addr = 0;
    gnrc_netapi_get(netif->pid, NETOPT_ADDRESS, 0, &src_addr, sizeof(src_addr));

    printf("LQE node: addr=0x%04x ch=%u\n", src_addr, channel);

    /* Start receiver thread with large stack */
    thread_create(rx_stack, sizeof(rx_stack), THREAD_PRIORITY_MAIN - 1,
                  THREAD_CREATE_STACKTEST, _rx_thread, NULL, "rx_thread");

    uint32_t seq = 0;
    xtimer_ticks32_t last_wakeup = xtimer_now();

    while (1) {
        char payload[64];
        int len = snprintf(payload, sizeof(payload), "LQE:%04X:%08lu",
                          src_addr, (unsigned long)seq++);

        gnrc_pktsnip_t *pkt = gnrc_pktbuf_add(NULL, payload, len, GNRC_NETTYPE_UNDEF);
        if (pkt) {
            uint8_t dest[2] = {0xff, 0xff};
            gnrc_pktsnip_t *hdr = gnrc_netif_hdr_build(NULL, 0, dest, 2);
            if (hdr) {
                gnrc_netif_hdr_set_netif(hdr->data, netif);
                ((gnrc_netif_hdr_t *)hdr->data)->flags |= GNRC_NETIF_HDR_FLAGS_BROADCAST;
                pkt = gnrc_pkt_prepend(pkt, hdr);
                if (gnrc_netapi_send(netif->pid, pkt) < 1) {
                    gnrc_pktbuf_release(pkt);
                }
            } else {
                gnrc_pktbuf_release(pkt);
            }
        }

        if (seq % 10 == 0) {
            printf("TX;LQE:%04X:%08lu\n", src_addr, (unsigned long)(seq - 1));
        }

        xtimer_periodic_wakeup(&last_wakeup, TX_INTERVAL);
    }
    return 0;
}
