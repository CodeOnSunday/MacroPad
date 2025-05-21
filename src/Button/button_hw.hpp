#ifndef BUTTON_HW_H
#define BUTTON_HW_H

extern "C" {
    #include "stm32f0xx_ll_gpio.h"
}

#include "button.hpp"
#include <array>

struct BtnHWPin {
    GPIO_TypeDef *port;
    uint32_t pin;
};

class BtnHWGroup {
    public:
        BtnHWGroup(BtnHWPin hwPin, bool inverted=false);
        bool Get() const;
        void Set(bool active);

    private:
        BtnHWPin hwPin;
        bool inverted;
};

class BtnHWInput {
    public:
        BtnHWInput(BtnHWGroup *group, BtnHWPin hwPin);
        ButtonState Get() const;

    private:
        BtnHWGroup *group;
        BtnHWPin hwPin;
};

#ifndef BUTTON_HW_EXTERN
extern std::array<BtnHWGroup, 4> GroupDefinitions;
extern std::array<BtnHWInput, 24> ButtonDefinitions;
#endif

ButtonState ButtonReadState(uint32_t idx);
ButtonCheckStateType GenerateBtnChecker(uint32_t idx);

void btn_hw_task(uint32_t time);

#endif