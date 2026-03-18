# Preventing Spatial Leakage in WSN ML: A Rigorous Evaluation of Decision Trees, Knowledge Distillation, and ALE-based Surrogate Rules

[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)

This repository contains the complete reproducible pipeline, generated datasets, cross-compiled firmware artifacts, and numerical benchmarks for our manuscript investigating the fundamental architectural constraints of applying Machine Learning to Link Quality Estimation (LQE) in Wireless Sensor Networks (WSNs). This document serves as an exhaustive, paper-grade technical companion to the repository. It details every mathematical assumption, validation methodology, and computational artifact generated within this project.

---

## 1. Introduction & Core Problem Statement

The deployment of low-power Wireless Sensor Networks (WSNs) is heavily reliant on accurate, energy-efficient routing decisions. The fundamental building block of wireless routing is **Link Quality Estimation (LQE)**—the ability for a sensor node to predict whether a packet sent to a neighboring node will be successfully received. In standard IPv6 Routing Protocol for Low-Power and Lossy Networks (RPL), metrics such as the Expected Transmission Count (ETX) are derived directly from the underlying Packet Reception Rate (PRR). If a node incorrectly estimates the PRR of a link, it may choose a routing path that forces numerous retransmissions, leading to rapid energy depletion, increased MAC-layer contention, and ultimately, network partition.

In the 2.4 GHz Industrial, Scientific, and Medical (ISM) radio band, particularly within the IEEE 802.15.4 physical and MAC protocol layers utilized by Zigbee and Thread, the relationship between physical metrics (such as the Received Signal Strength Indicator - RSSI, or the Signal-to-Noise Ratio - SNR) and the PRR is highly non-linear. The defining characteristic of this environment is the "Transitional Region." Unlike wired networks or ideal theoretical models where communication is either perfectly reliable or completely severed, the transitional region is a stochastic zone where minor, almost imperceptible fluctuations in signal strength, background thermal noise, or MAC-layer hidden-terminal contention cause massive, unpredictable drops in packet delivery success. Consequently, simple threshold-based LQE heuristics (e.g., "if RSSI is greater than -85 dBm, the link is good") are incredibly inaccurate and fragile.

### The TinyML Paradox in LQE Research

To combat the unpredictability of the transitional region, researchers have increasingly turned to Machine Learning (ML). By feeding multi-dimensional feature sets (RSSI, SNR, local node density, remaining battery capacity) into complex algorithms, ML models can achieve near-perfect predictive accuracy. However, this has led to a pervasive methodological paradox in the academic literature, consisting of three major flaws:

1. **The Deployment Constraint Reality:** Standard WSN microcontrollers, such as the Texas Instruments MSP430, CC2538, or the Nordic Semiconductor nRF52 series, possess limited onboard resources. While an nRF52840 may have 1 MB of Flash, older platforms like the MSP430 may have as little as 32 KB. Crucially, a vast majority of this memory is statically allocated to the embedded Operating System (e.g., RIOT, Contiki-NG) and complex IPv6/6LoWPAN network stacks, leaving a constrained application budget—often ranging from 200 KB down to just a few kilobytes—for any deployed ML model.
2. **The Algorithmic Overhead:** Despite these physical constraints, networking literature frequently proposes massive ensemble models (such as Random Forests or Deep Neural Networks) to solve the LQE problem. These models can require hundreds of kilobytes of memory to store their decision boundaries and floating-point weights, rendering them difficult or impossible to deploy on constrained edge hardware. Compounding the issue, Python-level `sys.getsizeof()` metrics are often cited, which completely fail to represent actual compiled machine-code sizes.
3. **The Spatial Leakage Bias:** Compounding the memory issue is a methodological flaw in how models are evaluated. Literature evaluating LQE on static testbeds often reports highly optimistic predictive performance. This hyper-accuracy can be an artifact of utilizing naive K-Fold cross-validation on spatially correlated datasets. When static nodes transmit to one another, the multi-path fading and shadowing of that specific geographic link remain constant. Naive K-Fold mixes data from the same physical links into both the training and testing sets. The model risks "memorizing" the specific geographic topology of the testbed rather than learning the generalized physics of RF propagation, leading to degraded performance when deployed to novel physical topologies.

### Our Contributions

This repository serves to empirically investigate these paradoxes by establishing Pareto frontiers of accuracy versus compiled `.text` flash memory footprint in both simulation and physical testbed environments. We provide:
* A high-fidelity physical IEEE 802.15.4 simulation that enforces strict `GroupKFold` spatial-leakage prevention, guaranteeing that evaluation metrics reflect true physical generalization rather than spatial memorization.
* **A rigorous "Sim2Real" physical validation**, deploying custom C-based firmware to the FIT IoT-LAB testbed (M3 nodes running RIOT OS) to validate our simulation claims against actual 2.4 GHz physical constraints and hardware footprint measurements.
* A systematic, bare-metal benchmark of ML compression techniques, including directly grown shallow Decision Trees, Knowledge Distillation (KD) methodologies, and Accumulated Local Effects (ALE) based surrogate rules.
* Evidence that **shallow CART decision trees (Depths 4-6) are Pareto-optimal in simulation** for TinyML LQE (R²=0.767, 1,492 bytes), while complex distillation techniques and ALE surrogate rules fail to capture physical non-linearities. **Sim2Real validation on FIT IoT-LAB** reveals the Pareto elbow shifts to Depth 2-3 with reduced features, and dramatic spatial leakage inflation (XGBoost: 358% on testbed vs 1.4% in simulation). Traditional baselines (RSSI-binned, WMEWMA-like) are competitive on real hardware, confirming ML advantage is modest outside simulation.

---

