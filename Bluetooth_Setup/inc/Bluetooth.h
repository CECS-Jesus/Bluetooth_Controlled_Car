#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <stdint.h>

class Bluetooth {
public:
    Bluetooth() = default;
    // Call init() to configure UART1 hardware
    void init();

    // Output 8-bit data to UART1
    void outChar(uint8_t data);

    // Output a NULL-terminated string to UART1
    void outString(const char *pt);

    // Wait for new serial port input on UART1
    uint8_t inChar();

    // Capture a string from the Bluetooth module until "\r\n"
    // The final "\r\n" is removed, replaced with '\0'
    void inString(char *bufPt);
};

#endif // BLUETOOTH_H
