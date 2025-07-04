extern "C" {
    #include "Cube/main.h"
    #include "Cube/gpio.h"
    #include "Cube/peripherals/usart.h"
    #include "Cube/peripherals/dma.h"
    #include "Cube/peripherals/tim.h"
    #include "Cube/peripherals/usb.h"

    #include "tusb.h"
}

#include "Button/button.hpp"
#include "Button/button_sw.hpp"
#include "Button/button_hw.hpp"

#include "USB/HID/hid.hpp"
#include "USB/HID/usb_hid_keys.h"

#include "configuration.hpp"
std::array<ConfigEntry, 6*10> config_buffer;

using namespace std;

void configureBtn() {

    config_buffer[0].Type = CET_SENDKEY | CET_LAST;
    config_buffer[0].Param.Key.keycode = KEY_A;

    config_buffer[1].Type = CET_SENDKEY | CET_LAST;
    config_buffer[1].Param.Key.keycode = KEY_A;
    config_buffer[1].Param.Key.modifier = HID_KEY_SHIFT_LEFT;

    config_buffer[2].Type = CET_SENDKEY;
    config_buffer[2].Param.Key.keycode = KEY_B;

    config_buffer[3].Type = CET_SENDKEY | CET_LAST;
    config_buffer[3].Param.Key.keycode = KEY_C;

    buttons[0] = Button(buttons[0], &config_buffer[0], &config_buffer[1] );
    buttons[1] = Button(buttons[1], &config_buffer[2] );
}

const uint16_t ARR = 57;
const uint16_t LB1 = 28;
const uint16_t LB0 = 14;

uint16_t led_data[32];

void TIM_Callback(TIM_HandleTypeDef *htim){
    HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_3);
}

int main() {
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_DMA_Init();
    MX_TIM3_Init();
    MX_USART1_UART_Init();
    MX_USB_PCD_Init();
    
    tusb_rhport_init_t dev_init = {
        .role = TUSB_ROLE_DEVICE,
        .speed = TUSB_SPEED_AUTO
    };
    tusb_init(BOARD_TUD_RHPORT, &dev_init);

    configureBtn();

    for(uint16_t i=0;i<sizeof(led_data) / sizeof(uint16_t);i++){
        led_data[i] = LB1;
    }

    HAL_TIM_RegisterCallback(&htim3, HAL_TIM_PWM_PULSE_FINISHED_CB_ID, TIM_Callback);
    HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_3, (uint32_t*)led_data, sizeof(led_data) / sizeof(uint16_t));
  
    while(1) {
        uint32_t time = HAL_GetTick();
        btn_task(time);
        btn_hw_task(time);

        tud_task();
        hid_task();
    }

    return 0;
}