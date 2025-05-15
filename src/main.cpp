extern "C" {
    #include "Cube/main.h"
}

int main() {

    HAL_Init();
    SystemClock_Config();
  
    while(1) {
        asm("nop");
    }

    return 0;
}