## 2. Methodology: Dataset Generation & Physics Simulation

A central challenge in LQE machine learning research is the acquisition of clean, fully-featured, and large-scale datasets. While physical testbeds (such as FIT IoT-LAB or FlockLab) are invaluable for final validation, they are incredibly difficult to control. Physical testbeds suffer from unrepeatable environmental interference, undocumented node failures, and most importantly, an inability to accurately record ground-truth continuous values for variables like concurrent hidden-terminal collisions and precise, synchronous battery discharge rates across thousands of nodes.

Instead of relying solely on a static, spatially leaked physical testbed dataset for our primary architectural search, we engineered a mathematically pure, high-fidelity dataset grounded in established RF propagation theory and IEEE 802.15.4 specifications. The pipeline for this generation is fully encapsulated within `src/simulation/wsn_simulation.py`.

### 2.1 The Zuniga-Krishnamachari Physical Layer Model

At the core of our physical layer simulation is the seminal Zuniga-Krishnamachari theoretical model. This model mathematically bridges the gap between raw RF signal strength and the resulting Packet Reception Rate (PRR) by explicitly analyzing the modulation and encoding scheme used by the radio hardware. IEEE 802.15.4-compliant radios operating in the 2.4 GHz band utilize Offset Quadrature Phase-Shift Keying (O-QPSK) combined with Direct Sequence Spread Spectrum (DSSS).

The simulation computes the Signal-to-Noise Ratio (SNR) by calculating the difference between the Received Signal Strength Indicator (RSSI) and the environmental Noise Floor. Using the Zuniga-Krishnamachari derivation for O-QPSK/DSSS, we calculate the exact theoretical Bit Error Rate (BER) for a given SNR. The mathematical representation implemented in our code utilizes the complementary error function (`erfc`) to determine the bit-level failure probability:

```python
# O-QPSK/DSSS BER Calculation based on Zuniga-Krishnamachari
# Note: 8.0 represents the DSSS processing gain (chip rate 2 Mcps / data rate 250 kbps) for 802.15.4
ber = 0.5 * erfc(np.sqrt(8.0 * (10 ** (snr_db / 10))))

# Packet Reception Rate for a standard 127-byte 802.15.4 payload
prr_base = (1 - ber) ** (8 * 127)
```
This baseline PRR curve perfectly recreates the infamous "Transitional Region." When the SNR is high (e.g., > 5 dB), the BER is near zero, and PRR is 1.0. When SNR drops below -5 dB, the BER spikes, and PRR crashes to 0.0. However, in the narrow band between roughly -4 dB and +2 dB, the `erfc` function produces a sharp, non-linear cascade where PRR values are wildly distributed between 0.1 and 0.9.

### 2.2 MAC-Layer Contention & Hidden Terminals

RF energy alone does not govern link quality. In real-world dense sensor networks, packet loss is frequently caused by collisions at the Medium Access Control (MAC) layer rather than thermal noise. The IEEE 802.15.4 protocol uses Carrier Sense Multiple Access with Collision Avoidance (CSMA/CA). Before transmitting, a node "listens" to the channel to ensure it is clear.

However, the "Hidden Terminal Problem" plagues this mechanism. If Node A and Node C are both out of range of each other, but both are within range of Node B, they cannot hear each other's carrier sense. They may transmit to Node B simultaneously, causing a destructive collision. To model this, our simulation script generates precise 2D coordinates for all nodes. For every transmitting node, we calculate a `Local_Density` metric—the number of active, transmitting nodes within its physical interference range.

As the `Local_Density` increases, the simulation applies a probabilistic penalty proxy to the `prr_base` derived from the Zuniga-Krishnamachari model (approximating an unslotted CSMA collision profile). This transforms the purely physical, 1-dimensional SNR-to-PRR curve into a complex, multi-dimensional surface. While an explicit simulation artifact, this forces models to evaluate conditions where an otherwise perfect RF link (high SNR) experiences severe packet loss purely due to network density.

### 2.3 Environmental Modeling & Feature Space

To ensure robust generalization, the pipeline simulates 675 distinct network configurations. Each configuration varies critical parameters: node densities (ranging from sparse 20-node deployments to ultra-dense 150-node clusters), base noise floors, transmitter power variations, and multi-path fading indices (log-normal shadowing variance). Furthermore, the simulation tracks a linear discharge of battery energy, allowing models to learn if low residual energy correlates with transmission failure.

The engine generates over 4 million transmission records. We then filter out nodes that have depleted their energy reserves, resulting in a spatially diverse, robust dataset of 150,000 links. Each record is characterized by 8 precisely calculated features:
1. `Transmission_Power_dBm`: The physical transmit power of the sender.
2. `Distance_to_Sink_m`: The Euclidean distance between sender and receiver.
3. `Local_Density`: The number of concurrent transmitters in the vicinity.
4. `Signal_Strength_RSSI_dBm`: The received signal strength at the receiver.
5. `Noise_Level_dBm`: The localized thermal and background noise.
6. `SNR_dB`: The differential between RSSI and Noise.
7. `Initial_Energy_J`: The battery state at deployment.
8. `Residual_Energy_J`: The battery state at the time of transmission.

*(Note: Features 7 and 8 represent perfectly continuous energy states. In physical deployments, battery state estimation is notoriously noisy and platform-specific, representing an idealized feature space in this context).*

This high-fidelity simulated dataset provides the mathematical foundation required to evaluate ML compression techniques, with the caveat that features like density penalties and energy states are mathematical proxies rather than empirical measurements.

### 2.4 Physical Validation (Sim2Real on FIT IoT-LAB)

