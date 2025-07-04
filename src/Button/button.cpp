#include "button.hpp"
#include "button_hw.hpp"

Button::Button(uint16_t hw_button_idx, ConfigEntry *hit_config, ConfigEntry *press_config, uint32_t hit_duration_ms, uint32_t press_duration_ms) :
    hw_button_idx(hw_button_idx),
    hit_config(hit_config),
    press_config(press_config),
    hit_dur(hit_duration_ms),
    press_dur(press_duration_ms) {
}

Button::Button(const Button &other, ConfigEntry *hit_config):
    hw_button_idx(other.hw_button_idx),
    hit_config(hit_config),
    press_config(other.press_config),
    hit_dur(other.hit_dur),
    press_dur(other.press_dur) {
}

Button::Button(const Button &other, ConfigEntry *hit_config, ConfigEntry *press_config):
    hw_button_idx(other.hw_button_idx),
    hit_config(hit_config),
    press_config(press_config),
    hit_dur(other.hit_dur),
    press_dur(other.press_dur) {
}

void Button::Step(uint32_t timestamp) {
    ButtonState new_level = ButtonHW_ReadState(hw_button_idx);
    if(new_level == UNKNOWN) {
        return;
    }
     
    if(last_level != new_level) {
        if(new_level == IDLE) {
            if(timestamp > timer + press_dur) {
                if(hit_config != nullptr) {
                    configuration.QueueConfig(hit_config);
                }
            } else if(timestamp > timer + hit_dur) {
                if( press_config != nullptr) {
                    configuration.QueueConfig(press_config);
                }
            }
        }
        timer = timestamp;
        last_level = new_level;
    }
}