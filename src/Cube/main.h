#ifndef CUBEMAIN_H
#define CUBEMAIN_H

#include "stm32f0xx_hal.h"

#define BTN2_Pin GPIO_PIN_0
#define BTN2_GPIO_Port GPIOA
#define BTN3_Pin GPIO_PIN_1
#define BTN3_GPIO_Port GPIOA
#define BTN4_Pin GPIO_PIN_2
#define BTN4_GPIO_Port GPIOA
#define BTN5_Pin GPIO_PIN_3
#define BTN5_GPIO_Port GPIOA
#define BTN6_Pin GPIO_PIN_4
#define BTN6_GPIO_Port GPIOA
#define GRP1_Pin GPIO_PIN_5
#define GRP1_GPIO_Port GPIOA
#define GRP2_Pin GPIO_PIN_6
#define GRP2_GPIO_Port GPIOA
#define GRP3_Pin GPIO_PIN_7
#define GRP3_GPIO_Port GPIOA
#define GRP4_Pin GPIO_PIN_8
#define GRP4_GPIO_Port GPIOA
#define BTN1_Pin GPIO_PIN_8
#define BTN1_GPIO_Port GPIOB

void SystemClock_Config(void);
void Error_Handler(void);

#endif