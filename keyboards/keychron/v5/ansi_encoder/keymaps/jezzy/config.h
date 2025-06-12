#pragma once

// Remove the keyboard-level definition so we can redefine it
#undef  CAPS_LOCK_LED_INDEX
#define CAPS_LOCK_LED_INDEX        72  // C key in Qwerty
#define NUM_LOCK_LED_INDEX         31
#define SCROLL_LOCK_LED_INDEX      14
#define LAYER_INDICATOR_LED_INDEX  0   // Escape key

#define RGB_MATRIX_DEFAULT_MODE    RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define RGB_MATRIX_DEFAULT_HUE     255
#define RGB_MATRIX_DEFAULT_SAT     235
#define RGB_MATRIX_DEFAULT_VAL     180
#define RGB_MATRIX_DEFAULT_SPD     85
#define RGB_MATRIX_HUE_STEP        1
#define RGB_MATRIX_SAT_STEP        5
#define RGB_MATRIX_VAL_STEP        5
#define RGB_MATRIX_SPD_STEP        5

#define TAPPING_TERM               200  // milliseconds
