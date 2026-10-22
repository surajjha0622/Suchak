# Roadmap

## 1 · Bench test
- [ ] Run the LoRa ping sketch on two base boards ([firmware/bringup](../firmware/bringup/lora_ping/))
- [ ] Wire a DS3231 (I²C) and a tipping-bucket rain gauge input
- [ ] Read an ADXL345 over I²C and look at the vibration / frequency signal
- [ ] Water-level sensing method chosen and read on the bench
- [ ] Measure deep-sleep current of the base board

## 2 · Field node
- [ ] Base board Rev B: SX1262, correct LoRa band, solar charger, sensor + RTC headers ([details](hardware-reuse.md))
- [ ] Solar + LiFePO₄ power path validated
- [ ] Weatherproof enclosure (start from the CrashLink relay case)
- [ ] Camera node: choose compute platform, run on-node detection, send result + confidence only
- [ ] Rule-based local risk logic: rate of rise, fusion, high / medium / low confidence

## 3 · Multi-node pilot
- [ ] Zone gateway (Pi 5 / Jetson Nano) receiving from several nodes
- [ ] Offline buffer + sync
- [ ] Adaptive sampling
- [ ] Siren control + authorities local dashboard
- [ ] Upstream → downstream risk sharing between two gateways
- [ ] FastAPI + TimescaleDB backend, public dashboard / QGIS zone risk map

## 4 · Validate + scale
- [ ] Compare alerts against observed rainfall / river events
- [ ] Tune fusion thresholds to reduce false alarms
- [ ] Expand to more zones
