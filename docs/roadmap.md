# Roadmap

## 1 · Bench test
- [ ] Run the LoRa ping sketch on two base boards ([firmware/bringup](../firmware/bringup/lora_ping/))
- [ ] Wire a DS3231 (I²C) and a tipping-bucket rain gauge input
- [ ] Water-level sensing method chosen and read on the bench
- [ ] Measure deep-sleep current of the base board

## 2 · Field node
- [ ] Base board Rev B: SX1262, correct LoRa band, solar charger, sensor + RTC headers ([details](hardware-reuse.md))
- [ ] Solar + LiFePO₄ power path validated
- [ ] Weatherproof enclosure (start from the CrashLink relay case)
- [ ] Rule-based local risk logic (rate of rise, thresholds)

## 3 · Multi-node pilot
- [ ] Zone gateway on Raspberry Pi receiving from several nodes
- [ ] Offline buffer + sync
- [ ] Adaptive sampling
- [ ] Upstream → downstream risk sharing between two gateways
- [ ] FastAPI + TimescaleDB backend, first dashboard / QGIS map

## 4 · Validate + scale
- [ ] Compare alerts against observed rainfall / river events
- [ ] Train and evaluate the TinyML anomaly model against the rule-based baseline
- [ ] Add a second hazard module to prove modularity
