#ifndef USB_ID_H
#define USB_ID_H

#include "tusb.h"

static inline size_t board_usb_get_serial(uint16_t desc_str1[], size_t max_chars) {
    uint8_t uid[16] TU_ATTR_ALIGNED(4);
    size_t uid_len;
  
    const uint32_t UID_BASE = 0x1FFFF7ACUL;       /*!< Unique device ID register base address */
    volatile uint32_t * stm32_uuid = (volatile uint32_t *) UID_BASE;
    uint32_t* id32 = (uint32_t*) (uintptr_t) uid;
    id32[0] = stm32_uuid[0];
    id32[1] = stm32_uuid[1];
    id32[2] = stm32_uuid[2];
    uid_len = 12;
  
    if ( uid_len > max_chars / 2 ) uid_len = max_chars / 2;
  
    for ( size_t i = 0; i < uid_len; i++ ) {
      for ( size_t j = 0; j < 2; j++ ) {
        const char nibble_to_hex[16] = {
            '0', '1', '2', '3', '4', '5', '6', '7',
            '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
        };
        uint8_t const nibble = (uid[i] >> (j * 4)) & 0xf;
        desc_str1[i * 2 + (1 - j)] = nibble_to_hex[nibble]; // UTF-16-LE
      }
    }
  
    return 2 * uid_len;
}

#endif