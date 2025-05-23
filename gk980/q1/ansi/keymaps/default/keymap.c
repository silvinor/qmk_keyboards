// Copyright 2023 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_all(
         KC_ESC,              KC_F1,    KC_F2,    KC_F3,    KC_F4,       KC_F5,     KC_F6,     KC_F7,    KC_F8,     KC_F9,    KC_F10,   KC_F11,       KC_F12,    KC_MUTE,  KC_SCRL,  KC_PAUS, KC_HOME,   KC_END,
         KC_GRV,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,        KC_6,     KC_7,       KC_8,     KC_9,      KC_0,   KC_MINS,   KC_EQL,      KC_BSPC,               KC_NUM,  KC_PSLS, KC_PAST,  KC_PMNS,
         KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,        KC_Y,     KC_U,       KC_I,     KC_O,      KC_P,   KC_LBRC,  KC_RBRC,      KC_BSLS,                KC_P7,    KC_P8,   KC_P9,  KC_PPLS,
        KC_CAPS,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,        KC_H,     KC_J,       KC_K,     KC_L,   KC_SCLN,   KC_QUOT,                 KC_ENT,                KC_P4,    KC_P5,   KC_P6,
        KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,        KC_N,     KC_M,    KC_COMM,   KC_DOT,   KC_SLSH,                           KC_RSFT,      KC_UP,    KC_P1,    KC_P2,   KC_P3,  KC_PENT,
        KC_LCTL,  KC_LGUI,  KC_LALT,             KC_SPC,   KC_SPC,                 KC_SPC,             KC_RALT,     MO(1),   KC_MENU,                KC_LEFT,    KC_DOWN,  KC_RGHT,    KC_P0,  KC_PDOT
    ),

    [1] = LAYOUT_all(
        _______,             KC_F14,   KC_F15, G(KC_TAB),  KC_WSCH,  G(C(KC_S)),   KC_SLEP,   KC_MPRV,  KC_MPLY,   KC_MNXT,   KC_MUTE,  KC_VOLD,     KC_VOLU,   G(KC_SPC), RCS(KC_SPC), G(RCS(KC_4)), KC_PGUP, KC_PGDN,
        _______,  _______,  _______,  _______,   _______,  _______,     _______,   _______,   _______,  _______,   RM_TOGG,   RM_PREV,  RM_NEXT,      KC_DEL,                   KC_NUM,      KC_PSLS, KC_PAST, KC_PMNS,
        _______,  _______,  _______,  _______,   _______,  _______,     _______,   _______,   _______,  _______,   _______,   _______,  _______,     _______,                    KC_P7,        KC_P8,   KC_P9, KC_PPLS,
        _______,  _______,  _______,  _______,   _______,  _______,     _______,   _______,   _______,  _______,   _______,   _______,               _______,                    KC_P4,        KC_P5,   KC_P6,
        _______,  _______,  _______,  _______,   _______,  _______,     _______,   _______,   _______,  _______,   _______,                          _______,   RM_VALU,         KC_P1,        KC_P2,   KC_P3, KC_PENT,
        _______,  _______,  _______,             _______,  _______,                _______,             _______,   _______,   _______,               RM_SPDD,   RM_VALD,       RM_SPDU,          KC_P0, KC_PDOT
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(RM_HUED, RM_HUEU), ENCODER_CCW_CW(RM_SPDD, RM_SPDU), ENCODER_CCW_CW(C(MS_WHLD), C(MS_WHLU))},
    [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(RM_HUED, RM_HUEU), ENCODER_CCW_CW(RM_SPDD, RM_SPDU), ENCODER_CCW_CW(C(MS_WHLD), C(MS_WHLU))}
};
#endif

