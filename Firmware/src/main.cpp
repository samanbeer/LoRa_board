#include <Arduino.h>
#include <SPI.h>
#include <RadioLib.h>

// -------------------------------------------------------------
// Pin Configuration (ESP32-S3 to SX1262)
// -------------------------------------------------------------
#ifndef LORA_SCK
#define LORA_SCK    5
#define LORA_MISO   7
#define LORA_MOSI   6
#define LORA_CS     8
#define LORA_RESET  3
#define LORA_BUSY   4
#define LORA_DIO1   9
#endif

// Initialize custom SPI bus
SPIClass spiBus(FSPI);

// Create SX1262 instance
// NSS: 8, DIO1: 9, NRST: 3, BUSY: 4
SX1262 radio = new Module(LORA_CS, LORA_DIO1, LORA_RESET, LORA_BUSY, spiBus);

// Counter for transmitted packets
int packetCounter = 0;
unsigned long lastTxTime = 0;
const unsigned long txInterval = 5000; // send beacon every 5 seconds

void setup() {
    // Native USB CDC serial initialization
    Serial.begin(115200);
    delay(2000);

    Serial.println();
    Serial.println("==================================================");
    Serial.println(" LoRa Board (ESP32-S3 + SX1262) - Hardware Test   ");
    Serial.println("==================================================");

    // Initialize custom SPI pins for ESP32-S3
    spiBus.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);

    // Initialize SX1262:
    // Frequency: 868.0 MHz
    // Bandwidth: 125.0 kHz
    // Spreading Factor: 9
    // Coding Rate: 7 (4/7)
    // Sync Word: 0x12 (private network)
    // Power: +14 dBm (up to +22 dBm supported)
    // Preamble: 8 symbols
    // TCXO voltage: 0 (using onboard 32MHz XTAL, not TCXO)
    Serial.print(F("[SX1262] Initializing radio... "));
    int state = radio.begin(868.0, 125.0, 9, 7, 0x12, 14, 8, 0.0, false);

    if (state == RADIOLIB_ERR_NONE) {
        Serial.println(F("SUCCESS!"));
    } else {
        Serial.print(F("FAILED, code "));
        Serial.println(state);
        while (true) {
            delay(1000);
        }
    }

    // Configure SX1262 DIO2 to automatically control PE42359 RF Switch!
    Serial.print(F("[SX1262] Enabling DIO2 as RF Switch Control... "));
    state = radio.setDio2AsRfSwitchCtrl(true);
    if (state == RADIOLIB_ERR_NONE) {
        Serial.println(F("SUCCESS!"));
    } else {
        Serial.print(F("FAILED, code "));
        Serial.println(state);
    }

    Serial.println(F("[SX1262] Setup complete. Starting beacon transmission loop..."));
}

void loop() {
    unsigned long now = millis();

    if (now - lastTxTime >= txInterval) {
        lastTxTime = now;
        packetCounter++;

        String message = "LoRa_Board #" + String(packetCounter);
        Serial.print(F("[TX] Transmitting packet: "));
        Serial.print(message);
        Serial.print(F(" ... "));

        int state = radio.transmit(message);

        if (state == RADIOLIB_ERR_NONE) {
            Serial.println(F("Done!"));
        } else {
            Serial.print(F("Error, code "));
            Serial.println(state);
        }
    }

    delay(10);
}
