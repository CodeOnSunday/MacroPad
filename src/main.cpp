extern "C" {
    #include "Cube/main.h"
    #include "Cube/gpio.h"
    #include "Cube/peripherals/usart.h"
    #include "Cube/peripherals/tim.h"
    #include "Cube/peripherals/usb.h"

    #include "tusb.h"
}

#include "Button/button.hpp"
#include "Button/button_sw.hpp"
#include "Button/button_hw.hpp"

#include "USB/HID/hid.hpp"
#include "USB/HID/usb_hid_keys.h"

using namespace std;

void configureBtn() {
    buttons[0] = Button(buttons[0], []() { 
        keystroke_store.PushStroke(GenKeyCodeOneKey(KEY_A));
        keystroke_store.PushRelease();
    } );
    buttons[1] = Button(buttons[1], []() { 
        keystroke_store.PushStroke(GenKeyCodeOneKey(KEY_B));
        keystroke_store.PushRelease();
    } );
}

int main() {
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_TIM3_Init();
    MX_USART1_UART_Init();
    MX_USB_PCD_Init();


    tusb_rhport_init_t dev_init = {
        .role = TUSB_ROLE_DEVICE,
        .speed = TUSB_SPEED_AUTO
    };
    tusb_init(BOARD_TUD_RHPORT, &dev_init);

    configureBtn();
  
    while(1) {
        uint32_t time = HAL_GetTick();
        btn_task(time);
        btn_hw_task(time);

        tud_task();
        hid_task();
    }

    return 0;
}