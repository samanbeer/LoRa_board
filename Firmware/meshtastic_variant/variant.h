#pragma once

// Target Hardware: Custom ESP32-S3 + Semtech SX1262 LoRa Board (868 MHz)

#define HAS_BLUETOOTH 1
#define HAS_WIFI 1

// Button & LED configuration
#define BUTTON_PIN 0       // BOOT1 button (GPIO 0)
#define BUTTON_NEED_PULLUP

// ---------------------------------------------------------
// LoRa SX1262 Configuration
// ---------------------------------------------------------
#define USE_SX1262

// SPI Bus
#define LORA_SCK   5
#define LORA_MISO  7
#define LORA_MOSI  6
#define LORA_CS    8       // NSS

// Control Pins
#define LORA_RESET 3       // SX1262 NRESET
#define LORA_DIO1  9       // SX1262 DIO1 (IRQ)
#define SX126X_BUSY 4      // SX1262 BUSY

// RadioLib compatibility mappings
#define SX126X_CS    LORA_CS
#define SX126X_DIO1  LORA_DIO1
#define SX126X_RESET LORA_RESET

// RF Switch (PE42359 controlled via SX1262 DIO2)
#define SX126X_DIO2_AS_RF_SWITCH

// Crystal Oscillator (Abracon ABM8 32MHz XTAL)
// (DIO3 is not used for TCXO power on this board)