While simulation provides a clean mathematical baseline, proving deployment viability requires a transition to physical hardware. Our architecture incorporates a "Sim2Real" validation phase utilizing the **FIT IoT-LAB** platform (specifically the Grenoble site, using ARM Cortex-M3 nodes).

We deployed custom C-based firmware (`firmware/testbed_broadcast/main.c`) utilizing the **RIOT OS 2024.04** and its GNRC network stack to create a real-world 50-node testbed environment operating over IEEE 802.15.4 on channel 11 at the Grenoble site. The firmware implements a broadcast/listen architecture: each node transmits an LQE beacon every 500ms containing its 16-bit short address and sequence number, while simultaneously receiving beacons from all neighbors and reporting RSSI and LQI via serial output.

The experiment lifecycle is fully automated via SSH. Two pipeline entry points exist: `scripts/run_full_experiment.py` (end-to-end: compile, submit, capture serial data, parse, and run ML validation) and `scripts/run_real_testbed.py` (configurable via `--nodes` and `--duration` arguments).

The data acquisition layer (`src/data/fetch_testbed.py` and `src/data/process_testbed.py`) bridges the gap between raw testbed traces and the ML feature space. It queries the IoT-LAB REST API for exact 3D node coordinates, computing accurate Euclidean distances. `Local_Density` is reconstructed via spatial analysis using an empirically determined interference radius ($R_{int} = 2 \times R_{tx}$, where $R_{tx}$ is the distance at which PRR drops below 10%). The resulting 4-feature testbed dataset (Distance_m, RSSI_mean, LQI_mean, Local_Density → PRR) is evaluated using the same GroupKFold protocol as the simulation, grouped by receiver node to prevent spatial leakage.

---

## 3. The Spatial Leakage Bias in Evaluation

A core methodological focus of this manuscript is identifying and mitigating the impact of **Spatial Leakage** in the evaluation of Machine Learning models for wireless networks. Spatial leakage is a form of data leakage where geographic information from the testing set is inadvertently present in the training set, leading to falsely optimistic performance metrics. In the context of WSNs, this leakage occurs geographically.

When researchers aggregate packet transmission data from a wireless testbed (or a simulation), the dataset is composed of distinct, static physical links (e.g., Node 1 transmitting to Node 5). Because the nodes are immobile, the specific physical environment between them—the walls, the trees, the exact distance, the specific multi-path fading profile—remains constant across thousands of packet transmissions.

### The Failure of Naive K-Fold

Standard machine learning evaluation relies on `KFold` cross-validation with random shuffling (`KFold(shuffle=True)`). If a dataset contains 10,000 packets transmitted over the Node 1 $\rightarrow$ Node 5 link, a random shuffle will place roughly 8,000 of those packets in the training set and 2,000 in the testing set.

During training, a high-capacity model (like a Random Forest or XGBoost) will simply "memorize" the specific feature signatures (e.g., the exact Distance and average RSSI) of the Node 1 $\rightarrow$ Node 5 link. When the model evaluates the test set, it recognizes the signature and outputs the memorized average PRR for that specific link. The model achieves a high $R^2$ score on the validation set, but it may have partially learned a lookup table of the testbed's specific geometry rather than the generalized physics of RF propagation. When this trained model is flashed onto a node and deployed in a brand new environment—say, a smart agriculture field or a factory floor—it encounters novel distances and shadowing profiles. If overly reliant on spatial features, the model's accuracy is likely to degrade significantly.

### The GroupKFold Solution and Empirical Proof

To completely eradicate this issue, our pipeline strictly enforces **Group-based Cross-Validation** (`GroupKFold`). In our implementation (`src/modeling/spatial_leakage_comparison.py`), we utilize the `Config_ID` feature as the grouping key. `Config_ID` represents an entirely distinct network deployment with newly randomized node coordinates, noise floors, and densities. This methodology is not just theoretical; it is also rigorously applied when evaluating models against our physical FIT IoT-LAB testbed data (`src/modeling/testbed_validation.py`), grouping by Receiver Node to guarantee the model has not memorized the physical geometry of the testbed.

During a 5-Fold `GroupKFold` split, the data from an entire physical configuration is held out in the testing set. The model is forced to train on Topologies A, B, C, and D, and then predict the link qualities of Topology E—a spatial environment it has never seen before.

We ran a dedicated experiment to quantify the exact magnitude of this artifact inflation. We trained XGBoost, Depth-4 CART, Depth-6 CART, and Linear Regression models under both evaluation schemes and extracted the difference in the coefficient of determination ($R^2$).

### Spatial Leakage Results

| Architecture | Naive `KFold` $R^2$ (Leaked) | `GroupKFold` $R^2$ (Rigorous) | Artifact Inflation ($\Delta$) |
| :--- | :--- | :--- | :--- |
| **XGBoost (150 trees)** | 0.8088 | 0.7978 | **+ 0.0110** |
| **CART (Depth 4)** | 0.6464 | 0.6279 | **+ 0.0185** |
| **CART (Depth 6)** | 0.7778 | 0.7671 | **+ 0.0107** |
| **Linear Regression** | 0.1896 | 0.1845 | **+ 0.0051** |

*Simulation Conclusion:* In simulation, the leakage inflation is modest (1-2% $R^2$), falling within the standard deviation of cross-validation folds ($\pm 0.05$). While representing a consistent methodological bias, this magnitude alone does not constitute a crisis.

*Testbed Conclusion (Headline Finding):* On physical hardware, the picture changes dramatically. Testbed spatial leakage inflation is **358% for XGBoost** (naive $R^2$ = 0.363 vs GroupKFold $R^2$ = 0.079), **161% for CART d6** (0.181 vs 0.070), and only **5% for Linear Regression** (0.112 vs 0.107). The severity scales with model capacity—high-capacity models exploit spatial correlations far more aggressively on real data than in simulation. This establishes testbed-based spatial leakage prevention as a critical requirement for WSN evaluation, not merely a methodological nicety.

