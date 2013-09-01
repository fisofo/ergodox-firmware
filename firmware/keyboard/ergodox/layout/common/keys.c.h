/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * This file implements and extends the definitions in ".../lib/layout/keys.h"
 * and extends the definitions in ".../lib/layout/key-functions.h"
 *
 * Meant to be included *only* by the layout using it.
 */

// TODO: write a chordmak (or asetniop) layout, on top of a standard colemak
// layout, using chained sticky keys for the modifiers

// TODO: write tutorials
// - about
//   - basic key functions
//     - mention where people should look for more information; probably, the
//       usb, key_functions, and keys headers; and others?
//   - sticky keys
//   - macros
//   - chorded keys
//   - timed keys
//   - automatic repetition of utf-8 sequence keys
//   - layers
//   - making layouts
//   - changing the meaning of the LEDs
// - put the tutorials in the readme.md of
//   ".../firmware/keyboard/ergodox/layout"

#ifndef ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__COMMON__KEYS__C__H
#define ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__COMMON__KEYS__C__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include "./definitions.h"

// ----------------------------------------------------------------------------

/**                                            macros/KEYS__DEFAULT/description
 * Define the functions for a default key (i.e. a normal key that presses and
 * releases a keycode as you'd expect)
 *
 * Needed by ".../lib/layout/keys.h"
 */
#define  KEYS__DEFAULT(name, value)             \
    void P(name) (void) { KF(press)(value); }   \
    void R(name) (void) { KF(release)(value); }

/**                                            macros/KEYS__SHIFTED/description
 * Define the functions for a "shifted" key (i.e. a key that sends a "shift"
 * along with the keycode)
 *
 * Needed by ".../lib/layout/keys.h"
 */
#define  KEYS__SHIFTED(name, value)                             \
    void P(name) (void) { KF(press)(KEYBOARD__LeftShift);       \
                          KF(press)(value); }                   \
    void R(name) (void) { KF(release)(value);                   \
                          KF(release)(KEYBOARD__LeftShift); }

/**                                    macros/KEYS__LAYER__PUSH_POP/description
 * Define the functions for a layer push-pop key (i.e. a layer shift key).
 *
 * Naming Convention:
 * - Example: In the name `lpupo1l1`, we have the following:
 *     - `l`  : this is a layer key
 *     - `pu` : it pushes the layer element onto the stack on "press"
 *     - `po` : it pops the layer element out of the stack on "release"
 *     - `1`  : it pushes and pops the layer element with `layer_id` = 1
 *     - `l`  : (separate the `layer_id` from the `layer_number`)
 *     - `1`  : it pushes a layer element with `layer_number` = 1
 *
 * - The first and second number do not have to be the same (that is, the
 *   `layer_id` and `layer_number` can be different; there may be situations
 *   where you want or need this).
 *
 * - Only one of `pu` or `po` is necessary.  A key with only `pu` should *only*
 *   push the layer onto the stack, not pop anything out of it.  A key with
 *   only `po` should *only* pop the layer out of the stack.
 *
 * - If the function *only* pops the layer-element, the `layer_number` is not
 *   important: layers are popped based only on their `layer_id`.
 *
 * Notes:
 * - To save space, if you define a push-pop function, the push (only) and pop
 *   (only) functions may be defined as follows (using the example `lpupo1l1`
 *   from above):
 *
 *       #define  keys__press__lpu1l1    P(lpupo1l1)
 *       #define  keys__release__lpu1l1  KF(nop)
 *       #define  keys__press__lpo1l1    R(lpupo1l1)
 *       #define  keys__release__lpo1l1  KF(nop)
 */
#define  KEYS__LAYER__PUSH_POP(ID, LAYER)                                   \
    void P(lpupo##ID##l##LAYER) (void) { layer_stack__push(0, ID, LAYER);   \
                                         _flags.tick_keypresses = false; }  \
    void R(lpupo##ID##l##LAYER) (void) { layer_stack__pop_id(ID);           \
                                         _flags.tick_keypresses = false; }

/**                               macros/(group) layer : number pad/description
 * Define functions for pushing and popping the number pad (namely `numPush`,
 * `numPop`, and `numPuPo`)
 *
 * Members:
 * - `KEYS__LAYER__NUM_PU_PO`
 * - `KEYS__LAYER__NUM_PUSH`
 * - `KEYS__LAYER__NUM_POP`
 *
 * These macros are meant to be used (if necessary) in the layout file, since
 * they need to know the layer on which the number pad has been placed.
 */
