#include "Bluetooth.h"
#include "tm4c123gh6pm.h"

void Bluetooth::init() {
    // Enable Clocks
    SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART1; // activate UART1
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB; // activate Port B

    UART1_CTL_R &= ~UART_CTL_UARTEN;      // disable UART1

    // For 38400 baud (HC-05 default command mode), assuming 16 MHz:
    // IBRD = 16,000,000/(16*38400) ~ 26
    // FBRD = .04 * 64 ~ 3
    UART1_IBRD_R = 26;
    UART1_FBRD_R = 3;

    // 8-bit, no parity, one stop bit, FIFOs enabled
    UART1_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
    UART1_CTL_R |= 0x301;   // enable UART1, TXE, RXE

    // Configure PB1, PB0 for UART1
    GPIO_PORTB_AFSEL_R |= 0x03;
    GPIO_PORTB_DEN_R   |= 0x03;
    GPIO_PORTB_PCTL_R  = (GPIO_PORTB_PCTL_R & 0xFFFFFF00) + 0x00000011;
    GPIO_PORTB_AMSEL_R &= ~0x03;
}

void Bluetooth::outChar(uint8_t data) {
    // Wait for TX FIFO not full
    while((UART1_FR_R & UART_FR_TXFF) != 0) {}
    UART1_DR_R = data;
}

void Bluetooth::outString(const char *pt) {
    while(*pt) {
        outChar(static_cast<uint8_t>(*pt));
        pt++;
    }
}

uint8_t Bluetooth::inChar() {
    // Wait for RX FIFO not empty
    while((UART1_FR_R & UART_FR_RXFE) != 0) {}
    return static_cast<uint8_t>(UART1_DR_R & 0xFF);
}

void Bluetooth::inString(char *bufPt) {
    // Read until LF (0x0A). Expect replies end with "\r\n".
    uint8_t length = 0;
    const uint8_t LF = 0x0A;

    do {
        bufPt[length] = inChar();
        length++;
    } while(bufPt[length - 1] != LF);

    // Remove CR & LF at end, replace with null terminator
    // We expect last two chars: "\r\n"
    length -= 2;
    bufPt[length] = '\0';
}
