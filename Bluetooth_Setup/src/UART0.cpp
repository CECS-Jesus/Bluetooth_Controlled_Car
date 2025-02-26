#include "UART0.h"
#include "tm4c123gh6pm.h"

void UART0::init() {
    // Enable Clocks for UART0 and Port A
    SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0;  // activate UART0
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;  // activate port A

    UART0_CTL_R &= ~UART_CTL_UARTEN;       // disable UART0

    // Baud rate calculation: 
    // For 16 MHz system clock and 57600 baud:
    // IBRD = int(16,000,000 / (16 * 57600)) = 17
    // FBRD = round(0.36 * 64) = 23
    UART0_IBRD_R = 17;
    UART0_FBRD_R = 23;

    // 8-bit, no parity, one stop, FIFOs enabled
    UART0_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
    UART0_CTL_R |= 0x301;  // enable UART0, TXE, RXE

    // Configure PA1, PA0 as UART0
    GPIO_PORTA_AFSEL_R |= 0x03;
    GPIO_PORTA_DEN_R   |= 0x03;
    GPIO_PORTA_PCTL_R  = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011;
    GPIO_PORTA_AMSEL_R &= ~0x03;
}

void UART0::outChar(uint8_t data) {
    // Wait until TX FIFO not full
    while((UART0_FR_R & UART_FR_TXFF) != 0) {}
    UART0_DR_R = data;
}

void UART0::nextLine() {
    outChar(CR);
    outChar(LF);
}

void UART0::outString(const char *pt) {
    while(*pt) {
        outChar(static_cast<uint8_t>(*pt));
        pt++;
    }
}

uint8_t UART0::inChar() {
    // Wait until RX FIFO not empty
    while((UART0_FR_R & UART_FR_RXFE) != 0) {}
    return static_cast<uint8_t>(UART0_DR_R & 0xFF);
}

uint16_t UART0::inString(char *bufPt, uint16_t max) {
    uint16_t length = 0;
    uint8_t character;

    character = inChar();
    while(character != CR) {
        if(character == BS) {
            if(length > 0) {
                bufPt--;
                length--;
                outChar(BS);
            }
        } else if(length < (max - 1)) { 
            *bufPt = character;
            bufPt++;
            length++;
            outChar(character);
        }
        character = inChar();
    }
    *bufPt = 0; // Null-terminate
    return length;
}

