#include QMK_KEYBOARD_H

// GUI + esc = `
const key_override_t grave_esc_override = ko_make_basic(MOD_MASK_ALT, KC_GESC, KC_GRV);

const key_override_t **key_overrides = (const key_override_t *[]){
    &grave_esc_override,
    NULL // Null terminate the array of overrides!
};

/* THIS FILE WAS GENERATED!
 *
 * This file was generated by qmk json2c. You may or may not want to
 * edit it directly.
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_65_ansi(KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_HOME, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP, TT(1), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGDN, OSM(MOD_LSFT), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, OSM(MOD_RSFT), KC_UP, KC_END, KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RALT, KC_ENT, TO(1), KC_LEFT, KC_DOWN, KC_RGHT),
  [1] = LAYOUT_65_ansi(KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LGUI(KC_UP), KC_TRNS, KC_TRNS, KC_TRNS, LSA(KC_LEFT), LSA(KC_RGHT), KC_TRNS, KC_TRNS, TO(0), KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, LGUI(KC_LEFT), LGUI(KC_DOWN), LGUI(KC_RGHT), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_SPD, RGB_SPI, RGB_RMOD, RGB_MOD, RGB_TOG, KC_TRNS, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_VOLD, KC_MNXT)
};

/**
 * Change ctl+backspace into delete and do not register the alt modifier.
 */
static bool control_disabled = false;
static bool delete_pressed = false;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  if(keycode == KC_BSPC) {
    if (record->event.pressed) {
      if(keyboard_report->mods & MOD_BIT(KC_LCTL)) {
        delete_pressed = true;
        control_disabled = true;
        unregister_code(KC_LCTL);
        register_code(KC_DEL);
        return false;
      }
    } else if(delete_pressed) {
      delete_pressed = false;
      unregister_code(KC_DEL);

      if(control_disabled) {
        control_disabled = false;
        register_code(KC_LCTL);
      }
      return false;
    }
  } else if(keycode == KC_LCTL && !record->event.pressed && delete_pressed) {
    delete_pressed = false;
    control_disabled = false;
    unregister_code(KC_DEL);
    register_code(KC_BSPC);
    return false;
  }
  return true;
}
