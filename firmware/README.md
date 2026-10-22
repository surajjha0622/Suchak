# Firmware

| Path | What | State |
|------|------|-------|
| `common/BaseNodeRevA_pins.h` | Pin map for the Rev A base board, taken from the schematic | Done |
| `bringup/lora_ping/` | Two-board LoRa ping test | Draft, not yet run on hardware |

Planned next: DS3231 + rain-gauge + water-level drivers, deep-sleep scheduler, packet format, rule-based risk logic.

Toolchain: Arduino (ESP32 core) for now. Library: *LoRa* by Sandeep Mistry for the SX127x radio on Rev A; the SX1262 target will need a different driver (e.g. RadioLib).
