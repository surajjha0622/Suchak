# Feasibility

| Engineering risk | Mitigation | Why it is viable |
|------------------|-----------|------------------|
| Remote power | Solar + LiFePO₄ + deep sleep + RTC scheduling | Low-power operation reduces maintenance |
| Internet failure | Gateway processes and stores data locally | Detection and local alerts do not depend on the Internet |
| AI inference constrained at the node | Lightweight anomaly model / TinyML for local inference | Local decisions reduce latency and bandwidth |
| False alarms from noisy sensor data | Data-quality checks + temporal features + model confidence | Risk uses validated observations and model output |
| Fast-changing conditions | Rate of rise + adaptive sampling + local anomaly detection | More observations when conditions change |
| Different hazards at different locations | Modular sensor nodes for flood, fire, air quality, others | Common gateway, risk engine and dashboard |

## Open items we know about

These are not in the submission deck but matter for the build:

- **Deep-sleep current** of the reused base board is unmeasured (USB-UART chip, LEDs and buck-boost quiescent current all count).
- **Solar charging** is not on the base board; a LiFePO₄-capable charger / MPPT stage must be added.
- **LoRa band**: unlicensed LoRa in India is 865–867 MHz. The reused board's module is a 915 MHz part — see [hardware-reuse.md](hardware-reuse.md).
- **Sensor choice and calibration** (tipping-bucket resolution, water-level sensing method and its outdoor durability) are undecided.