#define  KEYS__LAYER__NUM_PU_PO(ID, LAYER)                              \
    void P(numPuPo) (void) { layer_stack__push(0, ID, LAYER);           \
                             KF(press)(KEYBOARD__LockingNumLock);       \
                             usb__kb__send_report();                    \
                             KF(release)(KEYBOARD__LockingNumLock);     \
                             usb__kb__send_report();                    \
                             _flags.tick_keypresses = false; }          \
    void R(numPuPo) (void) { layer_stack__pop_id(ID);                   \
                             KF(press)(KEYBOARD__LockingNumLock);       \
                             usb__kb__send_report();                    \
                             KF(release)(KEYBOARD__LockingNumLock);     \
                             usb__kb__send_report();                    \
                             _flags.tick_keypresses = false; }

#define  KEYS__LAYER__NUM_PUSH(ID, LAYER)                               \
    void P(numPush) (void) { layer_stack__push(0, ID, LAYER);           \
                             KF(press)(KEYBOARD__LockingNumLock);       \
                             _flags.tick_keypresses = false; }          \
    void R(numPush) (void) { KF(release)(KEYBOARD__LockingNumLock);     \
                             _flags.tick_keypresses = false; }

#define  KEYS__LAYER__NUM_POP(ID)                                       \
    void P(numPop) (void) { layer_stack__pop_id(ID);                    \
                            KF(press)(KEYBOARD__LockingNumLock);        \
                            _flags.tick_keypresses = false; }           \
    void R(numPop) (void) { KF(release)(KEYBOARD__LockingNumLock);      \
                            _flags.tick_keypresses = false; }

// ----------------------------------------------------------------------------

/**                                       functions/KF(2_keys_caps)/description
 * Press the given keycode, and also press "capslock" if this is the second
 * consecutive time this function has been called with `pressed == true`.
 *
 * Meant to be used with the left and right "shift" keys.
 */
void KF(2_keys_capslock)(bool pressed, uint8_t keycode) {
    static uint8_t counter = 0;
    if (pressed) {
        counter++;
        KF(press)(keycode);
    }
    if (counter == 2 && pressed) {
        KF(toggle_capslock)();
    }
    if (!pressed) {
        counter--;
        KF(release)(keycode);
    }
}

// ----------------------------------------------------------------------------

// --- default key definitions ------------------------------------------------

#include "../../../../../firmware/lib/layout/keys.h"


// --- special keycode --------------------------------------------------------

KEYS__DEFAULT( power,   KEYBOARD__Power      );
KEYS__DEFAULT( volumeU, KEYBOARD__VolumeUp   );
KEYS__DEFAULT( volumeD, KEYBOARD__VolumeDown );
KEYS__DEFAULT( mute,    KEYBOARD__Mute       );


// --- special function -------------------------------------------------------

/**                                                   keys/shL2kcap/description
 * left shift + toggle capslock (if both shifts are pressed)
 *
 * This key always generates a left shift.  If the `shR2kcap` is pressed at
 * the same time, "capslock" will be toggled.
 */
void P(shL2kcap) (void) { KF(2_keys_capslock)(true, KEYBOARD__LeftShift); }
void R(shL2kcap) (void) { KF(2_keys_capslock)(false, KEYBOARD__LeftShift); }

/**                                                   keys/shR2kcap/description
 * right shift + toggle capslock (if both shifts are pressed)
 *
 * This key always generates a right shift.  If the `shL2kcaps` is pressed at
 * the same time, "capslock" will be toggled.
 */
void P(shR2kcap) (void) { KF(2_keys_capslock)(true, KEYBOARD__RightShift); }
void R(shR2kcap) (void) { KF(2_keys_capslock)(false, KEYBOARD__RightShift); }

/**                                                      keys/btldr/description
 * jump to the bootloader
 *
 * This prepares the Teensy to load a new firmware.  If you press this without
 * meaning to, you must turn your keyboard off then on again (usually by
 * unplugging it, then plugging it back in)
 */
void P(btldr) (void) { KF(jump_to_bootloader)(); }
void R(btldr) (void) {}

/**                                                      keys/macros/description
 * Common windows macros
 *
 * Shortcut keys that can be used in place of keys
 *
 * NOT INCLUDED:
 * Keys without macros: G, J, K, M
 * Shortucts not yet included:
 * 	Win + # keys
 * 	Win + Arrow keys
 */
void keys__press__m_all(void) {
    usb__kb__set_key(true, KEYBOARD__LeftControl);
    usb__kb__set_key(true, KEYBOARD__a_A);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__LeftControl);
    usb__kb__set_key(false, KEYBOARD__a_A);
}
void R(m_all)(void) {}

