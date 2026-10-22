# Feasibility

Engineering risks and how the design handles them (from the technical deck):

| Engineering risk | Mitigation | Why it is viable |
|------------------|-----------|------------------|
| Remote power | Solar + LiFePO₄ + deep sleep + RTC scheduling | Low-power operation reduces maintenance |
| Internet failure | Gateway processes and stores data locally | Detection and local alerts do not depend on the Internet |
| Video is too heavy for LoRa | Camera frame processed on the node; only result + confidence sent | Keeps the LoRa link light and the node low-power |
| False alarms from a single sensor | Vibration, camera, rainfall and level cross-checked with confidence levels | A siren fires only on agreeing, high-confidence signals |
| Fast-changing conditions | Rate of rise + adaptive sampling | More readings are taken when conditions change |

## Open items we know about

These are not in the deck but matter for the build:

- **Camera node compute.** An ESP32 alone is unlikely to run OpenCV-class detection. The platform for on-node inference (and its power budget on solar) is undecided.
- **Deep-sleep current** of the reused base board is unmeasured (USB-UART chip, LEDs and buck-boost quiescent current all count).
- **Solar charging** is not on the base board; a LiFePO₄-capable charger / MPPT stage must be added.
- **LoRa band**: unlicensed LoRa in India is 865–867 MHz. The reused board's module is a 915 MHz part — see [hardware-reuse.md](hardware-reuse.md).
- **Sensor choice and calibration**: tipping-bucket resolution, water-level sensing method and its outdoor durability, and the ADXL345 mounting and flash-flood vibration signature are undecided.
- **Fusion thresholds and false-alarm rate** need validation against real events before sirens are trusted.
