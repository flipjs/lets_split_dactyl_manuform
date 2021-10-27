// This is a version of let's Split with the modifier keys moved into the thumbcluster.
// I left the matrix configuration as is, modified this file only.
// (actually I had to specify ROW2COL since in my CrocoDox I put them in the opposit direction.

//#include "lets_split.h"
#include "lets_split_dactyl_manuform.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "keymap_steno.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _QWERTY 0
#define _CURSORRGHT 1
#define _CURSORLEFT 2
#define _NUMBERS 3
#define _EXTRARIGHT 4
#define _NUMPAD 16
#define _PLOVER 5
#define _STENO_TXBOLT 6
#define _STENO_TXBOLT2 7
//  these two layers are transparent ones intentionally.
//  When their respective switches are held together - the extra right will be initiated.
#define _DUMMY1 10
#define _DUMMY2 11


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  NUMPAD,
// These three wiil work as RAISE, LOWER  and ADJUST in the original PLANCK
  CURSORRGHT = LT(_CURSORRGHT,KC_SPC),
  CURSORLEFT = LT(_CURSORLEFT,KC_SPC),
  NUMBERS,
  PLOVER,
  EXT_PLV,

  STENO_TXBOLT,
  STENO_TXBOLT2,
  EXT_PLV2,

// These  pairs when held together - will turn on the EXTRA RIGHT layer,
// But will do nothing when held down by themselves.
// The single hit will still be their regular key.
  S_RT = LT(_DUMMY1, KC_S),
  D_RT = LT(_DUMMY2, KC_D)
};



// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty                                 
 * ,-----------------------------------------++-----------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  ||   Y  |   U  |   I  |   O  |   P  |BSpc  |
 * |------+------+------+------+------+------++------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  ||   H  |   J  |   K  |   L  |   ;  |Enter |
Hold:            |both-ExtraRgt|
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Ctrl |   Z  |   X  |   C  |   V  |   B  ||   N  |   M  |   ,  |   .  |   /  |RCtrl |
 * +------+------+------+------+------+------++------+------+------+------+------+------+
		 |  GUI | Alt  |      |      ||      |      | RAlt | Menu |
	         +------+------+      |      ||      |      +------+------+               
Hold:  		               | LSft |CursLt||CursRt| RSft |
Single hit:		       |   Space     ||    Space    |
		               +------+------||------+------+
      Here	               | LCtrl| LAlt || RAlt | RCtrl|                Here 
	^	               +------+------||------+------+                  ^
 	+------mapped------    | GUI  | Menu || Menu | GUI  |  -------mapped---+
This row is wired  	       +------+------||------+------+    
on the 5th row (R4), 
hence in the key map it is in the two outermost positions.

 */
[_QWERTY] = KEYMAP( \
  KC_ESC,  KC_Q,       KC_W,    KC_E,       KC_R,           KC_T,            KC_Y,       KC_U,           KC_I,     KC_O,    KC_P,    KC_BSPC, \
  KC_TAB,  KC_A,       S_RT,    D_RT,       KC_F,           KC_G,            KC_H,       KC_J,           KC_K,     KC_L,    KC_SCLN, KC_ENT , \
  KC_LCTL, KC_Z,       KC_X,    KC_C,       KC_V,           KC_B,            KC_N,       KC_M,           KC_COMM,  KC_DOT,  KC_SLSH, KC_RCTL, \
  _______, _______,    KC_LGUI, KC_LALT,    LSFT_T(KC_SPC), CURSORLEFT,      CURSORRGHT, RSFT_T(KC_SPC), KC_RALT,  KC_APP,  _______, _______, \
  KC_LGUI, KC_APP,     _______,   _______, KC_LCTL,        KC_LALT,         KC_RALT,    KC_RCTL,        _______,  _______, KC_APP,  KC_LGUI \
),



/*

Layers below are used on top of QWERTY layer defined above.
(Except the PLOVER/STENO layers.)
                                           +-------+
The keys which are shown empty, like this: |       |, represent a transparent key,
                                           +-------+
meaning the key from the underlaying layer (i.e. QWERTY) will be used.
In the keymaps those keys are defined as "_______".

                                           +-------+         +-------+
The keys which are shown solid, like this: | XXXXX | or this |  ...  |, represent an opaque/blocking key�
                                           +-------+         +-------+
Such key is not doing anything in that layer nor allowing the key from the underlaying layer
to be invoked.
In the keymaps those keys are defined as "XXXXXXX".

Most of the modifiers are the same in all layers.
So in most layers they are defined as transparent keys,
letting the keys from QWERTY layer to do the work.

With that idea all the layers below leave the unmodified keys as transparent keys.
In the same time - the layers block the keys that have no sense to be used 
in that given layer. For instance in the cursor control layers 
some of the keys are not used in the layer, but they are blocked to avoid
alpha-keys from QWERTY layer to appear.

For the same reason the keymaps below are shown simplified,
without separate thumbcluster.

*/



