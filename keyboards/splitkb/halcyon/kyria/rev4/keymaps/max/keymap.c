// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _MEDIA,
    _NAVIGATION,
    _FUNCTION,
    _SYMBOLS,
    _NUMBERS,
    _ADJUST,
    _GAMING,
    _GAMNUM,
};

// clang-format off

// Aliases for readability
#define MED   LT(_MEDIA     , KC_TAB )
#define NAV   LT(_NAVIGATION, KC_SPC )
#define FUNC  LT(_FUNCTION  , KC_ENT )
#define SYM   LT(_SYMBOLS   , KC_ESC )
#define NUM   LT(_NUMBERS   , KC_BSPC)
#define ADJ   LT(_ADJUST    , KC_DEL )
#define QWERTY TO(_QWERTY)

#define GUIA LGUI_T(KC_A)
#define ALTS LALT_T(KC_S)
#define CTLD LCTL_T(KC_D)
#define SFTF LSFT_T(KC_F)
#define HYPG HYPR_T(KC_G)
#define HYPH HYPR_T(KC_H)
#define SFTJ LSFT_T(KC_J)
#define CTLK LCTL_T(KC_K)
#define ALTL LALT_T(KC_L)
#define GUIC LGUI_T(KC_SCLN)

#define LPAREN LSFT_T(KC_LBRC)
#define RPAREN LCTL_T(KC_RBRC)

#define GAMING TO(_GAMING)
#define GAMNUM TO(_GAMNUM)