---

## 4. Benchmarking the Pareto Frontier

The ultimate goal of TinyML is to deploy predictive intelligence directly onto the edge node. However, comparing the deployment viability of ML architectures is notoriously difficult. Many papers report the file size of the serialized Python model (e.g., a `.pkl` or `.h5` file) or utilize Python's `sys.getsizeof()` function. These metrics are entirely detached from reality. A microcontroller does not run Python; it executes bare-metal, compiled machine code. Furthermore, standard x86-64 compilation metrics are irrelevant because they include 64-bit instruction padding and complex OS-level dynamic linking overheads that do not exist on a Cortex-M3 microcontroller.

To define a rigorous, undeniable Pareto frontier of predictive accuracy against memory constraints, we implemented a strict transpilation and bare-metal ARM cross-compilation pipeline (managed by `scripts/benchmark_size.py`).

### 4.1 Bare-Metal C Transpilation

The first step in our hardware evaluation is converting the trained scikit-learn and XGBoost models into dependency-free C code. We utilize the `m2cgen` (Model 2 C Generator) library to translate the complex tree structures and ensemble weights into thousands of lines of raw, nested `if-else` statements and floating-point arithmetic.

**Critical Adjustments for Embedded Compatibility:**
* **`NaN` Macro Resolution:** Tree ensembles frequently output `nan` (Not a Number) representations for missing data branches. During transpilation, we utilize robust regular expressions (`re.sub(r'\bnan\b', 'NAN', xgb_c_code)`) to map Python's `nan` to the strict `math.h` compliant `NAN` macro, preventing fatal compiler errors during the firmware build step.
* **Double-to-Float Emulation Penalties:** By default, XGBoost and scikit-learn operate using 64-bit `double` precision floating-point numbers, and `m2cgen` transpiles them as such. However, standard WSN microcontrollers (like the ARM Cortex-M3F) possess only Single-Precision Floating-Point Units (FPUs). If a program requires 64-bit `double` math, the ARM compiler must link massive software-emulation libraries, artificially bloating the ROM size by kilobytes and drastically increasing CPU execution cycles. To ensure a fair comparison against simpler integer-based rules, we run a rigorous regex pass replacing all `double` declarations with `float`.

### 4.2 ARM Cortex-M3 Cross-Compilation Metrics

Once the pure `main.c` files are generated, we invoke the GNU ARM Embedded Toolchain (`arm-none-eabi-gcc`). We compile the models using flags that mimic a production-grade embedded OS build:
`ARM_CFLAGS = ['-mcpu=cortex-m3', '-mthumb', '-mfloat-abi=soft', '-Os', '-Wall', '-ffreestanding', '-nostdlib', '-c']`

Crucially, the `-Os` flag optimizes for minimum size, while `-ffreestanding` and `-nostdlib` strip out standard C library overhead. The choice of `-mfloat-abi=soft` explicitly enforces software floating-point emulation. While the Cortex-M3F features a hardware FPU, many legacy WSN platforms do not. This flag penalizes models heavily reliant on floating-point arithmetic (like XGBoost) compared to integer-heavy decision trees, simulating a rigorous lowest-common-denominator deployment scenario. We then execute the GNU `size` utility to precisely extract:
* **`.text` size:** The compiled, executable machine code and constant data. This represents the immutable **Flash/ROM** footprint required.
* **`.bss` and `.data` size:** Uninitialized and initialized global variables. This represents the volatile **SRAM** required during execution.

### 4.3 The Pareto Optimal Discoveries

We performed an exhaustive sweep of CART decision trees at various depths, alongside linear regression baselines and a massive 150-estimator XGBoost model.

| Architecture | ARM Flash (`.text`) | ARM SRAM (`.bss`) | $R^2$ Score (5-Fold GKF) | RMSE Mean |
| :--- | :--- | :--- | :--- | :--- |
| **XGBoost (150 trees)** | 237,700 bytes | 4 bytes | 0.7978 ± 0.0422 | 0.0173 |
| **CART (Depth 10)** | 18,552 bytes | 4 bytes | 0.7587 ± 0.0574 | - |
| **CART (Depth 8)** | 5,832 bytes | 4 bytes | 0.7838 ± 0.0481 | - |
| **CART (Depth 6) [Optimal]** | **1,492 bytes** | **4 bytes** | **0.7671 ± 0.0545** | **0.0185** |
| **CART (Depth 5)** | 764 bytes | 4 bytes | 0.7158 ± 0.0639 | - |
| **CART (Depth 4)** | 412 bytes | 4 bytes | 0.6279 ± 0.0836 | 0.0234 |
| **Linear Regression** | 292 bytes | 4 bytes | 0.1845 ± 0.0251 | 0.0351 |

**Analysis (Simulation):** The data maps a clear Pareto frontier in simulation. The "Teacher" XGBoost model achieves the highest accuracy ($R^2 = 0.7978$) but requires an impractical 237 KB of flash memory. A Depth 6 CART decision tree yields an $R^2$ of 0.7671 (an absolute gap of $\Delta R^2 = 0.0307$, which falls within the cross-fold standard deviation) while utilizing only **1,492 bytes**. This is a reduction in memory footprint of over 99.3%.

If a slightly larger flash memory budget is available (e.g., > 6 KB), Depth 8 is strictly better functionally, achieving an $R^2$ of 0.7838 at 5,832 bytes. However, pushing the CART model beyond Depth 8 is counter-productive. Strikingly, a Depth 10 tree balloons to 18.5 KB, but its accuracy drops to 0.7587, indicating severe overfitting to the training topology. Thus, extreme memory constraints naturally act as a powerful regularizer. In simulation, directly-grown CART trees restricted to Depth 6 or 8 represent the Pareto-optimal architecture for TinyML LQE.

