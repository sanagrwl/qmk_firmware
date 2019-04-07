#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"
#include "keymap_french.h"
#include "keymap_spanish.h"
#include "keymap_hungarian.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  RGB_SLD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox(KC_EQUAL,KC_1,KC_2,KC_3,KC_4,KC_5,TT(1),KC_TAB,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_TRANSPARENT,KC_GRAVE,LSFT_T(KC_A),LCTL_T(KC_S),LALT_T(KC_D),LGUI_T(KC_F),KC_G,KC_LSPO,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_ESCAPE,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_LEFT,KC_RIGHT,KC_F5,KC_F6,KC_HOME,KC_BSPACE,KC_DELETE,KC_END,KC_TRANSPARENT,KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINUS,KC_TRANSPARENT,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_BSLASH,KC_H,LGUI_T(KC_J),LALT_T(KC_K),LCTL_T(KC_L),LSFT_T(KC_SCOLON),KC_QUOTE,KC_ESCAPE,KC_N,KC_M,KC_COMMA,KC_DOT,KC_SLASH,KC_RSPC,KC_UP,KC_DOWN,KC_LBRACKET,KC_RBRACKET,KC_CAPSLOCK,KC_F7,KC_F8,KC_PGUP,KC_PGDOWN,KC_ENTER,KC_SPACE),

  [1] = LAYOUT_ergodox(KC_AUDIO_MUTE,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,TO(0),KC_AUDIO_VOL_UP,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_AUDIO_VOL_DOWN,KC_LSHIFT,KC_LCTRL,KC_LALT,KC_LGUI,KC_TRANSPARENT,KC_LSHIFT,KC_TRANSPARENT,KC_TRANSPARENT,KC_UP,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_LEFT,KC_DOWN,KC_RIGHT,KC_TRANSPARENT,KC_TRANSPARENT,KC_HOME,KC_TRANSPARENT,KC_TRANSPARENT,KC_END,KC_TRANSPARENT,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_F12,KC_TRANSPARENT,KC_LGUI,KC_LALT,KC_LCTRL,KC_RSHIFT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_UP,KC_TRANSPARENT,KC_SLASH,KC_RSHIFT,KC_LEFT,KC_DOWN,KC_RIGHT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_PGUP,KC_PGDOWN,KC_ENTER,KC_SPACE),

};

bool suspended = false;
const uint16_t PROGMEM fn_actions[] = {
[1] = ACTION_LAYER_TAP_TOGGLE(1)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
switch(id) {
case 0:
if (record->event.pressed) {
SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
}
break;
}
return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
switch (keycode) {
// dynamically generate these.
case EPRM:
if (record->event.pressed) {
eeconfig_init();
}
return false;
break;
}
return true;
}

uint32_t layer_state_set_user(uint32_t state) {

uint8_t layer = biton32(state);

ergodox_board_led_off();
ergodox_right_led_1_off();
ergodox_right_led_2_off();
ergodox_right_led_3_off();
switch (layer) {
case 1:
ergodox_right_led_1_on();
break;
case 2:
ergodox_right_led_2_on();
break;
case 3:
ergodox_right_led_3_on();
break;
case 4:
ergodox_right_led_1_on();
ergodox_right_led_2_on();
break;
case 5:
ergodox_right_led_1_on();
ergodox_right_led_3_on();
break;
case 6:
ergodox_right_led_2_on();
ergodox_right_led_3_on();
break;
case 7:
ergodox_right_led_1_on();
ergodox_right_led_2_on();
ergodox_right_led_3_on();
break;
default:
break;
}
return state;

};
