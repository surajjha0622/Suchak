# Architecture

![Architecture](assets/architecture.svg)

Suchak is organised in **zones**. Each zone has several sensor nodes and one gateway. Zones talk to each other and to a regional backend.

## Components

### Sensor node
- ESP32 reads the sensors and timestamps readings with a DS3231 RTC.
- **Current prototype (flood):** rainfall (rain gauge) and water level.
- Readings are packed into compact packets and sent over LoRa to the zone gateway.
- Powered by solar + LiFePO₄; sleeps between samples and wakes on RTC schedule.
- Sensor interfaces are modular, so smoke, air quality, heat, gas, soil moisture or vibration sensors can be added without changing the gateway.

### Zone gateway
- Receives node packets over LoRa.
- **Data-quality checks** (range, stuck values, missing samples) before any risk is computed.
- **Temporal features**, e.g. rate of rise from water-level readings.
- **Local risk logic** produces a risk level per zone. A lightweight anomaly / TinyML model is the *proposed* addition; until it is validated, risk is decided by explicit rules.
- Triggers local alerts (e.g. siren) and **adaptive sampling** (nodes sample faster when risk rises).
- Buffers data and event summaries locally and syncs when the Internet is available.
- Shares risk with neighbouring gateways over LoRa.

### Regional backend
- Python / FastAPI ingestion, PostgreSQL + TimescaleDB for time series.
- GIS layer (QGIS) for zone-wise risk maps.
- Authority and public dashboards showing risk, sensor status and alerts; long-term trend analysis.

## Data flow

1. Node samples → packet → LoRa → gateway.
2. Gateway validates, derives features, computes risk.
3. Rising risk → gateway tells nodes to sample faster (adaptive sampling).
4. Local hazard detected → local alert immediately, no Internet needed.
5. Upstream risk → LoRa message to downstream gateway → it raises monitoring.
6. Only critical alerts, summaries and risk assessments go to the backend, which keeps bandwidth and latency low.

## Offline behaviour

Sensing, edge processing, LoRa communication and local alerts do not depend on the Internet. Events are stored in the gateway buffer and synchronised later.

## What is proposed vs built

Edge AI, cooperative upstream/downstream behaviour and the multi-hazard modules are proposed features. The flood prototype starts with local risk logic while the AI layer is developed and validated. See the [status table](../README.md#status).
