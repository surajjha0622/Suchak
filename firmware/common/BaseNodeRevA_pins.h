#pragma once
// Pin map for hardware/base-node (Rev A, ex-CrashLink relay node).
// Source of truth: hardware/base-node/BaseNode_RevA_schematic.pdf
// ESP32-WROOM-32E, RFM95W (SX127x) on SPI.

// LoRa (RFM95W)
#define PIN_LORA_SCK   18
#define PIN_LORA_MOSI  19   // note: MOSI/MISO are NOT the ESP32 VSPI defaults on this board
#define PIN_LORA_MISO  23
#define PIN_LORA_NSS    5
#define PIN_LORA_RST   26
#define PIN_LORA_DIO0  27

// User I/O
#define PIN_LED1       13
#define PIN_LED2       33
#define PIN_SW1        35   // input-only pad (no internal pull-up)
#define PIN_SW2        34   // input-only pad (no internal pull-up)

// Not routed anywhere on Rev A (module pads only, no header) — see hardware/base-node/README.md
