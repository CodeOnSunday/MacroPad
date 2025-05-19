#include "button.hpp"

Button::Button(ButtonCheckStateType state_callback, ButtonEventHandlerType callback_hit, ButtonEventHandlerType callback_press, uint32_t hit_duration_ms, uint32_t press_duration_ms) :
    state_cb(state_callback),
    hit_cb(callback_hit),
    press_cb(callback_press),
    hit_dur(hit_duration_ms),
    press_dur(press_duration_ms) {
}

void Button::Step(uint32_t timestamp) {
    bool new_level = state_cb();
    if(last_level != new_level) {
        if(last_level == 0) {
            if(timestamp > timer + press_dur) {
                press_cb();
            } else if(timestamp > timer + hit_dur) {
                hit_cb();
            }
        }
        timer = timestamp;
    }
    last_level = new_level;
}