**Sim2Real Gap (Testbed):** Physical validation on 50-node FIT IoT-LAB (56,485 link records, 4 features: Distance, RSSI, LQI, Local_Density) reveals a significant sim-to-real gap. All models achieve much lower R² on testbed data. The Pareto-optimal depth shifts from d6 to d2-d3.

| Architecture | ARM Flash (`.text`) | Testbed $R^2$ (5-Fold GKF) | Simulation $R^2$ | Sim/Real Ratio |
| :--- | :--- | :--- | :--- | :--- |
| **XGBoost (150 trees)** | 237,700 bytes | 0.0793 ± 0.0253 | 0.7978 | 10.1x |
| **CART (Depth 3) [Testbed Optimal]** | **220 bytes** | **0.1198 ± 0.0154** | — | — |
| **CART (Depth 2)** | **132 bytes** | **0.1161 ± 0.0153** | — | — |
| **CART (Depth 6) [Sim Optimal]** | 1,484 bytes | 0.0696 ± 0.0426 | 0.7671 | 11.0x |
| **Linear Regression** | 292 bytes | 0.1068 ± 0.0194 | 0.1845 | 1.7x |
| **RSSI-Binned (ETX-like)** | ~200 bytes | 0.1071 ± 0.0106 | — | — |
| **WMEWMA-like** | ~300 bytes | 0.1056 ± 0.0173 | — | — |
| **ALE Rule** | 396 bytes | 0.1003 ± 0.0202 | 0.1437 | 1.4x |
| **Mean Baseline** | — | -0.0039 | 0.0 | — |

Traditional LQE baselines (RSSI-binned: R²=0.107, WMEWMA-like: R²=0.106) are competitive with ML models on real hardware, suggesting the ML advantage seen in simulation may be partially attributable to the simulator's controlled feature space. Critically, spatial leakage inflation is 358% for XGBoost on testbed (naive R²=0.363 vs grouped R²=0.079), far exceeding the 1.4% seen in simulation — confirming that GroupKFold enforcement is essential for real-world WSN evaluation.

---

## 5. The Limitations of Additive Surrogate Rules

In the quest to compress complex black-box AI models for edge deployment, the field of Explainable AI (XAI) has heavily promoted the extraction of "Surrogate Rules." The theory suggests that by analyzing the predictions of a massive ensemble (like XGBoost), we can extract human-readable, piecewise-linear rules that describe the model's behavior. These rules can then be compiled into ultra-lightweight `if-else` blocks for the microcontroller, theoretically offering the best of both worlds: the accuracy of an ensemble and the footprint of a heuristic.

We explicitly tested this methodology within our pipeline (`src/modeling/fair_ale_comparison.py`).

### 5.1 Accumulated Local Effects (ALE) Extraction

We utilized **Accumulated Local Effects (ALE)**, a state-of-the-art XAI technique that calculates the main effect of individual features while robustly handling feature correlations (unlike Partial Dependence Plots, which assume independence). We analyzed the 150-tree XGBoost model to extract 1D ALE arrays for the two most critical features: `SNR_dB` and `Local_Density`.

The ALE algorithms yielded incredibly logical, physically sound rules:
* It identified a strict SNR transitional zone: if SNR is below -4.75 dB, the ALE effect plummets. Above +1.25 dB, the effect plateaus to a maximum.
* It generated a 5-point Look-Up Table (LUT) for node density, proving that as MAC-layer contention increases past 37 concurrent nodes, the likelihood of packet reception drops sharply.

We combined these two 1D ALE rules using Ordinary Least Squares (OLS) to create a linearly additive surrogate model and transpiled it to C code (`firmware/ale_rule/main.c`).

### 5.2 The Benchmarking Shortfall

* **ALE Firmware Footprint:** An incredibly tiny **396 bytes** of `.text` on the Cortex-M3.
* **ALE Predictive Accuracy:** An **$R^2$ of 0.1437**.

The 2-feature ALE surrogate rule performed slightly worse than a rudimentary Linear Regression model ($R^2 = 0.1845$). Why did this XAI technique fail to capture the environment's complexity?

The answer lies in the fundamental physics of the wireless channel. RF link quality is dictated by severe non-linear **interactions** between features. For example, a high local density of nodes (causing hidden terminal collisions) might cause zero packet loss if the transmitter is very close and the SNR is extremely high (the capture effect). However, if the SNR is in the marginal transitional zone, that exact same density will cause exponential packet loss. 

ALE, by design, isolates the *marginal* effect of a single variable. When we sum the 1D ALE effect of SNR and the 1D ALE effect of Density linearly, we mathematically strip out the multi-variable interaction variance. The surrogate rule acts as if SNR and Density affect the packet completely independently, which is a physical impossibility. 

### 5.3 The Fair Comparison Baseline

To preemptively counter the argument that the ALE rule failed simply because it only used two features (while XGBoost used 8), we designed a rigorous fairness test. We trained a Depth 6 CART model restricted to the *exact same two features* (SNR and Density) utilized by the ALE rule.

Despite being starved of 75% of the dataset's features, the constrained 2-feature CART model yielded an $R^2$ of **0.3998**, vastly outperforming the 0.1437 of the 2-feature ALE rule. Because decision trees inherently split the data space hierarchically (e.g., checking Density *only after* verifying a specific SNR threshold), they effortlessly model the non-linear interaction variance that linearly additive surrogate rules destroy. 

