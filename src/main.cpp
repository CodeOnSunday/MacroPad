extern "C" {
    #include "Cube/main.h"
    #include "Cube/gpio.h"
    #include "Cube/peripherals/usart.h"
    #include "Cube/peripherals/tim.h"
    #include "Cube/peripherals/usb.h"
}

#include "Button/button.hpp"
#include "USB/HID/hid.hpp"

using namespace std;

array<Button, 24> buttons;

int main() {
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_TIM3_Init();
    MX_USART1_UART_Init();
    MX_USB_PCD_Init();
  
    while(1) {
        hid_task();
    }

    return 0;
}