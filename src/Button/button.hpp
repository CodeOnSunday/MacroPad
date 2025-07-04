#ifndef BUTTON_H
#define BUTTON_H

#include <cstdint>
#include <functional>
#include "../configuration.hpp"

enum ButtonState {
	PRESSED,
	IDLE,
	UNKNOWN
};

class Button {
	public:
		Button(uint16_t hw_button_idx, ConfigEntry *hit_config = nullptr, ConfigEntry *press_config = nullptr, uint32_t hit_duration_ms = 100, uint32_t press_duration_ms = 1500);
		Button(const Button &other, ConfigEntry *hit_config);
		Button(const Button &other, ConfigEntry *hit_config, ConfigEntry *press_config);
		void Step(uint32_t timestamp);

	private:
		uint16_t hw_button_idx;
        ConfigEntry *hit_config = nullptr;
		ConfigEntry *press_config =  nullptr;
        uint16_t hit_dur;
        uint16_t press_dur;

		uint32_t timer = 0;
		ButtonState last_level = ButtonState::IDLE;
};

#endif