This finding provides an important academic caution: while XAI techniques like ALE are excellent for analyzing marginal effects and providing interpretability, repurposing an additive sum of 1D marginals as a predictive model represents a category error in highly interactive physical environments. The assumption of linear additivity inherently strips away the critical non-linear multi-variable interactions that define the RF transitional region.

*Testbed Confirmation:* The ALE rule achieves $R^2$ = 0.100 on the physical testbed, underperforming both Linear Regression ($R^2$ = 0.107) and traditional RSSI-binned estimators ($R^2$ = 0.107). However, it should be noted that ALE (Apley & Zhu, 2020) was designed as an explainability tool, not as a model compression technique. This evaluation should be interpreted as testing whether XAI marginal-effect tools can double as deployment models—the answer is negative in both simulation and physical environments.

---

## 6. The Limitation of Knowledge Distillation

Another prominent strategy for deploying complex ML to edge devices is **Knowledge Distillation (KD)**. Originally pioneered in deep learning, KD involves transferring the knowledge of a massive "Teacher" model to a smaller, constrained "Student" model.

Instead of training the shallow Student tree on the hard, binary Ground Truth data (e.g., the packet either arrived `1` or failed `0`), the Student is trained on the continuous, soft-probability outputs of the Teacher (e.g., the Teacher predicts an 85% chance of success). These "soft labels" theoretically contain rich "dark knowledge" about the variance and shape of the data distributions that hard labels obscure. The training loss is governed by an interpolation parameter $\alpha$, which blends the Ground Truth loss with the Teacher loss.

We implemented a full KD pipeline (`src/modeling/knowledge_distillation.py`), systematically sweeping the $\alpha$ parameter (from 0.0 - pure teacher, to 1.0 - pure ground truth) across student CART trees of varying depths.

### 6.1 KD Sweep Results

Our empirical data revealed a fascinating, depth-conditional nuance that sharply limits the utility of Knowledge Distillation in the TinyML domain.

For severely constrained, ultra-shallow trees (Depths 2 through 6)—the exact region we previously identified as the Pareto-optimal hardware sweet spot—training on the Teacher's soft labels provided marginal to no statistically significant benefit. 
* At **Depth 6**, Ground Truth training yielded $R^2 = 0.7671$, while the pure KD student managed $R^2 = 0.7647$. The difference ($\Delta = 0.0024$) is well within the cross-fold standard deviation ($\pm 0.0545$), indicating no meaningful improvement.

However, as the student tree deepened and gained more capacity, KD began to show value. 
* At **Depth 8**, the pure KD student achieved an $R^2 = 0.7921$, outperforming the Ground Truth trained equivalent ($R^2 = 0.7838$).

### 6.2 Analysis of the Distillation Gap

Why does KD fail for shallow trees but succeed for deeper ones? The answer lies in the topological rigidity of shallow decision boundaries. A massive XGBoost teacher model creates a highly complex, beautifully curved probability surface across the 8-dimensional feature space. An ultra-shallow Depth 4 tree, limited to exactly 15 boolean splits, creates a crude, blocky, highly discretized topological map. 

When you attempt to force the shallow tree to learn the Teacher's smooth probabilities (KD), its limited split budget is wasted trying to fit smooth gradients that it architecturally cannot represent, rather than focusing on the high-impact, binary failures of the ground truth data. Only when the tree gains enough capacity (at Depth 8) to approximate smooth surfaces does the Teacher's "dark knowledge" become mathematically actionable.

**The Practical Trade-off:** The actual decision a practitioner faces is evaluating the KD-Depth-8 model ($R^2 = 0.7921$, 5,832 bytes) against the simpler GT-Depth-6 model ($R^2 = 0.7671$, 1,492 bytes). KD only becomes accuracy-positive precisely at a structural depth that requires a 400% increase in Flash memory over the Pareto-optimal GT baseline. Therefore, unless the hardware budget easily accommodates 6 KB of dedicated LQE logic, the architectural complexity of maintaining a Knowledge Distillation pipeline is difficult to justify.

*Testbed Implication:* On physical hardware, CART d8 achieves negative $R^2$ (-0.025), meaning even the Ground Truth tree at this depth is worse than predicting the mean. The KD benefit observed in simulation at depth 8 is therefore moot on real data—the student model overfits regardless of soft-label training. This further narrows KD's utility to simulation-scale feature spaces where deep trees remain viable.

---

## 7. Extended Network Analysis: LOFO & Link-Zones

While $R^2$ (coefficient of determination) is the standard statistical metric for regression models, it can be highly misleading when deployed as a routing metric. A model could achieve a high $R^2$ by perfectly predicting the easy links (PRR=1.0 or 0.0) while completely failing to map the volatile transitional zone. To ensure our models are robust from a network engineering perspective, we implemented extensive secondary metrics.

### 7.1 Leave-One-Feature-Out (LOFO) Correlative Masking

**Script:** `src/modeling/ablation_studies.py`

When analyzing the internal "Split Importance" generated by the XGBoost algorithm, we found severe discrepancies. Split Importance counts how many times a feature was used to make a decision across the 150 trees. 
* XGBoost reported that `Noise_Level_dBm` was the second most important feature in the entire dataset, carrying a massive **32.3%** importance weight (behind only `Transmission_Power_dBm` at **34.4%**).
* Conversely, `Local_Density` (the MAC-layer contention metric) carried only a **15.6%** importance weight.

To test true predictive value, we performed a strict Leave-One-Feature-Out (LOFO) analysis. We completely dropped one feature at a time, retrained the entire XGBoost model from scratch, and measured the drop in $R^2$. The results completely inverted the narrative:
* Dropping `Noise_Level_dBm` resulted in an insignificant LOFO accuracy drop of **0.0021**.
* Dropping `Local_Density` resulted in a catastrophic LOFO accuracy drop of **0.5076**.

