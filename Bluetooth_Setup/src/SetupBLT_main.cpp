#include <stdint.h>
#include <string.h>
#include "tm4c123gh6pm.h"
#include "UART0.h"
#include "Bluetooth.h"

int main(void) {
    // Create UART0 and Bluetooth objects
    UART0 pc;
    Bluetooth blt;

    // Initialize both
    pc.init();
    blt.init();

    // Setup message for pc terminal
    pc.outString(
        ">>>Welcome to Serial Terminal.<<< \r\n"
        ">>>This is the setup program for HC-05 Bluetooth module.<<< \r\n"
        ">>>You are 'AT' Command Mode.<<< \r\n"
        ">>>Type 'AT' Command. Example: AT+NAME=YourName<<< \r\n"
    );

    char userInput[66];
    char output[66];
    const char newline[] = "\r\n";

    while(1) {
        // Prompt user in terminal
        pc.nextLine();
        pc.inString(userInput, sizeof(userInput));

        // Send user input to Bluetooth
        blt.outString(userInput);
        blt.outString(newline);

        // Wait for Bluetooth to finish transmitting
        while((UART1_FR_R & UART_FR_BUSY) != 0) {}

        // Get response from Bluetooth
        blt.inString(output);
        pc.nextLine();
        pc.outString(output);
        pc.nextLine();

        // If user typed something containing '?'
        // The HC-05 may send an extra response
        // e.g., AT+VERSION?
        // Edge case for question mark
        if(userInput[7] == '?') {
            blt.inString(output);
            pc.outString(output);
            pc.nextLine();
        }
    }

    // Should never get here
    return 0;
}
