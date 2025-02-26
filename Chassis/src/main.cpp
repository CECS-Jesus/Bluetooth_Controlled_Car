#include <cctype>        
#include "PLL.h"
#include "LED.h"
#include "Motors.h"
#include "Bluetooth.h"
#include "Move.h"

#define MAX_ASCII 255

// Forward declarations for local helper functions
static void systemInit();
static void invalidInput();

// Array of function pointers for handling user commands
static void (*moveChoices[MAX_ASCII])(void);

int main() {
    // Initialize system peripherals
    systemInit();

    for(int i = 0; i < MAX_ASCII; i++) {
        moveChoices[i] = invalidInput;
    }
    // User choices to control chassis via bluetooth
    moveChoices['f'] = [] { Move::forward(); };
    moveChoices['b'] = [] { Move::backward(); };
    moveChoices['l'] = [] { Move::leftTurn(); };
    moveChoices['r'] = [] { Move::rightTurn(); };
    moveChoices['s'] = [] { Move::stop(); };

    // Adjust Motor speed
    moveChoices['u'] = [] { Motors::incrementSpeed(); };
    moveChoices['d'] = [] { Motors::decrementSpeed(); };

    //Main loop waits for chars from UART1 (user).
    while(true) {
        // Read one char from Bluetooth (UART1)
        unsigned char c = Bluetooth::uart1InChar();  
        // Convert to lowercase so uppercase inputs also work
        unsigned char cmd = static_cast<unsigned char>(std::tolower(c));
        // Perform user function
        moveChoices[cmd]();
    }
}

static void systemInit() {
    PLL::init();               // Set up PLL, system clock
    LEDController::init();     // Configure onboard LEDs
    Motors::init();            // Configure motor PWM
    Bluetooth::init();         // Initialize UART for Bluetooth
}
