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
        case 'N': kb__led__on(1); break;  // numlock
        case 'C': kb__led__on(2); break;  // capslock
        case 'S': kb__led__on(3); break;  // scroll lock
        case 'O':                 break;  // compose
        case 'K':                 break;  // kana
    };
}

void kb__led__logical_off(char led) {
    switch(led) {
        case 'N': kb__led__off(1); break;  // numlock
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

    MATRIX_LAYER(  // layer 0 : default
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
     esc,        1,        2,        3,        4,        5,    grave,
     tab,        q,        w,        f,        p,        g, m_altspc,
	guiL,        a,        r,        s,        t,        d,
shL2kcap,        z,        x,        c,        v,        b,   lpu2l2,
   ctrlL,     altL,    brktL,    brktR, lpupo1l1,
                                                                 ins,    prScr,
                                                       nop,      nop,     home,
                                                        bs,      del,      end,
// right hand ..... ......... ......... ......... ......... ......... .........
             equal,        6,        7,        8,        9,        0,     dash,
		    lpu3l3,        j,        l,        u,        y,  semicol,  bkslash,
                           h,        n,        e,        i,        o,    quote,
			lpu2l2,        k,        m,    comma,   period,    slash, shR2kcap,
						      lpupo1l1,      app,      app,     altR,    ctrlR,
 m_winLt,  m_winRt,
   pageU,      nop,      nop,
   pageD,    enter,    space  ),

// ............................................................................

    MATRIX_LAYER(  // layer 1 : macros, navigation
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
 m_altF4,       F1,       F2,       F3,       F4,       F5,   transp,
  transp,   m_winS,  m_ctrlW,  m_ctrlF,  m_ctrlP, m_gadget,   transp,
  transp,  m_ctrlA,   m_winR,  m_ctrlS,  m_ctrlT,   m_altD,
  transp,  m_ctrlZ,  m_ctrlX,  m_ctrlC,  m_ctrlV,  m_ctrlB,   transp,
  transp,   transp,  m_winLt,  m_winRt,      nop,
															  transp,   transp,
                                                       nop,      nop,   transp,
													 ctrlL,     altR,     guiL,
// right hand ..... ......... ......... ......... ......... ......... .........
			 btldr,       F6,       F7,       F8,       F9,      F10,      F11,
            transp,      nop,  m_ctrlL,  m_ctrlU,  m_ctrlY,      nop,      F12,
					 m_ctrlH, m_ctshfN,   m_winE,  m_ctrlI,  m_ctrlO,      nop,
            transp,   transp,   transp,     home,   arrowU,      end,    pageU,
                                   nop,   arrowL,   arrowD,   arrowR,    pageD,
   m_cad,  m_caEnd,
     nop,      nop,      nop,
	guiR,     altR,    ctrlR  ),

// ............................................................................

    MATRIX_LAYER(  // layer 2 : numpad, hidden F#
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
  transp,      nop,      nop,      nop,      nop,      nop,   transp,
  transp,      F13,      F14,      F15,      F16,      F17,   transp,
  transp,      F18,      F19,      F20,      F21,      F22,
   pageU,     home,   arrowU,      end,      nop,      nop,   lpo2l2,
   pageD,   arrowL,   arrowD,   arrowR,   transp,
                                                              transp,   transp,
                                                       nop,      nop,   transp,
                                                    transp,   transp,   transp,
// right hand ..... ......... ......... ......... ......... ......... .........
			transp,      nop,      num,    kpDiv,    kpMul,    kpSub,      nop,
			transp,      nop,      kp7,      kp8,      kp9,    kpAdd,      nop,
                         nop,      kp4,      kp5,      kp6,    kpAdd,      nop,
			lpo2l2,      nop,      kp1,      kp2,      kp3,  kpEnter,   transp,
                                   kp0,      nop,    kpDec,  kpEnter,   transp,
     nop,      nop,
     nop,      nop,      nop,
     nop,   transp,      kp0  ),

// ............................................................................

    MATRIX_LAYER(  // layer 3 : gaming
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
  transp,    grave,        1,        2,        3,        4,        5,
  transp,      tab,        q,        w,        e,        r,        g,
  transp,   shiftL,        a,        s,        d,        f,
  transp,    ctrlL,        z,        x,        c,        v,        b,
  transp,   transp,   transp,   transp,    space,
																  F5,       F8,
                                                       nop,      nop,   transp,
													 space,   transp,   transp,
// right hand ..... ......... ......... ......... ......... ......... .........
            transp,        6,        7,        8,        9,        0,   transp,
            lpo3l3,        y,        u,        i,        o,        p,   transp,
                           h,        j,        k,        l,  semicol,   transp,
            transp,        n,        m,   transp,   transp,   transp,   transp,
                                transp,   transp,   transp,   transp,   transp,
  transp,   transp,
  transp,      nop,      nop,
  transp,   transp,   transp  ),

};

