#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <stdint.h>
#include "tm4c123gh6pm.h"

class Bluetooth {
public:
    static void init();
    static void uart1Init();
    static unsigned char uart1InChar();
};

#endif
