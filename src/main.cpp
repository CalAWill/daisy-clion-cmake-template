#include "daisy_seed.h"
using namespace daisy;

DaisySeed hw;

// Simple blink example
int main(void) {
    hw.Init();
    while(1) {
        hw.SetLed(true);
        System::Delay(500);
        hw.SetLed(false);
        System::Delay(500);
    }
}