// Last row is for hlc to work correctly. It is a 'mute' section.

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |   [ {  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |   ' "  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  | LEFTM|RIGHTM|  |      |      |   N  |   M  | ,  < | . >  | /  ? |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |MIDDLE| MEDIA| NAV  | FUNC |  | SYM  | NUM  | ADJ  |      | Menu |
 *                        |      |  M   | TAB  | Space| Enter|  | ESC  | BSP  | DEL  |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT_split_3x6_5_hlc(
     XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LCBR,
     XXXXXXX,    GUIA,    ALTS,    CTLD,    SFTF,    HYPG,                                               HYPH,    SFTJ,    CTLK,    ALTL,    GUIC, KC_QUOT,
     XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, MS_BTN1, MS_BTN2,        XXXXXXX, XXXXXXX,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
                                XXXXXXX, MS_BTN3,     MED,     NAV,    FUNC,            SYM,     NUM,     ADJ, XXXXXXX,  KC_APP,
     KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

/*
 * Media  Layer: Media
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      | PREV | NEXT |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  GUI |  Alt | Ctrl | Shift| HYPER|                              |      | NEXT | STOP |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      | VOL↓ | VOL↑ | MUTE |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_MEDIA] = LAYOUT_split_3x6_5_hlc(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                             XXXXXXX, KC_MPRV, KC_MNXT, XXXXXXX, XXXXXXX,  GAMING,
      XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_HYPR,                                             XXXXXXX, KC_MPLY, KC_MSTP, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
                                 XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX,         _______, _______, _______, XXXXXXX, XXXXXXX,
     KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

/*
 * Navigation Layer: Navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  GUI |  Alt | Ctrl | Shift| HYPER|                              |  ←   |   ↓  |   ↑  |   →  | CAPSW|        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      | Home |PgDown| PGUp |  End |Insert|        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAVIGATION] = LAYOUT_split_3x6_5_hlc(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_HYPR,                                             KC_LEFT, KC_DOWN, KC_RGHT,   KC_UP, CW_TOGG, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_INS, XXXXXXX,
                                 XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX,         _______, _______, _______, XXXXXXX, XXXXXXX,
     KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

/*
 * Function Layer: Function keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |  F7  |  F8  |  F9  |  F12 |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  GUI |  Alt | Ctrl | Shift| HYPER|                              |      |  F4  |  F5  |  F6  |  F11 |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |  F1  |  F2  |  F3  |  F10 |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FUNCTION] = LAYOUT_split_3x6_5_hlc(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                             XXXXXXX,    KC_7,   KC_F8,   KC_F9,  KC_F12, XXXXXXX,
      XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_HYPR,                                             XXXXXXX,   KC_F4,   KC_F5,   KC_F6,  KC_F11, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX,   KC_F1,   KC_F2,   KC_F3,  KC_F10, XXXXXXX,
                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,         _______, _______, _______, XXXXXXX, XXXXXXX,
     KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

/*
 * Symbol Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  {   |  &   |  *   |  (   |  }   |                              |      |  (   |  )   |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  "   |  $   |  %   |  ^   |  +   |                              | HYPER| [ SFT| ] CTL| ALT  | GUI  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  ~   |  !   |  @   |  #   |  |   |      |      |  |      |      |      |  {   |  }   |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |  (   |  )   |  _   |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYMBOLS] = LAYOUT_split_3x6_5_hlc(
      KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                                             XXXXXXX, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX, XXXXXXX,
     KC_TILD , KC_EXLM,  KC_AT , KC_HASH,  KC_DLR, KC_PERC,                                             KC_HYPR,  LPAREN,  RPAREN, KC_LPRN, KC_LALT, KC_LGUI,
     KC_PIPE , KC_BSLS, KC_COLN, KC_SCLN, KC_MINS, KC_LBRC, KC_LCBR, _______,         XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX,
                                 _______, _______, _______, _______, _______,         _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

/*
 * Number Layer: Numbers
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  [   |  7   |  8   |  9   |  ]   |                              |      |  (   |  )   |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  '   |  4   |  3   |  6   |  =   |                              | HYPER| [ SFT| ] CTL| ALT  | GUI  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  `   |  1   |  2   |  3   |  \   |      |      |  |      |      |      |  {   |  }   |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |  .   |  0   |  -   |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUMBERS] = LAYOUT_split_3x6_5_hlc(
      XXXXXXX, KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC,                                             XXXXXXX, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, KC_QUOT,    KC_4,    KC_5,    KC_6,  KC_EQL,                                             KC_HYPR,  LPAREN,  RPAREN, KC_LPRN, KC_LALT, KC_LGUI,
      XXXXXXX,  KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX,
                                 XXXXXXX, XXXXXXX,  KC_DOT,    KC_0, KC_MINS,         XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX,
     KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

/*
 * Adjust Layer: RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT_split_3x6_5_hlc(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      RM_SPDU, RM_NEXT, RM_VALU, RM_HUEU, RM_SATU, RM_TOGG,                                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      RM_SPDD, RM_PREV, RM_VALD, RM_HUED, RM_SATD, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX,
     KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

/*
 * Base Layer: Gaming, non home row mods.
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  TAB   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   ↑  |   O  |   P  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | L_SHIFT|   A  |   S  |   D  |   F  |   G  |                              |   H  |   ←  |   ↓  |   →  | ;  : |   ' "  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | L_CTRL |   Z  |   X  |   C  |   V  |   B  | KC_1 | KC_2 |  |      |      |   N  |   M  | ,  < | . >  | /  ? |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | ESC  | L_ALT|GAMNUM| Space| Enter|  | ESC  | BSP  | DEL  |      | Menu |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAMING] = LAYOUT_split_3x6_5_hlc(
      KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                               KC_Y,    KC_U,   KC_UP,    KC_O,    KC_P, KC_LCBR,
     KC_LSFT,    KC_A,    KC_A,    KC_D,    KC_F,    KC_G,                                               KC_H, KC_LEFT, KC_DOWN,KC_RIGHT, KC_SCLN, KC_QUOT,
     KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_1,    KC_2,        XXXXXXX, XXXXXXX,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
                                 KC_ESC, KC_LALT,  GAMNUM,  KC_SPC,  KC_ENT,         KC_ESC, KC_BSPC,  KC_DEL, XXXXXXX,  KC_APP,
     KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

/*
 * Number Layer: Gaming, less symbols more left side
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  [   |  7   |  8   |  9   |  ]   |                              |   Y  |   U  |   ↑  |   O  |   P  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  '   |  4   |  3   |  6   |  =   |                              |   H  |   ←  |   ↓  |   →  | ;  : |   ' "  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  `   |  1   |  2   |  3   |  \   |      |      |  |      |      |   N  |   M  | ,  < | . >  | /  ? |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |  .   |  0   |  -   |  | ESC  | BSP  | DEL  |      | Menu |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAMNUM] = LAYOUT_split_3x6_5_hlc(
      XXXXXXX, KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC,                                               KC_Y,    KC_U,   KC_UP,    KC_O,    KC_P,  QWERTY,
      XXXXXXX, KC_QUOT,    KC_4,    KC_5,    KC_6,  KC_EQL,                                               KC_H, KC_LEFT, KC_DOWN,KC_RIGHT, KC_SCLN, KC_QUOT,
      XXXXXXX,  KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
                                 XXXXXXX, XXXXXXX,  KC_DOT,    KC_0, KC_MINS,         KC_ESC, KC_BSPC,  KC_DEL, XXXXXXX,  KC_APP,
     KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT_split_3x6_5_hlc(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
//     ),
//
};

// clang-format on
