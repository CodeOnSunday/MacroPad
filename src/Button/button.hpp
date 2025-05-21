#ifndef BUTTON_H
#define BUTTON_H

#include <cstdint>
#include <functional>

enum ButtonState {
	PRESSED,
	IDLE,
	UNKNOWN
};

typedef std::function<ButtonState()> ButtonCheckStateType;
typedef std::function<void()> ButtonEventHandlerType;

const ButtonCheckStateType btn_state_true = []()->ButtonState{return ButtonState::UNKNOWN;};
const ButtonEventHandlerType btn_cb_nop = [](){};

class Button {
	public:
		Button(ButtonCheckStateType state_callback = btn_state_true, ButtonEventHandlerType callback_hit = btn_cb_nop, ButtonEventHandlerType callback_press = btn_cb_nop, uint32_t hit_duration_ms = 100, uint32_t press_duration_ms = 1500);
		Button(const Button &other, ButtonEventHandlerType callback_hit);
		Button(const Button &other, ButtonEventHandlerType callback_hit, ButtonEventHandlerType callback_press);
		void Step(uint32_t timestamp);

		ButtonCheckStateType GetChecker() const;
        
	private:
        ButtonCheckStateType state_cb;
        ButtonEventHandlerType hit_cb;
        ButtonEventHandlerType press_cb;
        uint32_t hit_dur;
        uint32_t press_dur;

		uint32_t timer = 0;
		ButtonState last_level = ButtonState::IDLE;
};

#endif