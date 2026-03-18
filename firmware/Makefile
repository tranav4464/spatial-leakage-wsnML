# Makefile for Compiled Size Benchmarking
# Compiles to object files to measure actual machine code footprint.
# Use `size` to read .text section (not raw .o file size).
#
# Supports BOTH x86-64 (native) and ARM Cortex-M (cross-compilation).
# ARM is the PRIMARY target for publication metrics.

# === ARM Cortex-M3 Cross-Compilation (PRIMARY — for publication) ===
ARM_CC = /c/msys64/mingw64/bin/arm-none-eabi-gcc.exe
ARM_SIZE = /c/msys64/mingw64/bin/arm-none-eabi-size.exe
ARM_CFLAGS = -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -Os -Wall -ffreestanding -nostdlib -c

# === x86-64 Native Compilation (SECONDARY — for local testing/timing) ===
X86_CC = gcc
X86_SIZE = size
X86_CFLAGS = -Os -Wall -I. -c

# Targets
CART_DEPTHS = 2 3 4 5 6 8 10
CART_SRCS = $(foreach d,$(CART_DEPTHS),$(wildcard cart_depth$(d)/main.c))

ALL_SRCS = $(wildcard xgboost_full/main.c) $(wildcard ale_rule/main.c) \
           $(wildcard linreg/main.c) $(CART_SRCS)

ARM_OBJS = $(ALL_SRCS:.c=.arm.o)
X86_OBJS = $(ALL_SRCS:.c=.o)

# Default: build ARM (publication target)
all: arm

arm: $(ARM_OBJS) arm-size

x86: $(X86_OBJS) x86-size

# ARM compilation rules
%.arm.o: %.c
	$(ARM_CC) $(ARM_CFLAGS) -o $@ $<

# x86 compilation rules
%.o: %.c
	$(X86_CC) $(X86_CFLAGS) -o $@ $<

arm-size: $(ARM_OBJS)
	@echo "=== ARM Cortex-M3 Compiled Binary Footprints ==="
	@echo "Compiler: arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -Os"
	@echo ""
	@for f in $^; do \
		echo "$$f:"; \
		$(ARM_SIZE) $$f; \
		echo ""; \
	done

x86-size: $(X86_OBJS)
	@echo "=== x86-64 Compiled Binary Footprints ==="
	@for f in $^; do \
		echo "$$f:"; \
		$(X86_SIZE) $$f; \
		echo ""; \
	done

clean:
	find . -name "*.o" -delete
	find . -name "*.arm.o" -delete
