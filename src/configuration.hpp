#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <cstdint>
#include <array>

#ifndef CONF_EXTERN
#define CONF_EXTERN extern
#endif

typedef enum {
    CET_LAST = 1,
    CET_DELAY = 2,
    CET_SENDKEY = 4,
    CET_LED = 8
} ConfigEntryType;

typedef struct {
    uint8_t modifier;
    uint8_t keycode;
} ConfigEntryKeyParam;

typedef struct {
    uint8_t led_id;
    uint8_t led_color_r;
    uint8_t led_color_g;
    uint8_t led_color_b;
} ConfigEntryLedParam;

typedef struct {
    uint8_t Type; // ConfigEntryType
    union {
        struct {
            uint16_t delay_before_ms;
        } Delay;
        ConfigEntryKeyParam Key;
        ConfigEntryLedParam Led;
    } Param;
} ConfigEntry;

class ConfigRunner {
    public:
        ConfigRunner();

        void QueueConfig(ConfigEntry * const entry);
        void Step(uint32_t timestamp);

    private:
        std::array<ConfigEntry * const, 5> active_configs = {nullptr};
        uint8_t readIdx = 0;
        uint8_t writeIdx = 0;
};

CONF_EXTERN ConfigRunner configuration;

#endif