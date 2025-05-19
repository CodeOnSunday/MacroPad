#ifndef BUTTON_H
#define BUTTON_H

#include <cstdint>
#include <functional>

typedef std::function<bool()> ButtonCheckStateType;
typedef std::function<void()> ButtonEventHandlerType;

const ButtonCheckStateType btn_state_true = []()->bool{return true;};
const ButtonEventHandlerType btn_cb_nop = [](){};

class Button {
	public:
		Button(ButtonCheckStateType state_callback = btn_state_true, ButtonEventHandlerType callback_hit = btn_cb_nop, ButtonEventHandlerType callback_press = btn_cb_nop, uint32_t hit_duration_ms = 100, uint32_t press_duration_ms = 1500);
		void Step(uint32_t timestamp);
        
	private:
        ButtonCheckStateType state_cb;
        ButtonEventHandlerType hit_cb;
        ButtonEventHandlerType press_cb;
        uint32_t hit_dur;
        uint32_t press_dur;

		uint32_t timer = 0;
		bool last_level = 1;
};

#endif