#ifndef UART0_H
#define UART0_H

#include <stdint.h>

// Match the #defines in original code
static const uint8_t CR = 0x0D;
static const uint8_t LF = 0x0A;
static const uint8_t BS = 0x08;
static const uint8_t SP = 0x20;

class UART0 {
public:
    UART0() = default;
    // Call init() to configure UART0 hardware
    void init();

    // Output 8-bit data to UART0
    void outChar(uint8_t data);

    // Output a NULL-terminated string to UART0
    void outString(const char *pt);

    // Move cursor to next line on UART0
    void nextLine();

    // Wait for new serial port input (blocks until received)
    uint8_t inChar();

    // Accept ASCII characters (up to max-1) until Enter (CR).
    // Echoes each character, handles backspace, and null-terminates the result.
    // Returns number of characters read (not counting the null terminator).
    uint16_t inString(char *bufPt, uint16_t max);
};

#endif // UART0_H