**The Cause:** This highlights two phenomena. First, it is a classic example of Correlative Masking. `Noise_Level_dBm` is highly negatively correlated with `SNR_dB` ($r=-0.71$). When we remove Noise, the model effortlessly mathematically reconstructs the missing data by leaning heavily on the SNR feature. Therefore, while it is frequently used in splits (high importance), it contains highly redundant information. 

Second, the catastrophic drop associated with `Local_Density` reflects an explicit simulation artifact. Because our Python simulation engine mathematically forces a PRR penalty precisely based on the `Local_Density` variable to approximate CSMA/CA hidden-terminal collisions, the XGBoost model has effectively reverse-engineered the generator's penalty function. In a real-world physical deployment, density affects PRR in a much noisier, stochastically coupled manner alongside fading and environmental scatter. Therefore, this extreme LOFO result must be interpreted as a validation of the model's capacity to fit the simulated data generating process, rather than an absolute physical law of RF propagation.

### 7.2 Categorical Link-Zone F1 Scores

**Script:** `src/modeling/extended_metrics.py`

In an IPv6 RPL routing environment, a PRR prediction of 0.5 is catastrophic—it means half the packets will be lost, leading to endless MAC retries and battery death. Routing protocols function best with discrete categorical buckets. We implemented a secondary classification analysis grading our regression models on their ability to correctly categorize links into strict routing zones:
* **Good:** PRR > 0.90 (Ideal for routing)
* **Transitional:** 0.10 <= PRR <= 0.90 (Highly volatile, use with extreme caution)
* **Bad:** PRR < 0.10 (Effectively dead link)

We computed the weighted F1-Score for these classifications. The results further validate the Pareto frontier. The massive XGBoost teacher achieved a weighted F1 of 0.9836. Our optimal CART Depth 6 model, despite utilizing only 1.4KB of flash memory, maintained a weighted F1 of **0.9824**. 

*Note on Dataset Distribution:* An F1 score of 0.98 alongside an $R^2$ of ~0.76 strongly implies that the dataset exhibits a heavily bimodal distribution (the vast majority of links are either cleanly in the "Good" or "Bad" buckets, with fewer links genuinely resting in the highly volatile "Transitional" zone). While the massive memory reduction achieved by using shallow trees does not compromise the model's functional ability to categorize usable versus dead routing paths, the near-perfect F1 score may overstate the algorithm's precision on marginal transitional links specifically.

*Testbed Context:* On the FIT IoT-LAB testbed, the class imbalance is even more severe—76% of records have PRR = 1.0 (mean PRR = 0.916). Testbed F1-weighted scores range from 0.66 (mean baseline) to 0.74 (CART d2), which is substantially lower than simulation. Critically, transitional-region-only R² is negative for all models on the testbed (best: XGBoost at -1.81), meaning no model meaningfully predicts PRR variance within the transitional zone on real hardware. This confirms that standard R² is an inappropriate metric for heavily skewed testbed PRR distributions, and future work should evaluate models using transitional-region RMSE or calibration plots.

---

## 8. Directory & Implementation Guide

This repository has been structured for absolute transparency. The core simulation and compilation pipelines are fully automated and reproducible from scratch on your local machine. Please note that the final "Sim2Real" hardware validation phase (Section 2.4) requires an active, authenticated account with the FIT IoT-LAB testbed and is not reproducible purely locally.

### Exhaustive Repository Map

