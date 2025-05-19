#ifndef HID_H
#define HID_H

#include "keystrokes.hpp"

#ifndef HID_EXTERN
#define HID_EXTERN extern
#endif

HID_EXTERN KeystrokeStore<50> keystroke_store;

void hid_task();

#endif