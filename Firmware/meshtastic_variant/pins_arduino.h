#pragma once

#include <stdint.h>
#include "soc/soc_caps.h"

#define USB_VID 0x303A
#define USB_PID 0x1001

static const uint8_t TX = 43;
static const uint8_t RX = 44;

static const uint8_t SS    = 8;
static const uint8_t MOSI  = 6;
static const uint8_t MISO  = 7;
static const uint8_t SCK   = 5;

static const uint8_t BUTTON = 0;
