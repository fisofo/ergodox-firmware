/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * A Colemark layout utilizing layers for quick access to macros.
 *
 * Implements the "layout" section of '.../firmware/keyboard.h'
 */


#include "./common/definitions.h"


// ----------------------------------------------------------------------------
// matrix control
// ----------------------------------------------------------------------------

#include "./common/exec_key.c.h"


// ----------------------------------------------------------------------------
// LED control
// ----------------------------------------------------------------------------

void kb__led__logical_on(char led) {
    switch(led) {
        case 'N': kb__led__off(1); break;  // numlock
        case 'C': kb__led__on(2); break;  // capslock
        case 'S': kb__led__on(3); break;  // scroll lock
        case 'O':                 break;  // compose
        case 'K':                 break;  // kana
    };
}

void kb__led__logical_off(char led) {
    switch(led) {
        case 'N': kb__led__on(1); break;  // numlock
        case 'C': kb__led__off(2); break;  // capslock
        case 'S': kb__led__off(3); break;  // scroll lock
        case 'O':                  break;  // compose
        case 'K':                  break;  // kana
    };
}


// ----------------------------------------------------------------------------
// keys
// ----------------------------------------------------------------------------

#include "./common/keys.c.h"

KEYS__LAYER__NUM_PUSH(10, 3);
KEYS__LAYER__NUM_POP(10);


// ----------------------------------------------------------------------------
// layout
// ----------------------------------------------------------------------------

#include "./common/matrix.h"

static _layout_t _layout = {

// ............................................................................

    MATRIX_LAYER(  // BLACK layer 0 : default
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
     esc,        1,        2,        3,        4,        5,    grave,
     tab,        q,        w,        f,        p,        g,   lpu3l3,
	guiL,        a,        r,        s,        t,        d,
shL2kcap,        z,        x,        c,        v,        b, lpupo1l1,
   ctrlL,     altL,      app,     altL,    ctrlL,
                                                                 F16,    prScr,
                                                       nop,      nop,      F19,
                                                        bs, lpupo1l1,      del,
// right hand ..... ......... ......... ......... ......... ......... .........
               ins,        6,        7,        8,        9,        0,     dash,
		     brktL,        j,        l,        u,        y,  semicol,  bkslash,
                           h,        n,        e,        i,        o,    quote,
			 brktR,        k,        m,    comma,   period,    slash, shR2kcap,
						 space_tap_key,   lpu2l2,      app,     altR,    ctrlR,
 m_winLt,  m_winRt,
 m_winUp,      nop,      nop,
  lpu1l1, lpupo1l1,    enter  ),

// ............................................................................

    MATRIX_LAYER(  // RED layer 1 : function keys, navigation
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
 m_altF4,       F1,       F2,       F3,       F4,       F5,   transp,
  transp,   transp,   transp,   transp,   transp,   transp,   transp,
  transp,   transp,   transp,   transp,   transp,   transp,
  transp,   transp,   transp,   transp,   transp,   transp,   transp,
  transp,   transp,   transp,   transp,   transp,
															  transp,   transp,
                                                       nop,      nop,   transp,
													transp,      nop,   transp,
// right hand ..... ......... ......... ......... ......... ......... .........
			 btldr,       F6,       F7,       F8,       F9,      F10,      F11,
               F17,      ins,     home,   arrowU,      end,      nop,      F12,
					     nop,   arrowL,   arrowD,   arrowR,      nop,    equal,
               F18,      nop,    pageU,      nop,    pageD,      nop,   transp,
								transp,   transp,   transp,   transp,   transp,
   m_cad,  m_caEnd,
  transp,      nop,      nop,
  lpo1l1,      nop,   transp  ),

// ............................................................................

    MATRIX_LAYER(  // BLUE layer 2 : numpad, gaming
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
  transp,   transp,   transp,   transp,   transp,   transp,   transp,
  transp,   transp,   transp,   transp,   transp,   transp,   transp,
  transp,   transp,   transp,   transp,   transp,   transp,
  transp,   transp,   transp,   transp,   transp,   transp,      nop,
  transp,   transp,   transp,   transp,    space,
                                                                  F5,       F8,
                                                       nop,      nop,   transp,
                                                    transp,   transp,   transp,
// right hand ..... ......... ......... ......... ......... ......... .........
			transp,      nop,      num,    kpDiv,    kpMul,    kpSub,      nop,
			transp,      esc,      kp7,      kp8,      kp9,    kpAdd,      nop,
                         F20,      kp4,      kp5,      kp6,    kpAdd,      nop,
			transp,      nop,      kp1,      kp2,      kp3,  kpEnter,   transp,
                                   kp0,   lpo2l2,    kpDec,  kpEnter,   transp,
  transp,   transp,
  transp,      nop,      nop,
  transp,   transp,   transp  ),

// ............................................................................

    MATRIX_LAYER(  // GREEN layer 3 : qwerty
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
  transp,        1,        2,        3,        4,        5,   transp,
  transp,        q,        w,        e,        r,        t,   lpo3l3,
  transp,        a,        s,        d,        f,        g,
  transp,        z,        x,        c,        v,        b,   transp,
  transp,   transp,   transp,   transp,   transp,
                                                              transp,   transp,
                                                       nop,      nop,   transp,
                                                    transp,   transp,   transp,
// right hand ..... ......... ......... ......... ......... ......... .........
            transp,        6,        7,        8,        9,        0,   transp,
            transp,        y,        u,        i,        o,        p,   transp,
                           h,        j,        k,        l,  semicol,   transp,
            transp,        n,        m,   transp,   transp,   transp,   transp,
								transp,   transp,   transp,   transp,   transp,
  transp,   transp,
  transp,      nop,      nop,
  transp,   transp,   transp   ),

};