/* Cursor Control on the right (Right Space)
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |Break |WheelD|MousUp|WheelU| Del  |  Ins | Home |  Up  | End  |   `  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |SelAll|MousLt|MousDn|MousRt| ...  | PgUp | Left | Down |Right | ...  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | Undo | Cut  | Copy | Paste| ...  | PgDn |MsBtLe|MsBtMi|MsBtRt| ...  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |   X  |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_CURSORRGHT] = KEYMAP( \
  _______, KC_BRK,           KC_WH_D,      KC_MS_U,      KC_WH_U,      KC_DEL,              KC_INS,   KC_HOME, KC_UP,   KC_END,  KC_GRV,  KC_DEL,  \
  KC_ENT,  LCTL(KC_A),       KC_MS_L,      KC_MS_D,      KC_MS_R,      XXXXXXX,             KC_PGUP,  KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, _______, \
  _______, LCTL(KC_Z),       LSFT(KC_DEL), LCTL(KC_INS), LSFT(KC_INS), XXXXXXX,             KC_PGDN,  KC_BTN1, KC_BTN3, KC_BTN2, XXXXXXX, _______, \
  _______, _______,          _______,      _______,      _______,      _______,             _______,  _______, _______, _______, _______, _______, \
  _______, _______,          _______,      _______,      _______,      _______,             _______,  _______, _______, _______, _______, _______  \
),



 /* Cursor Control on the left (Left Space)
 * ,-----------------------------------------------------------------------------------.
 * |      |Break | Home |  Up  | End  |  Ins | Del  |WheelU|MousUp|WheelD|   `  | Del  |
 * |------+------+------+------+------+------+-------------+------+------+------+------|
 * | Enter|SelAll|Right | Down | Left | PgUp | xxx  |MousLt|MousDn|MousRt| xxx  |Enter |
 * |------+------+------+------+------+------+------|------+------+------+------+------|
 * |      | xxx  |MsBtRt|MsBtMi|MsBtLe| PgDn | xxx  | Cut  | Copy | Paste| xxx  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |   X  |	    |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_CURSORLEFT] = KEYMAP( \
  _______, KC_BRK,          KC_HOME, KC_UP,   KC_END,  KC_INS,        KC_DEL,  KC_WH_U,      KC_MS_U,      KC_WH_D,      KC_GRV,  KC_DEL , \
  KC_ENT,  LCTL(KC_A),      KC_LEFT, KC_DOWN, KC_RGHT, KC_PGUP,       XXXXXXX, KC_MS_L,      KC_MS_D,      KC_MS_R,      XXXXXXX, _______, \
  _______, XXXXXXX,         KC_BTN2, KC_BTN3, KC_BTN1, KC_PGDN,       XXXXXXX, LCTL(KC_DEL), LCTL(KC_INS), LSFT(KC_INS), XXXXXXX, _______, \
  _______, _______,         _______, _______, _______, _______,       _______, _______,      _______,      _______,      _______, _______, \
  _______, _______,         _______, _______, _______, _______,       _______, _______,      _______,      _______,      _______, _______  \

),


 /* Numbers on the home row, FNs on the top row, symbols in the second row
 * (Lower or Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |BackSp|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   F1 |   F2 |   F3 |   F4 |   F5 |   F6 |   F7 |   F8 |   F9 |   F10|      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F11 |  F12 | LAlt |LShift| LAlt | RAlt |RShift|   ,  |   .  |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMBERS] = KEYMAP( \
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, \
  _______, KC_F11,  KC_F12,  KC_LALT, KC_LSFT, KC_LALT, KC_RALT, KC_RSFT, KC_COMM, KC_DOT,  KC_SLSH, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

/* ExtraRightSide (the keys from the right side which did not fit into the matrix)
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   `  |PLOVR2|PLOVER|TxBOLT|TxBlt2|   `  |   =  |   (  |   )  |   -  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |CAPSLK|      |   ******    |      |      |      |      |      |      |  '   |      |
                   This is the
		  keys turning
                  this layer on
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |   [  |   ]  |  \   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_EXTRARIGHT] = KEYMAP( \
  _______, KC_GRV,  PLOVER,  PLOVER,  STENO_TXBOLT, STENO_TXBOLT2, KC_GRV,  KC_EQL,  KC_LPRN, KC_RPRN, KC_MINS, _______, \
  KC_CAPS, XXXXXXX, _______, _______, XXXXXXX,      XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_QUOT, _______, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,       XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS, _______, \
  _______, _______, _______, _______, _______,      _______,       _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,      _______,       _______, _______, _______, _______, _______, _______  \
 
),

// TODO: This layer is not working properly, I do not use it anyway. 
/* Numbers on the home row, and the right side turned into a numpad
 *
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |BackSp|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |   +  |   4  |   5  |   6  |   *  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |LShift| LAlt | RAlt |   1  |   2  |   3  |   \  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | Exit | Exit |      |   0  |   .  |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] =  KEYMAP( \
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,    _______, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PPLS,  KC_4,    KC_5,    KC_6,    KC_PAST, KC_PENT, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, KC_LALT, KC_RALT,  KC_1,    KC_2,    KC_3,    KC_PSLS, _______, \
  _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, QWERTY,  QWERTY,   _______, KC_0,    KC_DOT,  _______, _______ \
),

/* Plover layer (http://opensteno.org)
This layer remains on until EXIT key is pressed or the keyboard is reconnected.
No other layers/modifiers to be used with it - it is self-sufficient.
All other STENO/PLOVER layers defind below implement the same map with minor variances:
	- TX Bolt protocol over COM port is used instead of acting as a regular keyboard.
        - NumBar keys are moved below the alpha-keys.

 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | xxxx |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | xxxx |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * +------+------+------+------+------+------+------+------+------+------+------+------+
		 | xxxx | xxxx |      |      ||      |      | xxxx| xxx  |
	         +------+------+      |      ||      |      +-----+------+               
  		               |   A  |   O  ||   E  |   U  |
		               +------+------||------+------+
      Here	               | xxxx | xxxx || xxxx | xxxxx|                Here 
	^	               +------+------||------+------+                  ^
 	+------mapped------    | xxxx |EXIT  || EXIT | xxxx |  -------mapped---+
This row is wired  	       +------+------||------+------+    
on the 5th row (R4), 
hence in the key map it is in the two outermost positions.
 */

