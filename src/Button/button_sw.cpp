#define BUTTON_SW_EXTERN

extern "C" {
    #include "stm32f0xx_hal.h"
}

#include "button_sw.hpp"
#include "button_hw.hpp"

std::array<Button, 6> buttons = {
    // Btn 1-6
    Button(0),
    Button(1),
    Button(2),
    Button(3),
    Button(4),
    Button(5),
    // // Btn 7-12
    // Button(6),
    // Button(7),
    // Button(8),
    // Button(9),
    // Button(10),
    // Button(11),
    // // Btn 13-18
    // Button(12),
    // Button(13),
    // Button(14),
    // Button(15),
    // Button(16),
    // Button(17),
    // // Btn 19-24
    // Button(18),
    // Button(19),
    // Button(20),
    // Button(21),
    // Button(22),
    // Button(23),
};

void btn_task(uint32_t time) {
    for(auto it = buttons.begin(); it != buttons.end(); it++) {
        it->Step(time);
    }
}