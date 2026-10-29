# LoRa Board Firmware Guide (Meshtastic & RadioLib)

This directory contains the firmware configurations, hardware pinout mappings, and test source code for the **ESP32-S3 + SX1262 LoRa Board (868 MHz)**.

---

## 1. Hardware Pinout Mapping

| Function | ESP32-S3 Pin | SX1262 / Hardware Net | Description |
| :--- | :---: | :---: | :--- |
| **SPI SCK** | GPIO 5 | `SCK` | SPI Clock |
| **SPI MOSI** | GPIO 6 | `MOSI` | SPI Master Out Slave In |
| **SPI MISO** | GPIO 7 | `MISO` | SPI Master In Slave Out |
| **LoRa CS (NSS)** | GPIO 8 | `NSS` | Radio Chip Select |
| **LoRa RESET** | GPIO 3 | `RESET` | Active-low Radio Reset |
| **LoRa BUSY** | GPIO 4 | `BUSY` | Radio Busy status signal |
| **LoRa DIO1** | GPIO 9 | `DIO1` | Primary IRQ interrupt pin |
| **RF Switch (DIO2)**| N/A | `DI12` / `CTRL` | Directly driven by SX1262 DIO2 (`DIO2_AS_RF_SWITCH`) |
| **Crystal / XTAL** | N/A | `XTA` / `XTB` | 32 MHz Quartz Crystal (ABM8) |
| **BOOT Button** | GPIO 0 | `BOOT1` | Firmware upload / User button |
| **RESET Button** | EN / RST | `RESET1` | Hardware reset |
| **USB CDC/JTAG** | GPIO 19/20 | `USB_D-` / `USB_D+` | Native USB-C communication |

---

## 2. Meshtastic Support

The board uses Semtech SX1262 and ESP32-S3, which is 100% compatible with the official [Meshtastic](https://meshtastic.org/) ecosystem!

### Option A: Using the Custom Meshtastic Variant
In the `meshtastic_variant/` folder:
- **`variant.h`**: Defines the exact SPI and SX1262 control lines, and specifies `#define SX126X_DIO2_AS_RF_SWITCH` so the SX1262 automatically manages the PE42359 SPDT RF switch during TX and RX.
- **`pins_arduino.h`**: Core pin definitions for PlatformIO compilation.

To build Meshtastic for this board:
1. Clone the official [Meshtastic Firmware](https://github.com/meshtastic/firmware) repository.
2. Place the contents of `meshtastic_variant/` into a new target under `variants/esp32s3/lora_board/` (or adapt `variants/esp32s3/heltec_v3/`).
3. Build and upload using PlatformIO:
   ```bash
   pio run -e esp32s3-lora_board -t upload
   ```

### Option B: Using Meshtastic Web Flasher / Generic ESP32-S3
You can also flash a generic ESP32-S3 SX1262 build via the [Meshtastic Web Flasher](https://flasher.meshtastic.org/) and override the GPIO pin definitions in the Meshtastic CLI or Web App settings using the pin table above.

---

## 3. Quick Hardware Test (PlatformIO & RadioLib)

Before running Meshtastic, you can quickly verify that your assembled board, soldering, RF switch, and antenna are working properly using the provided test project.

### How to test:
1. Connect the board via USB-C.
2. Open this `Firmware/` folder in [PlatformIO](https://platformio.org/) (VS Code).
3. If entering bootloader mode is required:
   - Hold **BOOT1** (GPIO 0).
   - Press and release **RESET1**.
   - Release **BOOT1**.
4. Run the upload command:
   ```bash
   pio run -t upload
   ```
5. Open Serial Monitor (`115200` baud):
   ```bash
   pio device monitor
   ```
6. You will see:
   ```text
   ==================================================
    LoRa Board (ESP32-S3 + SX1262) - Hardware Test   
   ==================================================
   [SX1262] Initializing radio... SUCCESS!
   [SX1262] Enabling DIO2 as RF Switch Control... SUCCESS!
   [SX1262] Setup complete. Starting beacon transmission loop...
   [TX] Transmitting packet: LoRa_Board #1 ... Done!
   ```

> [!CAUTION]
> Always ensure the U.FL antenna is attached before transmitting RF packets to prevent damaging the SX1262 output amplifier.
