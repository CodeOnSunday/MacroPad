#define HID_EXTERN
#include "hid.hpp"

extern "C" {
    #include "tusb.h"
    #include "../usb_descriptors.h"
}

void hid_task() {
	if ( tud_hid_n_ready(ITF_NUM_HID1) ) {
		if(!keystroke_store.IsEmpty()){
			KeystrokeType stroke = keystroke_store.Pull();
			tud_hid_n_keyboard_report(ITF_NUM_HID1, 0, stroke.modifier, stroke.keycode);
		}
	}
}