[_PLOVER] = KEYMAP( \
  KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   , \
  XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, \
  XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_C,    KC_V,    KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, EXT_PLV, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXT_PLV, XXXXXXX \
),

/* Plover Layer via TX Bolt interface.
   The layout is the same as for Plover above, just different key codes
*/

[_STENO_TXBOLT] = KEYMAP( \
   STN_NUM, STN_NUM, STN_NUM, STN_NUM, STN_NUM, STN_NUM,    STN_NUM, STN_NUM, STN_NUM, STN_NUM, STN_NUM, STN_NUM, \
   STN_SL,  STN_SL,  STN_TL,  STN_PL,  STN_HL,  STN_ST1,    STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR, \
   STN_SL,  STN_SL,  STN_KL,  STN_WL,  STN_RL,  STN_ST2,    STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR, \
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, STN_A,   STN_O,      STN_E,   STN_U,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
   XXXXXXX, EXT_PLV2,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXT_PLV2, XXXXXXX \
 ), 

/*  TX Bolt with the alpha rows moved up, numbar below them. 
*/
[_STENO_TXBOLT2] = KEYMAP( \
   STN_SL,  STN_SL,  STN_TL,  STN_PL,  STN_HL,  STN_ST1,    STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR, \
   STN_SL,  STN_SL,  STN_KL,  STN_WL,  STN_RL,  STN_ST2,    STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR, \
   STN_NUM, STN_NUM, STN_NUM, STN_NUM, STN_NUM, STN_NUM,    STN_NUM, STN_NUM, STN_NUM, STN_NUM, STN_NUM, STN_NUM, \
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, STN_A,   STN_O,      STN_E,   STN_U,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
   XXXXXXX, EXT_PLV2,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXT_PLV2, XXXXXXX \
 ), 

/* Dummy layers, both transparent, used to implement the extra right layer switch: S+D both held down.
*/

