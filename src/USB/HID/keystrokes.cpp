#include "keystrokes.hpp"

KeystrokeType GenKeyCodeOneKey(uint8_t key, uint8_t mod) {
    return (KeystrokeType){
        .modifier = mod,
        .keycode = { key, 0 }
    };
}