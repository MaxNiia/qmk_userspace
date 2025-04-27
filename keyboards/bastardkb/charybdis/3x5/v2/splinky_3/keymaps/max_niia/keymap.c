#include <stdint.h>
#include "keycodes.h"
#include QMK_KEYBOARD_H

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_FUNCTION,
    LAYER_NAVIGATION,
    LAYER_MEDIA,
    LAYER_POINTER,
    LAYER_NUMERAL,
    LAYER_SYMBOLS,
    LAYER_GAMING,
    LAYER_GAMNUM,
    LAYER_GAMFUN,
};

// Automatically enable sniping-mode on the pointer layer.
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define TAB_MED LT(LAYER_MEDIA, KC_TAB)
#define SPC_NAV LT(LAYER_NAVIGATION, KC_SPC)
#define ENT_FUN LT(LAYER_FUNCTION, KC_ENT)
#define ESC_SYM LT(LAYER_SYMBOLS, KC_ESC)
#define BSP_NUM LT(LAYER_NUMERAL, KC_BSPC)

#define BASE TO(LAYER_BASE)
#define _L_PTR(KC) LT(LAYER_POINTER, KC)
#define LPAREN RSFT_T(KC_LBRC)
#define RPAREN RCTL_T(KC_RBRC)
#define GAMING TO(LAYER_GAMING)
#define GAMNUM TO(LAYER_GAMNUM)
#define GAMFUN TO(LAYER_GAMFUN)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_O
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off

/** Convenience row shorthands. */
#define _______________DEAD_HALF_ROW_______________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ______________HOME_ROW_GACS_L______________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_MEH
#define ______________HOME_ROW_GACS_R______________  KC_MEH, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI

/** \brief QWERTY layout (3 rows, 10 columns). */
#define LAYOUT_LAYER_BASE                                                                         \
       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, \
       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, \
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, \
                      TAB_MED, SPC_NAV, ENT_FUN,     ESC_SYM, BSP_NUM

/** \brief Mouse emulation and pointer functions. */
#define LAYOUT_LAYER_POINTER                                                                      \
    XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD,     S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX, \
    ______________HOME_ROW_GACS_L______________,     ______________HOME_ROW_GACS_R______________, \
    _______, DRGSCRL, SNIPING, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, SNIPING, DRGSCRL, _______, \
                      KC_BTN2, KC_BTN1, KC_BTN3,     KC_BTN3, KC_BTN1

/**
 * \brief Media layer.
 *
 * Tertiary left- and right-hand layer is media and RGB control.  This layer is
 * symmetrical to accommodate the left- and right-hand trackball.
 */
#define LAYOUT_LAYER_MEDIA                                                                        \
   RGB_RMOD, RGB_MOD, RGB_TOG, RGB_HUI, RGB_HUD,     RGB_SAI, RGB_SAD, XXXXXXX, XXXXXXX,  GAMING, \
    KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT,     KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT, \
    RGB_VAI, RGB_VAD, XXXXXXX, XXXXXXX,   NK_ON,     QK_BOOT, EE_CLR,  XXXXXXX, RGB_SPI, RGB_SPD, \
                      _______, KC_MPLY, KC_MSTP,     KC_MSTP, KC_MPLY

/**
 * \brief Navigation layer.
 *
 * Primary right-hand layer (left home thumb) is navigation and editing. Cursor
 * keys are on the home position, line and page movement below, clipboard above,
 * caps lock and insert on the inner column. Thumb keys are duplicated from the
 * base layer to avoid having to layer change mid edit and to enable auto-repeat.
 */
#define LAYOUT_LAYER_NAVIGATION                                                                   \
    _______________DEAD_HALF_ROW_______________,     _______________DEAD_HALF_ROW_______________, \
    ______________HOME_ROW_GACS_L______________,     KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, CW_TOGG, \
    _______________DEAD_HALF_ROW_______________,     KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_INS, \
                      XXXXXXX, _______, XXXXXXX,      KC_ESC,  KC_DEL

/**
 * \brief Function layer.
 *
 * Secondary right-hand layer has function keys mirroring the numerals on the
 * primary layer with extras on the pinkie column, plus system keys on the inner
 * column. App is on the tertiary thumb key and other thumb keys are duplicated
 * from the base layer to enable auto-repeat.
 */
#define LAYOUT_LAYER_FUNCTION                                                                     \
    _______________DEAD_HALF_ROW_______________,     KC_PSCR,   KC_F7,   KC_F8,   KC_F9,  KC_F12, \
    ______________HOME_ROW_GACS_L______________,     KC_SCRL,   KC_F4,   KC_F5,   KC_F6,  KC_F11, \
    _______________DEAD_HALF_ROW_______________,     KC_PAUS,   KC_F1,   KC_F2,   KC_F3,  KC_F10, \
                      XXXXXXX, XXXXXXX, _______,      KC_ESC,  KC_DEL
/**
 * \brief Symbols layer.
 *
 * Secondary left-hand layer has shifted symbols in the same locations to reduce
 * chording when using mods with shifted symbols. `KC_LPRN` is duplicated next to
 * `KC_RPRN`.
 */
#define LAYOUT_LAYER_SYMBOLS                                                                      \
    KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,     XXXXXXX, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX, \
    KC_COLN,  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS,     XXXXXXX,  LPAREN,  RPAREN, KC_LALT, KC_RGUI, \
    KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_PIPE,     XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX, \
                      KC_LPRN, KC_RPRN, KC_UNDS,     _______, XXXXXXX

