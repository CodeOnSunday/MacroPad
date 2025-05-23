#ifndef CDC_H
#define CDC_H

#include <cstdint>
#include "KeyConfigParser.hpp"

#ifndef CDC_EXTERN
#define CDC_EXTERN extern
#endif

const uint32_t CDC_BUFFER_SIZE = 200;

class CDCBuffer : public KeyConfigSource {
    public:
        uint8_t* GetBuffer();
        uint32_t GetCount();
        void InputUsed(uint32_t count);
        void InputAdded(uint32_t count);

    private:
        uint8_t buffer[CDC_BUFFER_SIZE];
        uint32_t count = 0;
};

CDC_EXTERN CDCBuffer cdc_buffer;

void cdc_task();

#endif