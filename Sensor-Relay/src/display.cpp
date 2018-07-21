#include "display.h"

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

void dummy_func() {
    alpha4.begin(0x70);
    alpha4.writeDigitAscii(3, '4');
    alpha4.writeDisplay();
}
