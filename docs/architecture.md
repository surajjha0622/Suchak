# Architecture

![Architecture](assets/architecture.svg)

Suchak is organised in **zones**. Each zone has several field nodes and one gateway. Gateways pass risk to the downstream zone over LoRa, and the gateway is the unit that keeps working with no Internet.

## Components

### Sensor node
- ESP32 reads the sensors and timestamps readings with a DS3231 RTC.
- **Rain gauge** for rainfall; **water-level** sensing at selected river / stream points.
- **Vibration / frequency sensor** (ADXL345) to detect approaching flash floods.
- Readings are packed into compact packets and sent over SX1262 LoRa to the zone gateway.
- Powered by solar + LiFePO₄; sleeps between samples and wakes on RTC schedule.

### Camera node
- Watches strategic points: bridges, culverts, narrow channels.
- The frame is processed **on the node** (OpenCV). Only the **detection result and its confidence** are sent over LoRa — never video. This keeps the link light and the node low-power.

### Zone gateway
- Receives node packets over LoRa (Raspberry Pi 5 / Jetson Nano class).
- **Checks incoming data** and calculates **rate of rise** from water-level readings.
- **Fuses** rainfall, water level, vibration signature and camera result. Each result carries a **high / medium / low confidence**, and the gateway assigns a **local risk level**.
- **Adaptive sampling:** rising risk increases sampling frequency; a vibration or camera flag increases level and camera checks.
- **Siren and dashboard alert** only on confirmed, high-confidence risk (signals must agree).
- Shares important risk with neighbouring gateways over LoRa.
- Stores data locally and syncs when the Internet returns.

### Dashboards
- **Authorities local dashboard** — runs on the gateway: siren control, node health, zone risk map. Works offline.
- **Public web dashboard** — zone risk map, served by the backend when online.

### Backend
- Python / FastAPI, PostgreSQL + TimescaleDB for time series.
- QGIS / GIS layer for zone-wise risk maps.

## Data flow

1. Node samples → packet → LoRa → gateway. Camera node sends result + confidence only.
2. Gateway validates, computes rate of rise, fuses the signals, assigns confidence and a local risk level.
3. Rising risk → sampling frequency increases; vibration or camera flag → more level and camera checks.
4. Confirmed high-confidence risk → local siren and dashboard alert, no Internet needed.
5. Upstream alert → LoRa message to the downstream gateway → it checks more often.
6. When the Internet is available, stored data syncs to the backend and the public dashboard.

## Offline mode

The LoRa gateway, authorities dashboard, sirens and the Pi 5 / Jetson Nano keep working without Internet. Data is stored locally, local alerts continue, and stored data syncs when the Internet returns. Camera inference runs on the node, not in the cloud.

## What is proposed vs built

Everything above is the proposed design except the reused base board and the LoRa ping sketch (itself not yet run on hardware). Zone coordination, adaptive sampling, on-node camera inference and local risk logic are VE GA's proposed features, as stated in the deck. See the [status table](../README.md#status).
