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
shL2kcap,        z,        x,        c,        v,        b,      ins,
   ctrlL,     altL,      app,     altL, ctrlL2l1,
                                                                 F17,      F18,
                                                       nop,      nop,    prScr,
                                                        bs, lpupo1l1,      del,
// right hand ..... ......... ......... ......... ......... ......... .........
			 equal,        6,        7,        8,        9,        0,     dash,
		     brktL,        j,        l,        u,        y,  semicol,  bkslash,
                           h,        n,        e,        i,        o,    quote,
			 brktR,        k,        m,    comma,   period,    slash, shR2kcap,
							     space,   lpu1l1,      app,     altR,    ctrlR,
 m_winLt,  m_winRt,
 m_winUp,      nop,      nop,
      bs,   lpu2l2,    enter  ),

// ............................................................................

    MATRIX_LAYER(  // RED layer 1 : function keys, navigation
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
 m_altF4,       F1,       F2,       F3,       F4,       F5,   transp,
  transp,    pageU,     home,   arrowU,      end,      ins,   transp,
  transp,    pageD,   arrowL,   arrowD,   arrowR,      del,
  transp,  m_ctrlZ,  m_ctrlX,  m_ctrlC,  m_ctrlV,  m_ctrlB,   transp,
  transp,   transp,   transp,   transp,    ctrlL,
															  transp,   transp,
                                                       nop,      nop,   transp,
													transp,      nop,   transp,
// right hand ..... ......... ......... ......... ......... ......... .........
			 btldr,       F6,       F7,       F8,       F9,      F10,      F11,
               F17,      ins,     home,   arrowU,      end,   transp,   transp,
					     del,   arrowL,   arrowD,   arrowR,   transp,   transp,
               F18,   	 F12,    pageU,   transp,    pageD,   transp,   transp,
								transp,   lpo1l1,   transp,   transp,   transp,
   m_cad,  m_caEnd,
  transp,      nop,      nop,
  transp,       bs,   transp  ),

// ............................................................................

    MATRIX_LAYER(  // BLUE layer 2 : numpad
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
  transp,   transp,   transp,   transp,   transp,   transp,   transp,
  transp,   transp,   transp,   transp,   transp,   transp,   transp,
  transp,   transp,   transp,   transp,   transp,   transp,
  transp,   transp,   transp,   transp,   transp,   transp,   transp,
  transp,   transp,   transp,   transp,   transp,
															  transp,   transp,
                                                       nop,      nop,   transp,
                                                    transp,   transp,   transp,
// right hand ..... ......... ......... ......... ......... ......... .........
			transp,      nop,      num,    kpDiv,    kpMul,    kpSub,   transp,
			transp,      esc,      kp7,      kp8,      kp9,    kpAdd,   transp,
                         F20,      kp4,      kp5,      kp6,    kpAdd,   transp,
			transp,      nop,      kp1,      kp2,      kp3,  kpEnter,   transp,
                                   kp0,      nop,    kpDec,  kpEnter,   transp,
  transp,   transp,
  transp,      nop,      nop,
  transp,   lpo2l2,   transp  ),

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

