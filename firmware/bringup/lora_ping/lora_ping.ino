// LoRa link bring-up for the Suchak base node (Rev A).
// Flash the same sketch on two boards: each sends a counter every 2 s and prints
// anything it receives with RSSI/SNR.
//
// STATUS: draft, not yet run on hardware.
// Needs the "LoRa" library by Sandeep Mistry (SX127x). The Rev A radio is an
// RFM95W-915S2, so this exercises the link but not the final SX1262 radio.
#include <SPI.h>
#include <LoRa.h>
#include "../../common/BaseNodeRevA_pins.h"

// Set to a frequency your module is built for AND that is legal where you test.
// India unlicensed LoRa is 865-867 MHz; a 915 MHz module may perform poorly there.
#ifndef LORA_FREQ_HZ
#define LORA_FREQ_HZ 866E6
#endif

uint32_t counter = 0;
uint32_t lastTx = 0;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED1, OUTPUT);

  SPI.begin(PIN_LORA_SCK, PIN_LORA_MISO, PIN_LORA_MOSI, PIN_LORA_NSS);
  LoRa.setPins(PIN_LORA_NSS, PIN_LORA_RST, PIN_LORA_DIO0);

  if (!LoRa.begin(LORA_FREQ_HZ)) {
    Serial.println("LoRa init failed - check wiring/antenna/frequency");
    while (true) delay(1000);
  }
  LoRa.setSpreadingFactor(9);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);
  LoRa.setSyncWord(0x12);
  LoRa.receive();
  Serial.println("Suchak base node: LoRa ready");
}

void loop() {
  if (millis() - lastTx >= 2000) {
    lastTx = millis();
    LoRa.beginPacket();
    LoRa.print("SUCHAK ");
    LoRa.print(counter++);
    LoRa.endPacket();          // blocking TX
    LoRa.receive();            // back to RX
    digitalWrite(PIN_LED1, !digitalRead(PIN_LED1));
  }

  int size = LoRa.parsePacket();
  if (size) {
    String msg;
    while (LoRa.available()) msg += (char)LoRa.read();
    Serial.printf("RX '%s' RSSI=%d SNR=%.1f\n", msg.c_str(), LoRa.packetRssi(), LoRa.packetSnr());
  }
}