[_DUMMY1] = KEYMAP( \
  _______, _______,          _______,      _______,      _______,      _______,             _______,  _______, _______, _______, _______, _______, \
  _______, _______,          _______,      _______,      _______,      _______,             _______,  _______, _______, _______, _______, _______, \
  _______, _______,          _______,      _______,      _______,      _______,             _______,  _______, _______, _______, _______, _______, \
  _______, _______,          _______,      _______,      _______,      _______,             _______,  _______, _______, _______, _______, _______, \
  _______, _______,          _______,      _______,      _______,      _______,             _______,  _______, _______, _______, _______, _______  \
) 
,
[_DUMMY2] = KEYMAP( \
  _______, _______,          _______,      _______,      _______,      _______,             _______,  _______, _______, _______, _______, _______, \
  _______, _______,          _______,      _______,      _______,      _______,             _______,  _______, _______, _______, _______, _______, \
  _______, _______,          _______,      _______,      _______,      _______,             _______,  _______, _______, _______, _______, _______, \
  _______, _______,          _______,      _______,      _______,      _______,             _______,  _______, _______, _______, _______, _______, \
  _______, _______,          _______,      _______,      _______,      _______,             _______,  _______, _______, _______, _______, _______  \
) 


};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

void matrix_init_user() {
  steno_set_mode(STENO_MODE_BOLT); // or STENO_MODE_BOLT
}

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {

   case QWERTY:
      if (record->event.pressed) {
        layer_off(_CURSORRGHT);
        layer_off(_CURSORLEFT);
        layer_off(_NUMBERS);
        layer_off(_EXTRARIGHT);
        layer_off(_NUMPAD);
        layer_off(_PLOVER);
        layer_on(_QWERTY);

      }
      return false;
      break;


     case NUMPAD:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
	layer_invert(_QWERTY);
	layer_invert(_NUMPAD);
      }
      return false;
      break;

    case CURSORRGHT:
      if (record->event.pressed) {
        layer_on(_CURSORRGHT);
        update_tri_layer(_CURSORRGHT, _CURSORLEFT, _NUMBERS);
      } else {
        layer_off(_CURSORRGHT);
        update_tri_layer(_CURSORRGHT, _CURSORLEFT, _NUMBERS);
       }
      return true;// false;
      break;
    case CURSORLEFT:
      if (record->event.pressed) {
        layer_on(_CURSORLEFT);
        update_tri_layer(_CURSORRGHT, _CURSORLEFT, _NUMBERS);
      } else {
        layer_off(_CURSORLEFT);
        update_tri_layer(_CURSORRGHT, _CURSORLEFT, _NUMBERS);
      }
      return true;// 	false;
      break;



   case S_RT:
      if (record->event.pressed) {
        layer_on(_DUMMY1);
        update_tri_layer(_DUMMY1, _DUMMY2, _EXTRARIGHT);
      } else {
        layer_off(_DUMMY1);
        update_tri_layer(_DUMMY1, _DUMMY2, _EXTRARIGHT);
       }
      return true;// false;
      break;

   case D_RT:
      if (record->event.pressed) {
        layer_on(_DUMMY2);
        update_tri_layer(_DUMMY1, _DUMMY2, _EXTRARIGHT);
      } else {
        layer_off(_DUMMY2);
        update_tri_layer(_DUMMY1, _DUMMY2, _EXTRARIGHT);
       }
      return true;// false;
      break;




    case PLOVER:
      if (record->event.pressed) {
        layer_off(_QWERTY);
        layer_off(_CURSORRGHT);
        layer_off(_CURSORLEFT);
        layer_off(_NUMBERS);
        layer_off(_EXTRARIGHT);
        layer_off(_NUMPAD);
        layer_on(_PLOVER);
 
       if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;


     case EXT_PLV:
      if (record->event.pressed) {
        layer_off(_PLOVER);
        layer_on(_QWERTY);
      }
      return false;
      break;

    case STENO_TXBOLT:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_NOTE_ARRAY(tone_plover, false, 0);
        #endif
        layer_off(_CURSORRGHT);
        layer_off(_CURSORLEFT);
        layer_off(_NUMBERS);
        layer_off(_EXTRARIGHT);
        layer_off(_NUMPAD);
        layer_off(_PLOVER);
        layer_off(_STENO_TXBOLT2);
        layer_on(_STENO_TXBOLT);
       if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;

    case STENO_TXBOLT2:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_NOTE_ARRAY(tone_plover, false, 0);
        #endif
        layer_off(_CURSORRGHT);
        layer_off(_CURSORLEFT);
        layer_off(_NUMBERS);
        layer_off(_EXTRARIGHT);
        layer_off(_NUMPAD);
        layer_off(_PLOVER);
        layer_off(_STENO_TXBOLT);
        layer_on(_STENO_TXBOLT2);
       if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;

     case EXT_PLV2:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_plover_gb, false, 0);
        #endif
        layer_off(_STENO_TXBOLT);
        layer_off(_STENO_TXBOLT2);
        layer_on(_QWERTY);
      }
      return false;
      break;

 }
  return true;
}
 
