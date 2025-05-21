#ifndef BUTTON_SW_H
#define BUTTON_SW_H

#include "button.hpp"

#include <array>

#ifndef BUTTON_SW_EXTERN
extern std::array<Button, 24> buttons;
#endif

void btn_task(uint32_t time);

#endif