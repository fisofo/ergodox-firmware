/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * EEPROM interface
 *
 * Prefix: `eeprom__`
 *
 * Notes:
 * - This is meant to be a replacement for the read, write, and update
 *   functions provided by `<avr/eeprom.h>`, and should be preferred for those
 *   operations.  There are other things provided by that header that may be
 *   useful however, and it's likely that both will be needed.
 *
 * Implementation notes:
 * - Writes generated by calls to `eeprom__write()` and `eeprom__copy()` should
 *   collectively execute in the order in which the calls were performed (i.e.
 *   all writes should be sequential, in the expected order, regardless of the
 *   function which generated them).
 */


#ifndef ERGODOX_FIRMWARE__LIB__EEPROM__H
#define ERGODOX_FIRMWARE__LIB__EEPROM__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include <stdint.h>

// ----------------------------------------------------------------------------

#ifndef OPT__EEPROM_MACRO__EEPROM_SIZE
    #error "OPT__EEPROM_MACRO__EEPROM_SIZE not defined"
#endif

// ----------------------------------------------------------------------------

uint8_t eeprom__read  (uint8_t * from);
uint8_t eeprom__write (uint8_t * to, uint8_t data);
uint8_t eeprom__copy  (uint8_t * to, uint8_t * from, uint8_t length);


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__LIB__EEPROM__H



// ============================================================================
// === documentation ==========================================================
// ============================================================================


// ----------------------------------------------------------------------------
// macros ---------------------------------------------------------------------
// ----------------------------------------------------------------------------

// === OPT__EEPROM_MACRO__EEPROM_SIZE ===
/**                           macros/OPT__EEPROM_MACRO__EEPROM_SIZE/description
 * The total size (in bytes) of the EEPROM memory to be allocated by the
 * implementing file
 */


// ----------------------------------------------------------------------------
// functions ------------------------------------------------------------------
// ----------------------------------------------------------------------------

// === eeprom__read() ===
/**                                          functions/eeprom__read/description
 * Read and return the data at `address` in the EEPROM memory space
 *
 * Arguments:
 * - `from: The address of (i.e. a pointer to) the location to read from
 */

// === eeprom__write() ===
/**                                         functions/eeprom__write/description
 * Schedule a regular 1 byte write to the EEPROM memory space
 *
 * Arguments:
 * - `to`: The address of (i.e. a pointer to) the location to write to
 * - `data`: The data to write
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 *
 * Notes:
 * - Writes are scheduled (i.e. buffered) because writing to EEPROMs takes an
 *   enormous (relative to a microprocessor clock cycle) amount of time.
 * - Due to the technology used, EEPROM bytes, when cleared, have a logical
 *   value of `1`.  Interesting stuff, but I didn't read about it thoroughly
 *   enough to give my own explanation here.
 *
 * Implementation notes:
 * - Undefined behavior will result if
 *     - `to` is not a valid address
 * - This function should only modify when necessary; that is, when the data to
 *   be written is different than the data that's already there.  This requires
 *   more processor time (to read the current value and compare), but it's
 *   better for the EEPROM (which has a limited write life), and will allow the
 *   operation to complete *much* more quickly in the event that the data has
 *   not changed.
 * - Writing `0xFF` should clear the memory (without writing anything), and
 *   writing to a location currently set to `0xFF` should write without
 *   clearing first.
 */

// === eeprom__copy() ===
/**                                          functions/eeprom__copy/description
 * Copy data from one location in the EEPROM memory space to another
 *
 * Arguments:
 * - `to: The address of (i.e. a pointer to) the location to start writing to
 * - `from`: The address of (i.e. a pointer to) the location to start copying
 *   from
 * - `length`: The number of bytes to sequentially copy
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 *
 *
 * Implementation notes:
 *
 * - If `to == from`, nothing should be done
 * - If `to < from`, copying should start with the given addresses, and
 *   increment for `length - 1` bytes
 * - If `to > from`, copying should start with the given addresses, and
 *   decrement for `length - 1` bytes
 *
 * - Undefined behavior will result if any address in either the block you're
 *   copying from (`from`..`from+length-1`) or the block you're copying to
 *   (`to`..`to+length-1`) is invalid.
 */

