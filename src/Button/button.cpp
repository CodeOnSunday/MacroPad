#include "button.hpp"

Button::Button(ButtonCheckStateType state_callback, ButtonEventHandlerType callback_hit, ButtonEventHandlerType callback_press, uint32_t hit_duration_ms, uint32_t press_duration_ms) :
    state_cb(state_callback),
    hit_cb(callback_hit),
    press_cb(callback_press),
    hit_dur(hit_duration_ms),
    press_dur(press_duration_ms) {
}

Button::Button(const Button &other, ButtonEventHandlerType callback_hit):
    state_cb(other.state_cb),
    hit_cb(callback_hit),
    press_cb(other.press_cb),
    hit_dur(other.hit_dur),
    press_dur(other.press_dur) {
}

Button::Button(const Button &other, ButtonEventHandlerType callback_hit, ButtonEventHandlerType callback_press):
    state_cb(other.state_cb),
    hit_cb(callback_hit),
    press_cb(callback_press),
    hit_dur(other.hit_dur),
    press_dur(other.press_dur) {
}

void Button::Step(uint32_t timestamp) {
    ButtonState new_level = state_cb();
    if(new_level == UNKNOWN) {
        return;
    }
     
    if(last_level != new_level) {
        if(new_level == IDLE) {
            if(timestamp > timer + press_dur) {
                press_cb();
            } else if(timestamp > timer + hit_dur) {
                hit_cb();
            }
        }
        timer = timestamp;
        last_level = new_level;
    }
}

ButtonCheckStateType Button::GetChecker() const {
    return state_cb;
}
