#define BUTTON_HW_EXTERN
#include "button_hw.hpp"
#include <functional>

using namespace std;

BtnHWGroup::BtnHWGroup(BtnHWPin hwPin, bool inverted) :
    hwPin(hwPin),
    inverted(inverted) {
}

bool BtnHWGroup::Get() const {
    bool state = ( ( LL_GPIO_ReadOutputPort(hwPin.port) & hwPin.pin ) != 0 );
    if(inverted) {
        state = !state;
    }
    return state;
}

void BtnHWGroup::Set(bool active) {
    if(inverted) {
        active = !active;
    }
    if(active) {
        LL_GPIO_SetOutputPin(hwPin.port, hwPin.pin);
    } else {
        LL_GPIO_ResetOutputPin(hwPin.port, hwPin.pin);
    }
}

BtnHWInput::BtnHWInput(BtnHWGroup *group, BtnHWPin hwPin) :
    group(group), 
    hwPin(hwPin) {
}

ButtonState BtnHWInput::Get() const {
    if(group->Get()) {
        if( LL_GPIO_IsInputPinSet(hwPin.port, hwPin.pin) ) {
            return ButtonState::PRESSED;
        } else {
            return ButtonState::IDLE;
        }
    } else {
        return ButtonState::UNKNOWN;
    }
}


std::array<BtnHWGroup, 4> GroupDefinitions = {
    BtnHWGroup({ .port=GPIOA, .pin=LL_GPIO_PIN_5 }, true),
    BtnHWGroup({ .port=GPIOA, .pin=LL_GPIO_PIN_6 }),
    BtnHWGroup({ .port=GPIOA, .pin=LL_GPIO_PIN_7 }),
    BtnHWGroup({ .port=GPIOA, .pin=LL_GPIO_PIN_8 })
};

const struct BtnHWPin InputDefinitions[6] = {
    { .port=GPIOB, .pin=LL_GPIO_PIN_8 },
    { .port=GPIOA, .pin=LL_GPIO_PIN_0 },
    { .port=GPIOA, .pin=LL_GPIO_PIN_1 },
    { .port=GPIOA, .pin=LL_GPIO_PIN_2 },
    { .port=GPIOA, .pin=LL_GPIO_PIN_3 },
    { .port=GPIOA, .pin=LL_GPIO_PIN_4 }
};

std::array<BtnHWInput, 24> ButtonDefinitions = {
    // Btn 1-6
    BtnHWInput(&(GroupDefinitions[0]), InputDefinitions[0]),
    BtnHWInput(&(GroupDefinitions[0]), InputDefinitions[1]),
    BtnHWInput(&(GroupDefinitions[0]), InputDefinitions[2]),
    BtnHWInput(&(GroupDefinitions[0]), InputDefinitions[3]),
    BtnHWInput(&(GroupDefinitions[0]), InputDefinitions[4]),
    BtnHWInput(&(GroupDefinitions[0]), InputDefinitions[5]),
    // Btn 7-12
    BtnHWInput(&(GroupDefinitions[1]), InputDefinitions[0]),
    BtnHWInput(&(GroupDefinitions[1]), InputDefinitions[1]),
    BtnHWInput(&(GroupDefinitions[1]), InputDefinitions[2]),
    BtnHWInput(&(GroupDefinitions[1]), InputDefinitions[3]),
    BtnHWInput(&(GroupDefinitions[1]), InputDefinitions[4]),
    BtnHWInput(&(GroupDefinitions[1]), InputDefinitions[5]),
    // Btn 13-18
    BtnHWInput(&(GroupDefinitions[2]), InputDefinitions[0]),
    BtnHWInput(&(GroupDefinitions[2]), InputDefinitions[1]),
    BtnHWInput(&(GroupDefinitions[2]), InputDefinitions[2]),
    BtnHWInput(&(GroupDefinitions[2]), InputDefinitions[3]),
    BtnHWInput(&(GroupDefinitions[2]), InputDefinitions[4]),
    BtnHWInput(&(GroupDefinitions[2]), InputDefinitions[5]),
    // Btn 19-24
    BtnHWInput(&(GroupDefinitions[3]), InputDefinitions[0]),
    BtnHWInput(&(GroupDefinitions[3]), InputDefinitions[1]),
    BtnHWInput(&(GroupDefinitions[3]), InputDefinitions[2]),
    BtnHWInput(&(GroupDefinitions[3]), InputDefinitions[3]),
    BtnHWInput(&(GroupDefinitions[3]), InputDefinitions[4]),
    BtnHWInput(&(GroupDefinitions[3]), InputDefinitions[5]),
};

ButtonCheckStateType GenerateBtnChecker(uint32_t idx) {
    return [idx]() -> ButtonState{
        return ButtonDefinitions[idx].Get();
    };
}

void btn_hw_task(uint32_t time) {
    const uint8_t groupSize = sizeof(GroupDefinitions) / sizeof(GroupDefinitions[0]);
    static uint8_t activeGroup = groupSize - 1;
    static uint32_t timer = 0;

    if(time > timer) {
        GroupDefinitions[activeGroup].Set(false);
        activeGroup = (activeGroup + 1) % groupSize;
        GroupDefinitions[activeGroup].Set(true);

        timer = time + 50;
    }
}