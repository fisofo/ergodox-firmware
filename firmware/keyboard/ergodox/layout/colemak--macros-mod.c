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
     esc,        1,        2,        3,        4,        5,   grave,
     tab,        q,        w,        f,        p,        g,  lpu1l1,
     nop,        a,        r,        s,        t,        d,
shL2kcap,        z,        x,        c,        v,        b,     nop,
   ctrlL,      nop,    brktL,    brktR, lpupo1l1,
                                                                 ins,    prScr,
                                                       nop,      nop,     home,
                                                        bs,      del,      end,
// right hand ..... ......... ......... ......... ......... ......... .........
             equal,        6,        7,        8,        9,        0,     dash,
		    lpu2l2,        j,        l,        u,        y,  semicol,  bkslash,
                           h,        n,        e,        i,        o,    quote,
               nop,        k,        m,    comma,   period,    slash, shR2kcap,
						      lpupo2l2,   arrowL,   arrowD,   arrowR,      app,
     nop,      nop,
   pageU,      nop,      nop,
   pageD,    enter,    space  ),

// ............................................................................

    MATRIX_LAYER(  // layer 1 : left hand macros
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
     nop,       F1,       F2,       F3,       F4,       F5,      nop,
m_alttab,      nop,      nop,      nop,  m_close,      nop,   lpo1l1,
     nop,    m_all,    ctrlL,     guiL,     altL,      nop,
     nop,   m_undo,    m_cut,   m_copy,  m_paste,      nop,      nop,
     nop,      nop,      nop,      nop,      nop,
                                                                 nop,      nop,
                                                       nop,      nop,      nop,
                                                       nop,      nop,      nop,
// right hand ..... ......... ......... ......... ......... ......... .........
             btldr,   transp,   transp,   transp,   transp,   transp,   transp,
			transp,   transp,   transp,   transp,   transp,   transp,   transp,
					  transp,   transp,   transp,   transp,   transp,   transp,
            transp,   transp,   transp,   transp,   transp,   transp,   transp,
                                   nop,   transp,   transp,   transp,   transp,
  transp,   transp,
  transp,      nop,      nop,
  transp,   transp,   transp  ),

// ............................................................................

    MATRIX_LAYER(  // layer 2 :
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
     nop,       F1,       F2,       F3,       F4,       F5,      esc,
    scrl,    prScr,    pause,      nop,      nop,      nop,      nop,
     num,      nop,  volumeU,      ins,     home,    pageU,
    caps,     mute,  volumeD,      del,      end,    pageD,      nop,
  transp,   transp,   transp,   transp,      nop,
                                                              transp,   transp,
                                                    transp,   transp,   transp,
                                                    transp,   transp,   transp,
// right hand ..... ......... ......... ......... ......... ......... .........
			   nop,       F6,       F7,       F8,       F9,      F10,      F11,
            lpu2l2,      kp7,      kp8,      kp9,    kpDiv,    kpMul,      F12,
                         kp4,      kp5,      kp6,    kpSub,    kpAdd,  kpEnter,
               nop,      kp1,      kp2,      kp3,    space,   arrowU,   transp,
                                   nop,    kpDec,   arrowL,   arrowD,   arrowR,
  transp,   transp,
  transp,   transp,   transp,
  transp,   transp,      kp0  ),

// ............................................................................
};