void keys__press__m_bold(void) {
    usb__kb__set_key(true, KEYBOARD__LeftControl);
    usb__kb__set_key(true, KEYBOARD__b_B);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__LeftControl);
    usb__kb__set_key(false, KEYBOARD__b_B);
}
void R(m_bold)(void) {}

void keys__press__m_copy(void) {
    usb__kb__set_key(true, KEYBOARD__LeftControl);
    usb__kb__set_key(true, KEYBOARD__c_C);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__LeftControl);
    usb__kb__set_key(false, KEYBOARD__c_C);
}
void R(m_copy)(void) {}

void keys__press__m_explr(void) {
    usb__kb__set_key(true, KEYBOARD__LeftGUI);
    usb__kb__set_key(true, KEYBOARD__e_E);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__LeftGUI);
    usb__kb__set_key(false, KEYBOARD__e_E);
}
void R(m_explr)(void) {}

void keys__press__m_find(void) {
    usb__kb__set_key(true, KEYBOARD__LeftControl);
    usb__kb__set_key(true, KEYBOARD__f_F);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__LeftControl);
    usb__kb__set_key(false, KEYBOARD__f_F);
}
void R(m_find)(void) {}

void keys__press__m_repl(void) {
    usb__kb__set_key(true, KEYBOARD__LeftControl);
    usb__kb__set_key(true, KEYBOARD__h_H);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__LeftControl);
    usb__kb__set_key(false, KEYBOARD__h_H);
}
void R(m_repl)(void) {}

void keys__press__m_italic(void) {
    usb__kb__set_key(true, KEYBOARD__LeftControl);
    usb__kb__set_key(true, KEYBOARD__i_I);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__LeftControl);
    usb__kb__set_key(false, KEYBOARD__i_I);
}
void R(m_italic)(void) {}

// Use for Alt+D and Ctrl+L (and F6?)
void keys__press__m_addbar(void) {
    usb__kb__set_key(true, KEYBOARD__LeftControl);
    usb__kb__set_key(true, KEYBOARD__l_L);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__LeftControl);
    usb__kb__set_key(false, KEYBOARD__l_L);
}
void R(m_addbar)(void) {}

void keys__press__m_new(void) {
    usb__kb__set_key(true, KEYBOARD__LeftControl);
    usb__kb__set_key(true, KEYBOARD__n_N);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__LeftControl);
    usb__kb__set_key(false, KEYBOARD__n_N);
}
void R(m_new)(void) {}

void keys__press__m_open(void) {
    usb__kb__set_key(true, KEYBOARD__LeftControl);
    usb__kb__set_key(true, KEYBOARD__o_O);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__LeftControl);
    usb__kb__set_key(false, KEYBOARD__o_O);
}
void R(m_open)(void) {}

void keys__press__m_run(void) {
    usb__kb__set_key(true, KEYBOARD__LeftGUI);
    usb__kb__set_key(true, KEYBOARD__r_R);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__LeftGUI);
    usb__kb__set_key(false, KEYBOARD__r_R);
}
void R(m_run)(void) {}

void keys__press__m_print(void) {
    usb__kb__set_key(true, KEYBOARD__LeftGUI);
    usb__kb__set_key(true, KEYBOARD__p_P);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__LeftGUI);
    usb__kb__set_key(false, KEYBOARD__p_P);
}
void R(m_print)(void) {}





void keys__press__m_save(void) {
    usb__kb__set_key(true, KEYBOARD__LeftControl);
    usb__kb__set_key(true, KEYBOARD__s_S);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__LeftControl);
    usb__kb__set_key(false, KEYBOARD__s_S);
}
void R(m_save)(void) {}

void keys__press__m_cut(void) {
    usb__kb__set_key(true, KEYBOARD__LeftControl);
    usb__kb__set_key(true, KEYBOARD__x_X);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__LeftControl);
    usb__kb__set_key(false, KEYBOARD__x_X);
}
void R(m_cut)(void) {}

void keys__press__m_paste(void) {
    usb__kb__set_key(true, KEYBOARD__LeftControl);
    usb__kb__set_key(true, KEYBOARD__v_V);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__LeftControl);
    usb__kb__set_key(false, KEYBOARD__v_V);
}
void R(m_paste)(void) {}

void keys__press__m_redo(void) {
    usb__kb__set_key(true, KEYBOARD__LeftControl);
    usb__kb__set_key(true, KEYBOARD__y_Y);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__LeftControl);
    usb__kb__set_key(false, KEYBOARD__y_Y);
}
void R(m_redo)(void) {}

