/* Copyright 2017 Wunder
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// Windows 11 Desktop Management
#define X_CAL_L LCA(KC_LEFT)
#define X_CAL_R LCA(KC_RGHT)
#define X_TAB_L LCTL(KC_PGUP)
#define X_TAB_R LCTL(KC_PGDN)
#define XDESK_L LCTL(LGUI(KC_LEFT))
#define XDESK_R LCTL(LGUI(KC_RGHT))
#define XNXTMON LSG(KC_LEFT)
#define XDELDSK LCTL(LGUI(KC_F4))
#define XNEWDSK LCTL(LGUI(KC_D))
#define XGUIUP  LGUI(KC_UP)
// #define XGUIDWN LGUI(KC_DOWN)
#define XGUILFT LGUI(KC_LEFT)
#define XGUIRGT LGUI(KC_RGHT)


enum layer_names {
    _QW,
    _FN,
    _MP,
    _MD,
    _KB,
    _PL,
};

enum custom_keycodes {
    LAYER = SAFE_RANGE,
    PLOVER,
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LAYER:
            if (record->event.pressed) {
                layer_move(_FN);
            } else {
				if (layer_state_is(_FN)) {
					layer_clear();
				}
            }
            break;
        case PLOVER:
            if (record->event.pressed) {
                if (layer_state_is(_PL)) {
                    // ps for plover stop
                    // caught using sxhkd: super + ctrl + alt + shift + F12; ctrl+p; ctrl+s
                    SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT(SS_LSFT(SS_TAP(X_F12))))) SS_LCTL("ps"));
                    layer_clear();
                } else {
                    // pr for plover resume
                    // caught using sxhkd: super + ctrl + alt + shift + F12; ctrl+p; ctrl+r
                    SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT(SS_LSFT(SS_TAP(X_F12))))) SS_LCTL("pr"));
                    layer_move(_PL);
                }
            } else {
            }
            break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* QWERTY
     * .--------------------------------------------------------------------------------------------------------------------------------------.
     * | ESC    | 1      | 2      | 3      | 4      | 5      | HOME   | DEL    | END    | 6      | 7      | 8      | 9      | 0      | BACKSP |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * | TAB    | Q      | W      | E      | R      | T      | `      | PG UP  | \      | Y      | U      | I      | O      | P      | '      |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
     * | LCTRL  | A      | S      | D      | F      | G      | [      | PG DN  | ]      | H      | J      | K      | L      | ;      | ENTER  |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
     * | LSHIFT | Z      | X      | C      | V      | B      | -      | UP     | =      | N      | M      | ,      | .      | /      | RSHIFT |
     * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
     * | LGUI   | LCTRL  | LGUI   | LALT   | LAYER  | SPACE  | LEFT   | DOWN   | RIGHT  | BACKSP | MO(SM) | DEL    | RALT   | RGUI   | RCTRL  |
     * '--------------------------------------------------------------------------------------------------------------------------------------'
     */

    [_QW] = LAYOUT_ortho_5x15(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_HOME, KC_DEL,  KC_END,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_GRV,  KC_PGUP, KC_BSLS, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC, KC_PGDN, KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MINS, KC_UP,   KC_EQL,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LGUI, KC_LCTL, KC_LGUI, KC_LALT, LAYER,   KC_SPC,  KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, LAYER,   KC_DEL,  KC_RALT, KC_RGUI, KC_RCTL
    ),


    /* FUNCTIONS
     * .--------------------------------------------------------------------------------------------------------------------------------------.
     * | ESC    | F1     | F2     | F3     | F4     | F5     | F6     |        | F7     | F8     | F9     | F10    | F11    | F12    | BACKSP |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * |        |        |        | TO(KB) | TO(MD) |        |        |        |        | HOME   | PG DN  | PG UP  | END    |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
     * |        |        | TO(MP) |        |        |        |        |        |        | LEFT   | DOWN   | UP     | RIGHT  |        | ENTER  |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------|
     * |        |        |        |        |        |        |        |        |        |        | APP    | INSERT |        |        |        |
     * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
     * |        |        |        |        | LAYER  |        |        |        |        |        | LAYER  |        |        |        |        |
     * '--------------------------------------------------------------------------------------------------------------------------------------'
     */

    [_FN] = LAYOUT_ortho_5x15(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_BSPC,
		_______, _______, _______, TO(_KB), TO(_MD), KC_PERC, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
		_______, _______, TO(_MP), _______, _______, KC_CIRC, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, KC_ENT,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_APP,  KC_INS,  _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
	),


    /* MACROPAD
     * .--------------------------------------------------------------------------------------------------------------------------------------.
     * | ESC    | 1      | 2      | 3      | 4      | 5      | NUM LK | /      | *      | 6      | 7      | 8      | 9      | 0      | CALC   |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * | TAB    | CAL L  |        | CAL R  | DEL DSK|        | 7      | 8      | 9      | -      |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
     * |        | L DESK | NXTMON | R DESK | NEW DSK|        | 4      | 5      | 6      | +      | ENTER  |        |        |        | ENTER  |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
     * |        | G LEFT | G UP   | G RGHT |        |        | 1      | 2      | 3      | =      |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
     * |        |        |        |        | LAYER  |        | 0      | .      | .      |        | LAYER  |        |        |        |        |
     * '--------------------------------------------------------------------------------------------------------------------------------------'
     */

    [_MP] = LAYOUT(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_NUM,  KC_PSLS, KC_PAST, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_CALC,
        _______, X_CAL_L, X_CAL_R, X_TAB_L, X_TAB_R, XXXXXXX, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, XDESK_L, XNXTMON, XDESK_R, XXXXXXX, XXXXXXX, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, KC_PENT, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, XGUILFT, XGUIUP,  XGUIRGT, XDELDSK, XNEWDSK, KC_P1,   KC_P2,   KC_P3,   KC_PEQL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, _______, _______, KC_P0,   KC_PDOT, KC_PDOT, _______, _______, _______, _______, _______, _______
    ),


    /* MEDIA
    * .--------------------------------------------------------------------------------------------------------------------------------------.
    * | ESC    |        |        |        |        |        | SLEEP  | POWER  | BOOT   |        | MS WH L|MS CLK M|MS WH R |        | CALC   |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
    * |        | VOL DN | MUTE   | VOL UP |        |        | CAP LK | NUM LK | SCR LK | MS WH U|MS CLK L| MS UP  |MS CLK R|        |        |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
    * |        | PREV   | PLAY   | NEXT   | PR SCR |        |        |        | PAUSE  | MS WH D| MS LEFT| MS DOWN|MS RIGHT|        |        |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
    * |        |        | BRI DN | BRI UP |        |        |        |        |        |        |        |        |        |        |        |
    * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
    * |        |        |        |        | LAYER  |        |        |        |        |        | LAYER  |        |        |        |        |
    * '--------------------------------------------------------------------------------------------------------------------------------------'
    */

    [_MD] = LAYOUT(
        KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SLEP, KC_PWR,  QK_BOOT, XXXXXXX, KC_WH_L, KC_BTN3, KC_WH_R, XXXXXXX, KC_CALC,
        XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX, KC_CAPS, KC_NUM,  KC_SCRL, KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, KC_PSCR, XXXXXXX, XXXXXXX, XXXXXXX, KC_PAUS, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),


    /* KEYBOARD RGB
    * .--------------------------------------------------------------------------------------------------------------------------------------.
    * | ESC    | PLAIN  | BREATH |RAINBOW | SWIRL  | SNAKE  | KNIGHT | XMAS   | GRAD   | TEST   |        |        |        |        |        |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
    * |        |        |        |        |        |        | TOGGLE | MODE - | MODE + |        |        |        |        |        |        |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
    * |        |        |        |        |        | HUE +  | SAT +  | VALU + | SPD +  |        |        |        |        |        |        |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
    * |        |        |        |        |        | HUE -  | SAT -  | VALU - | SPD -  |        |        |        |        |        |        |
    * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
    * |        |        |        |        | LAYER  |        |        |        |        |        | LAYER  |        |        |        |        |
    * '--------------------------------------------------------------------------------------------------------------------------------------'
    */

    [_KB] = LAYOUT(
        KC_ESC,  RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW,RGB_M_SN,RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, RGB_RMOD,RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),


    // /* PLOVER
    // * .--------------------------------------------------------------------------------------------------------------------------------------.
    // * | ESC    | 1      | 2      | 3      | 4      | 5      | `      | PG UP  | \      | 6      | 7      | 8      | 9      | 0      | BACKSP |
    // * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
    // * | TAB    | Q      | W      | E      | R      | T      | [      | PG DN  | ]      | Y      | U      | I      | O      | P      | [      |
    // * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
    // * |        | A      | S      | D      | F      | G      | HOME   | UP     | END    | H      | J      | K      | L      | ;      | '      |
    // * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
    // * |        | Z      | X      | C      | V      | B      | LEFT   | DOWN   | RIGHT  | N      | M      | ,      | .      | /      |        |
    // * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
    // * |        |        |        |        | C      | V      | SPACE  | PLOVER | BACKSP | N      | M      | ENTER  |        |        |        |
    // * '--------------------------------------------------------------------------------------------------------------------------------------'
    // */
    //
    // [_PL] = LAYOUT(
    //     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_GRV,  KC_PGUP, KC_BSLS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    //     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_PGDN, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    //     _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME, KC_UP,   KC_END,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    //     _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LEFT, KC_DOWN, KC_RGHT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,
    //     _______, _______, _______, _______, KC_C,    KC_V,    KC_SPC,  PLOVER,  KC_BSPC, KC_N,    KC_M,    KC_ENT,  _______, _______, _______
    // ),

};

