#pragma once
#include "main.h"
#include <furi.h>

#define DEBOUNCE_TICKS 10
#define GPIO_INPUT_PINS_COUNT 6

extern const GpioPin input_gpio[GPIO_INPUT_PINS_COUNT];
extern const bool input_invert[GPIO_INPUT_PINS_COUNT];

extern const GpioPin led_gpio[3];
extern const GpioPin backlight_gpio;
extern const GpioPin sd_cs_gpio;
extern const GpioPin vibro_gpio;
extern const GpioPin ibutton_gpio;
extern const GpioPin cc1101_g0_gpio;
