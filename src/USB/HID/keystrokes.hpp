#ifndef KEYSTROKES_H
#define KEYSTROKES_H

#include <cstdint>
#include <array>

typedef struct {
    uint8_t modifier;
    uint8_t keycode[6];
} KeystrokeType;

template<uint32_t N>
class KeystrokeStore {
    public:
        void PushStroke(const KeystrokeType stroke) {
            strokes[write_idx] = stroke;
            write_idx = (write_idx + 1) % N;
        }
        void PushText(const char msg[], uint32_t size) {
            KeystrokeType kt = {0};
            for(uint32_t i=0; i<size; i++) {
                kt.keycode[0] = msg[i];
                PushStroke(kt);
            }
        }
        void PushRelease() {
            static const KeystrokeType kt = {0};
            PushStroke(kt);
        }

        bool IsEmpty() {
            return read_idx == write_idx;
        }
        KeystrokeType Pull() {
            if(IsEmpty()) {
                return (KeystrokeType){0};
            }
        
            uint32_t old_idx = read_idx;
            read_idx = (read_idx + 1) % N;
            return strokes[old_idx];
        }

    private:
        std::array<KeystrokeType, N> strokes;
        uint32_t write_idx = 0;
        uint32_t read_idx = 0;
};

#endif