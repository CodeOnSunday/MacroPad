#define BUTTON_SW_EXTERN

extern "C" {
    #include "stm32f0xx_hal.h"
}

#include "button_sw.hpp"
#include "button_hw.hpp"

std::array<Button, 24> buttons = {
    // Btn 1-6
    Button(GenerateBtnChecker(0)),
    Button(GenerateBtnChecker(1)),
    Button(GenerateBtnChecker(2)),
    Button(GenerateBtnChecker(3)),
    Button(GenerateBtnChecker(4)),
    Button(GenerateBtnChecker(5)),
    // Btn 7-12
    Button(GenerateBtnChecker(6)),
    Button(GenerateBtnChecker(7)),
    Button(GenerateBtnChecker(8)),
    Button(GenerateBtnChecker(9)),
    Button(GenerateBtnChecker(10)),
    Button(GenerateBtnChecker(11)),
    // Btn 13-18
    Button(GenerateBtnChecker(12)),
    Button(GenerateBtnChecker(13)),
    Button(GenerateBtnChecker(14)),
    Button(GenerateBtnChecker(15)),
    Button(GenerateBtnChecker(16)),
    Button(GenerateBtnChecker(17)),
    // Btn 19-24
    Button(GenerateBtnChecker(18)),
    Button(GenerateBtnChecker(19)),
    Button(GenerateBtnChecker(20)),
    Button(GenerateBtnChecker(21)),
    Button(GenerateBtnChecker(22)),
    Button(GenerateBtnChecker(23)),
};

void btn_task(uint32_t time) {
    for(auto it = buttons.begin(); it != buttons.end(); it++) {
        it->Step(time);
    }
}