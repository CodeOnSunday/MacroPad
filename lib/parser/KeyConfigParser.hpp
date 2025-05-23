#ifndef KEYCONFIGPARSER_H
#define KEYCONFIGPARSER_H

#include <cstdint>

class KeyConfigResult {
    public:
        KeyConfigResult();

    private:
        bool valid;
};

class KeyConfigSource {
    public:
        virtual uint8_t* GetBuffer() = 0;
        virtual uint32_t GetCount() = 0;
        virtual void InputUsed(uint32_t count) = 0;
};

class KeyConfigParser {
    public:
        KeyConfigParser();

        KeyConfigResult Parse(KeyConfigSource &source);
        void Reset();

    private:

};

#endif