/**
 * \brief Numeral layout.
 *
 * Primary left-hand layer (right home thumb) is numerals and symbols. Numerals
 * are in the standard numpad locations with symbols in the remaining positions.
 * `KC_DOT` is duplicated from the base layer.
 */
#define LAYOUT_LAYER_NUMERAL                                                                      \
    KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC,     XXXXXXX, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX, \
    KC_SCLN,    KC_4,    KC_5,    KC_6,  KC_EQL,     XXXXXXX,  LPAREN,  RPAREN, KC_LALT, KC_RGUI, \
     KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS,     XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX, \
                       KC_DOT,    KC_0, KC_MINS,     XXXXXXX, _______


#define LAYOUT_LAYER_GAMING_BASE                                                                  \
       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, \
       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, \
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, \
                       GAMNUM,  KC_SPC,  GAMFUN,      KC_ENT, KC_BSPC

#define LAYOUT_LAYER_GAMING_NUMBER                                                                \
    KC_LALT,    KC_7,    KC_8,    KC_9,  KC_GRV,       KC_Y,    KC_U,    KC_I,    KC_O,    BASE, \
    KC_LSFT,    KC_4,    KC_5,    KC_6,  KC_EQL,       KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, \
    KC_LCTL,    KC_1,    KC_2,    KC_3, KC_BSLS,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, \
                       GAMING,    KC_0, KC_MINS,     KC_ENT, KC_BSPC

#define LAYOUT_LAYER_GAMING_FUNCTION                                                              \
    KC_LALT,   KC_F7,   KC_F8,   KC_F9,  KC_F12,       KC_Y,    KC_U,    KC_I,    KC_O,    BASE, \
    KC_LSFT,   KC_F4,   KC_F5,   KC_F6,  KC_F11,       KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, \
    KC_LCTL,   KC_F1,   KC_F2,   KC_F3,  KC_F10,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, \
                       GAMING,  KC_SPC,  GAMING,     KC_ENT, KC_BSPC

/**
 * \brief Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for GACS (Gui, Alt, Ctl, Shift)
 * home row.  The layout passed in parameter must contain at least 20 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     HOME_ROW_MOD_GACS(LAYER_ALPHAS_QWERTY)
 */
#define _HOME_ROW_MOD_GACS(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
      LGUI_T(L10), LALT_T(L11), LCTL_T(L12), LSFT_T(L13), MEH_T(L14),  \
      MEH_T(R15),  RSFT_T(R16), RCTL_T(R17), LALT_T(R18), RGUI_T(R19), \
      __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

#define _HALF_HOME_ROW_MOD_GACS(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
             L10,         L11,         L12,         L13,         L14,  \
      MEH_T(R15),  RSFT_T(R16), RCTL_T(R17), LALT_T(R18), RGUI_T(R19), \
      __VA_ARGS__
#define HALF_HOME_ROW_MOD_GACS(...) _HALF_HOME_ROW_MOD_GACS(__VA_ARGS__)

/**
 * \brief Add pointer layer keys to a layout.
 *
 * Expects a 10-key per row layout.  The layout passed in parameter must contain
 * at least 30 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     POINTER_MOD(LAYER_ALPHAS_QWERTY)
 */
#define _POINTER_MOD(                                                  \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
             L10,         L11,         L12,         L13,         L14,  \
             R15,         R16,         R17,         R18,         R19,  \
      _L_PTR(L20),        L21,         L22,         L23,         L24,  \
             R25,         R26,         R27,         R28,  _L_PTR(R29), \
      __VA_ARGS__
#define POINTER_MOD(...) _POINTER_MOD(__VA_ARGS__)

#define _HALF_POINTER_MOD(                                             \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
             L10,         L11,         L12,         L13,         L14,  \
             R15,         R16,         R17,         R18,         R19,  \
             L20,         L21,         L22,         L23,         L24,  \
             R25,         R26,         R27,         R28,  _L_PTR(R29), \
      __VA_ARGS__
#define HALF_POINTER_MOD(...) _HALF_POINTER_MOD(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(
    POINTER_MOD(HOME_ROW_MOD_GACS(LAYOUT_LAYER_BASE))
  ),
  [LAYER_FUNCTION] = LAYOUT_wrapper(LAYOUT_LAYER_FUNCTION),
  [LAYER_NAVIGATION] = LAYOUT_wrapper(LAYOUT_LAYER_NAVIGATION),
  [LAYER_MEDIA] = LAYOUT_wrapper(LAYOUT_LAYER_MEDIA),
  [LAYER_NUMERAL] = LAYOUT_wrapper(LAYOUT_LAYER_NUMERAL),
  [LAYER_POINTER] = LAYOUT_wrapper(LAYOUT_LAYER_POINTER),
  [LAYER_SYMBOLS] = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
  [LAYER_GAMING] = LAYOUT_wrapper(HALF_POINTER_MOD(HALF_HOME_ROW_MOD_GACS(LAYOUT_LAYER_GAMING_BASE))),
  [LAYER_GAMNUM] = LAYOUT_wrapper(LAYOUT_LAYER_GAMING_NUMBER),
  [LAYER_GAMFUN] = LAYOUT_wrapper(LAYOUT_LAYER_GAMING_FUNCTION),
};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R',
        '*', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', '*',
                  '*', '*', '*',   '*', '*'
    );
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in
// rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif
