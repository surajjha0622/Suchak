# Hardware reuse from CrashLink

Only the **relay node** board from [CrashLink](https://github.com/surajjha0622/CrashLink) is carried over, as the **Suchak base node**. The CrashLink vehicle and gateway boards are not used: they exist for LTE, GPS and crash detection, which Suchak does not need.

Source in CrashLink: `hardware/pcb/RNode.epro2`, `SCH_RNode.pdf` and the PNG renders (CrashLink commit `b8a8dd2`, board silkscreen *CrashLink_v1.0*, schematic updated 2026-09-15).

## What the board already gives us

| Block | Parts | Useful for Suchak because |
|-------|-------|---------------------------|
| MCU | ESP32-WROOM-32E-N8 | Same MCU family as the deck |
| LoRa | RFM95W-915S2 + U.FL antenna connector | Working radio footprint, SPI wiring done |
| Power | TPS63001 buck-boost to 3.3 V from a 1.8–5.5 V input, screw terminal | Works from one Li-ion/LiFePO₄ cell |
| Programming | USB-C, CP2102N, auto-reset transistors, ESD protection | Flash and serial without an adapter |
| User I/O | 2 LEDs, 2 buttons, BOOT/EN buttons | Bring-up and debugging |

## What does not fit Suchak (and must change in Rev B)

| Gap | Why it matters | Rev B change |
|-----|----------------|--------------|
| **Radio is an RFM95W (SX1276)**, deck says **SX1262** | Different chip, different pinout (SX1262 needs BUSY and DIO1), different driver | Replace U7 with an SX1262 module and re-route the radio block |
| **915 MHz module** | Unlicensed LoRa in India is 865–867 MHz; a 915 MHz-matched module will have poor performance there | Pick an 865–867 MHz-capable SX1262 module |
| **No RTC** | Deck uses DS3231 for timestamps and scheduled wake | Add DS3231 on I²C (IO21/IO22 are free on the ESP32) |
| **No sensor connectors** | Spare ESP32 pads are not broken out; the module is soldered straight to the board | Add headers for rain-gauge pulse input, analog/digital water-level input, I²C |
| **No solar charger** | Deck specifies solar + LiFePO₄ | Add a LiFePO₄-capable solar charger / MPPT stage |
| **Deep-sleep current unknown** | Always-on USB-UART chip, LEDs and converter quiescent draw | Measure; consider gating CP2102N and LED power |
| **Silkscreen** says *Relay Node / CrashLink_v1.0* | Confusing for a different project | Re-label |

The existing board is still good for **bench bring-up** of the LoRa link and ESP32 firmware while Rev B is designed.

## Things worth knowing about the CrashLink source

While reading the schematic against the CrashLink relay firmware, two mismatches turned up. They are CrashLink issues, but anyone reusing its firmware on this PCB will hit them:

- The schematic puts **MOSI on IO19 and MISO on IO23**; `CrashLinkProtocol.h` has MISO 19 / MOSI 23.
- The schematic has **RST on IO26 and DIO0 on IO27**; the firmware header has RST 14 / DIO0 26.

Suchak's own pin header (`firmware/common/BaseNodeRevA_pins.h`) follows the schematic.

The archived `archives/pcb/relay_node/` in CrashLink (Gerbers, BOM, pick-and-place) is an **older** revision built around an ESP32-S3 dev-board socket without USB-C, so it was not copied. CrashLink has no Gerbers for the current RNode revision.
