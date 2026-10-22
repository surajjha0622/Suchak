# Suchak — Flood Early-Warning System

**Distributed sensors and local zone gateways that decide flood risk on the spot, zone by zone, and keep alerting when the Internet does not.**

Submitted to **Smart India Hackathon 2026** · Problem Statement [SIH26223](https://sih2026.vuce.in/ps/SIH26223) (Student Innovation — Disaster Management) · Hardware · Team **VE GA** (Team ID 155626)

<p align="center">
  <img src="docs/assets/architecture.svg" alt="Suchak system architecture" width="900">
</p>

---

## Problem

- Flood alerts can be delayed by centralized monitoring and multiple decision stages — an alert has to pass through people before it reaches anyone who can act.
- Remote areas may also have limited local monitoring and unreliable connectivity.

## Solution

Let the sensors decide on the spot, zone by zone.

- **Distributed sensors + local gateways** for zone-wise flood monitoring.
- **Camera and vibration / frequency nodes** give an early flash-flood indication.
- **LoRa carries processed results only — never raw video.**
- **Local risk detection and siren alerts** even when the Internet is unavailable.
- **Cooperative warning:** risk information is shared with downstream zones as conditions change.
- **Public web dashboard** showing the zone risk map.
- **Authorities local dashboard** for siren control, node health and the zone risk map.

```
Rainfall + Water Level + Vibration + Camera  →  Local Risk  →  Downstream Warning  →  Alert
```

## How it works

| Stage | What happens |
|-------|--------------|
| **1. Data collection** | Rain gauge; water level at selected river / stream points; camera nodes at bridges, culverts and narrow channels; vibration / frequency sensors for approaching flash floods; government weather data when available |
| **2. Communication** | ESP32 collects readings → SX1262 LoRa → zone gateway. Cameras send only the detection result and its confidence. Gateway-to-gateway links share important risk |
| **3. Processing** | Check incoming data, compute rate of rise from water level, fuse rainfall + level + vibration signature + camera result, attach a high / medium / low confidence, assign a local risk level |
| **4. Response** | Rising risk → faster sampling. Vibration or camera flag → more level and camera checks. Upstream alert → downstream zone checks more often. Confirmed high-confidence risk → local siren + dashboard alert |

**Offline mode:** the LoRa gateway, authorities dashboard, sirens and the Pi 5 / Jetson Nano keep working without Internet. Data is stored locally, local alerts continue, and stored data syncs when the Internet returns.

More detail in [`docs/architecture.md`](docs/architecture.md).

## Status

Being explicit about what exists:

| Area | State |
|------|-------|
| Idea, architecture, SIH submission | Done — see [`docs/`](docs/) |
| Base node PCB (ESP32 + LoRa + power + USB-C) | **Reused from [CrashLink](https://github.com/surajjha0622/CrashLink)** — design files in [`hardware/base-node/`](hardware/base-node/). Needs changes for Suchak, see [hardware reuse notes](docs/hardware-reuse.md) |
| LoRa bring-up firmware | Draft sketch in [`firmware/bringup/`](firmware/bringup/), **not yet run on hardware** |
| Sensor drivers (rain gauge, water level, ADXL345, DS3231) | Planned |
| Local risk logic (rate of rise, fusion, confidence, adaptive sampling) | Planned |
| Camera node (on-node detection, result + confidence only) | Planned — compute platform not yet chosen, see [feasibility](docs/feasibility.md) |
| Zone gateway (Pi 5 / Jetson Nano) + siren control | Planned |
| Backend + public / authorities dashboards | Planned |
| Field testing | Not started |

## Repository layout

```
Suchak/
├── docs/
│   ├── architecture.md        System design, data flow, offline behaviour
│   ├── hardware-reuse.md      What is reused from CrashLink and what must change
│   ├── feasibility.md         Engineering risks → mitigation, open items
│   ├── roadmap.md             Bench test → field node → pilot → validate
│   ├── references.md          Research + component references
│   ├── assets/                Diagrams
│   └── presentation/          SIH 2026 technical deck (.pptx)
├── hardware/
│   └── base-node/             ESP32 + LoRa base board (from CrashLink relay node)
└── firmware/
    ├── common/                Board pin map
    └── bringup/lora_ping/     LoRa link test sketch
```

## Tech stack

| Layer | Choice |
|-------|--------|
| Node MCU | ESP32 |
| Radio | LoRa, SX1262 (the reused Rev A board carries an RFM95W / SX127x) |
| Sensing | Rain gauge, water level, ADXL345 accelerometer (vibration / frequency), camera + OpenCV |
| Timekeeping | DS3231 RTC |
| Power | Solar + LiFePO₄, deep sleep + RTC scheduling |
| Gateway | Raspberry Pi (Pi 5 / Jetson Nano) |
| Backend | Python, FastAPI, PostgreSQL, TimescaleDB |
| Mapping | QGIS / GIS |

## Implementation path

1. **Bench test** — different conditions at different locations, simulated on the desk
2. **Field node** — solar, enclosure, real rainfall / water level
3. **Multi-node pilot** — multiple nodes at important locations; risk checked zone by zone
4. **Validate + scale**

Details in [`docs/roadmap.md`](docs/roadmap.md).

## Related work

- [CrashLink](https://github.com/surajjha0622/CrashLink) — ESP32 + LoRa distributed alert prototype by the same team; source of the base node PCB.

## Documents

- [SIH 2026 technical deck](docs/presentation/SIH2026-VEGA-SIH26223-TECHNICAL-REFINED.pptx)
- [References](docs/references.md)

## License

MIT — see [LICENSE](LICENSE).