void keys__press__m_undo(void) {
    usb__kb__set_key(true, KEYBOARD__LeftControl);
    usb__kb__set_key(true, KEYBOARD__z_Z);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__LeftControl);
    usb__kb__set_key(false, KEYBOARD__z_Z);
}
void R(m_undo)(void) {}

void keys__press__m_alttab(void) {
    usb__kb__set_key(true, KEYBOARD__LeftAlt);
    usb__kb__set_key(true, KEYBOARD__Tab);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__LeftAlt);
    usb__kb__set_key(false, KEYBOARD__Tab);
}
void R(m_alttab)(void) {}

void keys__press__m_close(void) {
    usb__kb__set_key(true, KEYBOARD__LeftAlt);
    usb__kb__set_key(true, KEYBOARD__F4);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__LeftAlt);
    usb__kb__set_key(false, KEYBOARD__F4);
}
void R(m_close)(void) {}

void keys__press__m_word(void) {
    usb__kb__set_key(true, KEYBOARD__LeftControl);
    usb__kb__set_key(true, KEYBOARD__RightArrow);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__LeftControl);
    usb__kb__set_key(false, KEYBOARD__RightArrow);
}
void R(m_word)(void) {}

void keys__press__m_bword(void) {
    usb__kb__set_key(true, KEYBOARD__LeftControl);
    usb__kb__set_key(true, KEYBOARD__LeftArrow);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__LeftControl);
    usb__kb__set_key(false, KEYBOARD__LeftArrow);
}
void R(m_bword)(void) {}

// ----------------------------------------------------------------------------
// --- layer ------------------------------------------------------------------

// note: these are just some default layer key definitions; no need to stick to
// them if they're inconvenient

KEYS__LAYER__PUSH_POP(0, 0);
#define  keys__press__lpu0l0    P(lpupo0l0)
#define  keys__release__lpu0l0  KF(nop)
#define  keys__press__lpo0l0    R(lpupo0l0)
#define  keys__release__lpo0l0  KF(nop)

KEYS__LAYER__PUSH_POP(1, 1);
#define  keys__press__lpu1l1    P(lpupo1l1)
#define  keys__release__lpu1l1  KF(nop)
#define  keys__press__lpo1l1    R(lpupo1l1)
#define  keys__release__lpo1l1  KF(nop)

KEYS__LAYER__PUSH_POP(2, 2);
#define  keys__press__lpu2l2    P(lpupo2l2)
#define  keys__release__lpu2l2  KF(nop)
#define  keys__press__lpo2l2    R(lpupo2l2)
#define  keys__release__lpo2l2  KF(nop)

KEYS__LAYER__PUSH_POP(3, 3);
#define  keys__press__lpu3l3    P(lpupo3l3)
#define  keys__release__lpu3l3  KF(nop)
#define  keys__press__lpo3l3    R(lpupo3l3)
#define  keys__release__lpo3l3  KF(nop)

KEYS__LAYER__PUSH_POP(4, 4);
#define  keys__press__lpu4l4    P(lpupo4l4)
#define  keys__release__lpu4l4  KF(nop)
#define  keys__press__lpo4l4    R(lpupo4l4)
#define  keys__release__lpo4l4  KF(nop)

KEYS__LAYER__PUSH_POP(5, 5);
#define  keys__press__lpu5l5    P(lpupo5l5)
#define  keys__release__lpu5l5  KF(nop)
#define  keys__press__lpo5l5    R(lpupo5l5)
#define  keys__release__lpo5l5  KF(nop)

KEYS__LAYER__PUSH_POP(6, 6);
#define  keys__press__lpu6l6    P(lpupo6l6)
#define  keys__release__lpu6l6  KF(nop)
#define  keys__press__lpo6l6    R(lpupo6l6)
#define  keys__release__lpo6l6  KF(nop)

KEYS__LAYER__PUSH_POP(7, 7);
#define  keys__press__lpu7l7    P(lpupo7l7)
#define  keys__release__lpu7l7  KF(nop)
#define  keys__press__lpo7l7    R(lpupo7l7)
#define  keys__release__lpo7l7  KF(nop)

KEYS__LAYER__PUSH_POP(8, 8);
#define  keys__press__lpu8l8    P(lpupo8l8)
#define  keys__release__lpu8l8  KF(nop)
#define  keys__press__lpo8l8    R(lpupo8l8)
#define  keys__release__lpo8l8  KF(nop)

KEYS__LAYER__PUSH_POP(9, 9);
#define  keys__press__lpu9l9    P(lpupo9l9)
#define  keys__release__lpu9l9  KF(nop)
#define  keys__press__lpo9l9    R(lpupo9l9)
#define  keys__release__lpo9l9  KF(nop)


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__COMMON__KEYS__C__H