```text
.
├── README.md                           # This document (Full Methodology & Results)
├── manuscript_plan.txt                 # Manuscript structure, abstract, and deep analysis
├── requirements.txt                    # Python package dependencies (scikit, xgboost, m2cgen, etc.)
├── firmware/                           # Auto-generated C Code and Embedded Makefiles
│   ├── Makefile                        # Bare-metal Cortex-M3 compilation flags (-Os, -nostdlib)
│   ├── testbed_broadcast/              # Custom RIOT OS firmware for FIT IoT-LAB M3 physical testbed
│   │   ├── main.c                      # GNRC broadcast/listen firmware (RSSI, LQI, seq extraction)
│   │   └── Makefile                    # RIOT build config for iotlab-m3 board
│   ├── testbed_cart_depth{2..10}/      # Testbed-trained CART C models (4 features)
│   ├── cart_depth{2..10}/              # Simulation-trained CART C models (8 features)
│   ├── xgboost_full/                   # Transpiled XGBoost C source (150 trees, ~237KB .text)
│   ├── linreg/                         # Transpiled Linear Regression C source
│   └── ale_rule/                       # Transpiled ALE Surrogate Rules C source
├── data/
│   ├── raw/
│   │   ├── wsn_dataset.csv             # 4.05M rows generated by physics simulation engine
│   │   ├── iotlab_serial.log           # Raw serial_aggregator output from experiment 433617
│   │   ├── iotlab_radio.csv            # Parsed radio records (607K RX events)
│   │   └── iotlab_nodes.json           # IoT-LAB node metadata and coordinates
│   └── processed/                      # All JSON metrics (Pareto, LOFO, KD, testbed results, etc.)
│       ├── testbed_results.json        # Full testbed ML validation with baselines & Wilcoxon tests
│       ├── testbed_dataset.csv         # 56K link-level features for testbed ML
│       └── *.json                      # Simulation results (12 JSON files)
├── results/
│   ├── figures/                        # IEEE-compliant PDF/PNG publication figures
│   └── tables/                         # model_benchmarks.csv/json
├── scripts/
│   ├── run_pipeline.py                 # Master orchestration script (simulation pipeline, 15 steps)
│   ├── benchmark_size.py               # ARM arm-none-eabi-gcc invocation & precise byte extraction
│   ├── generate_plots.py               # IEEE-compliant matplotlib/seaborn PDF figure generation
│   ├── run_full_experiment.py          # End-to-end IoT-LAB experiment (compile→run→parse→validate)
│   ├── run_real_testbed.py             # Configurable serial-based IoT-LAB experiment runner
│   ├── test_firmware.py                # Automated 5-node firmware validation test
│   └── float_validation.py            # Validates float32 vs float64 delta R² < 0.001
└── src/
    ├── data/
    │   ├── fetch_testbed.py            # IoT-LAB REST API client & PCAP/CSV parser
    │   └── process_testbed.py          # Link-level feature extraction (Distance, RSSI, LQI, Density → PRR)
    ├── simulation/
    │   └── wsn_simulation.py           # Zuniga-Krishnamachari & CSMA/CA MAC physics generator
    ├── modeling/
    │   ├── train_and_extract.py        # Core pipeline: GroupKFold XGBoost, ALE extraction, Wilcoxon tests
    │   ├── pareto_frontier.py          # Estimator sweep & convergence bounds detection
    │   ├── testbed_validation.py       # Testbed ML validation with ETX/WMEWMA baselines & Wilcoxon tests
    │   ├── knowledge_distillation.py   # Alpha sweep for Teacher-Student soft-label transfer
    │   ├── spatial_leakage_comparison.py # Explicit Naive KFold vs GroupKFold proof mechanism
    │   ├── fair_ale_comparison.py      # Feature-restricted CART vs ALE baseline verifier
    │   ├── extended_metrics.py         # RMSE, MAE, Link-Zone F1, and transitional-region metrics
    │   ├── ablation_studies.py         # LOFO iterative removal & correlation masking checks
    │   ├── reweighting_experiment.py   # Class-reweighting analysis (inverse-freq, trans-only, oversampling)
    │   ├── grouping_comparison.py      # Robustness across grouping strategies (dst/src/link_id)
    │   └── bootstrap_ci.py            # Bootstrap confidence intervals for key metrics
    └── deployment/
        ├── generate_c_code.py          # m2cgen Transpilation + double-to-float FPU fixing + nan regex
        ├── generate_cart_c_code.py     # Batch transpilation for Depth 2-10 Decision Trees
        └── generate_linreg_c_code.py   # Transpilation for the OLS Baseline
```

### Reproducibility Guide

To regenerate the entire dataset, cross-compile the firmware artifacts, and render the IEEE-compliant PDFs, follow these steps.

#### 1. Prerequisites & Environment Setup
You must have Python 3.8 or higher installed. 

Crucially, to generate the `.text` memory metrics, you must have the GNU ARM Embedded Toolchain (`arm-none-eabi-gcc`) installed and present in your system's PATH. The pipeline relies on this compiler to target the simulated Cortex-M3 microcontroller.
* **Windows Users:** We highly recommend installing the MSYS2 environment. Once installed, launch the MSYS2 terminal and execute:
  ```bash
  pacman -S mingw-w64-x86_64-arm-none-eabi-gcc
  ```
* **Linux (Ubuntu/Debian) Users:** 
  ```bash
  sudo apt-get update
  sudo apt-get install gcc-arm-none-eabi
  ```

#### 2. Install Python Dependencies
Navigate to the root of the cloned repository and install the required data science packages:
```bash
pip install -r requirements.txt
```

#### 3. Execute the Master Orchestration Pipeline
The entire suite is controlled by a single master script. Execution takes approximately 20 to 30 minutes depending on your CPU core count, primarily gated by the physical simulation engine generating the 4-million row base dataset and the iterative cross-validation of the Knowledge Distillation alpha sweep.

```bash
python scripts/run_pipeline.py
```

#### 4. Physical Testbed Execution (Optional)
To reproduce the hardware validation results, you must have an active account with FIT IoT-LAB and configure SSH keys.
```bash
# Full pipeline: compile firmware, run 50-node experiment, parse serial data, run ML validation
python scripts/run_full_experiment.py

# Alternative: configurable experiment runner
python scripts/run_real_testbed.py --user varshney --nodes 50 --duration 15
```

#### Expected Output Trace (Simulation Pipeline):
1. `wsn_simulation.py` runs, iterating through 675 network topologies to generate `data/raw/wsn_dataset.csv`.
2. The core ML models train using `GroupKFold`, outputting accuracy metrics to `data/processed/`.
3. `m2cgen` transpiles the Python models. Regex scripts scrub out `double` floats and `nan` values, writing raw `main.c` files into the `firmware/` directory.
4. `benchmark_size.py` locates `arm-none-eabi-gcc`, compiles the C files with the `-Os -mthumb -mcpu=cortex-m3` flags, and runs `arm-none-eabi-size` to extract the `.text` and `.bss` counts.
5. The `generate_plots.py` script renders the Pareto Frontiers, Spatial Leakage graphs, and ALE Multi-panes as high-resolution PDFs directly into `results/figures/`.

#### Expected Output Trace (Testbed Pipeline):
1. `run_full_experiment.py` uploads firmware via SSH, compiles on IoT-LAB, submits 50-node experiment (15 min).
2. `serial_aggregator` captures 600s of broadcast data (~600K RX lines) to `data/raw/iotlab_serial.log`.
3. Serial log is parsed to `data/raw/iotlab_radio.csv` (607K radio records).
4. `process_testbed.py` computes link-level features, producing `data/processed/testbed_dataset.csv` (56K records).
5. `testbed_validation.py` runs GroupKFold CV with all models + ETX/WMEWMA baselines, outputting `data/processed/testbed_results.json`.

---
*End of Manuscript Documentation.*