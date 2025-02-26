#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <stdint.h>
#include "tm4c123gh6pm.h"

class Bluetooth {
public:
    static void init();
    static void uart0Init();
    static void uart1Init();
    static void uart0OutChar(unsigned char data);
    static void uart0OutString(unsigned char* pt);
    static unsigned char uart1InChar();
    static void bltInString(unsigned char* bufPt);
};

#endif
