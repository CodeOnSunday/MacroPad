#include "cdc.hpp"

extern "C" { 
    #include "tusb.h"
    #include "../usb_descriptors.h"
}

uint8_t cdc_input_buffer[1024*3];
const uint16_t cdc_input_buffer_length = sizeof(cdc_input_buffer) / sizeof(cdc_input_buffer[0]);

void cdc_task() {
    
    if ( tud_cdc_available(ITF_NUM_CDC1) ) {
        uint32_t read_count = tud_cdc_read(cdc_input_buffer, (uint32_t) cdc_input_buffer_length);
	}
}