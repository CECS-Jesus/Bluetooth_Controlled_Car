#include "Motors.h"

uint64_t Motors::currDuty = STOP; // same name as original

void Motors::init() {
    currDuty = STOP;
    rightMotorInit();
    leftMotorInit();
    motorDirectionInit();
}

//--------------------------------------------
// These three initialization functions
// match your original code exactly
//--------------------------------------------
void Motors::leftMotorInit() {
    SYSCTL_RCGCPWM_R  |= 0x01;
    SYSCTL_RCGCGPIO_R |= 0x02;
    GPIO_PORTB_AFSEL_R  |= 0x80;
    GPIO_PORTB_PCTL_R  &= ~0xF0000000;
    GPIO_PORTB_PCTL_R  |=  0x40000000;
    GPIO_PORTB_AMSEL_R &= ~0x80;
    GPIO_PORTB_DEN_R   |= 0x80;
    SYSCTL_RCC_R       |= SYSCTL_RCC_USEPWMDIV;
    SYSCTL_RCC_R       &= ~SYSCTL_RCC_PWMDIV_M;
    SYSCTL_RCC_R       += SYSCTL_RCC_PWMDIV_2;
    PWM0_0_CTL_R        = 0;
    PWM0_0_GENB_R       = (PWM_0_GENB_ACTCMPBD_ONE | PWM_0_GENB_ACTLOAD_ZERO);
    PWM0_0_LOAD_R       = PERIOD - 1;
    PWM0_0_CMPB_R       = 0;
    PWM0_0_CTL_R       |= 0x00000001;
    PWM0_ENABLE_R      |= 0x00000002;
}

void Motors::rightMotorInit() {
    SYSCTL_RCGCPWM_R  |= 0x01;
    SYSCTL_RCGCGPIO_R |= 0x02;
    while((SYSCTL_RCGCGPIO_R & 0x02) == 0) {}
    GPIO_PORTB_AFSEL_R |= 0x40;
    GPIO_PORTB_PCTL_R  &= ~0x0F000000;
    GPIO_PORTB_PCTL_R  |= 0x04000000;
    GPIO_PORTB_AMSEL_R &= ~0x40;
    GPIO_PORTB_DEN_R   |= 0x40;
    GPIO_PORTB_DR8R_R  |= 0xC0;
    SYSCTL_RCC_R        = 0x00100000 | (SYSCTL_RCC_R & ~0x001E0000);
    PWM0_0_CTL_R        = 0;
    PWM0_0_GENA_R       = 0xC8;
    PWM0_0_LOAD_R       = PERIOD - 1;
    PWM0_0_CMPA_R       = 0;
    PWM0_0_CTL_R       |= 0x00000001;
    PWM0_ENABLE_R      |= 0x00000001;
}

void Motors::motorDirectionInit() {
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;
    while((SYSCTL_RCGC2_R & SYSCTL_RCGC2_GPIOE) != SYSCTL_RCGC2_GPIOE) {}
    GPIO_PORTE_AMSEL_R &= ~0x0F;
    GPIO_PORTE_PCTL_R  &= ~0x0000FFFF;
    GPIO_PORTE_DIR_R   |= 0x0F;
    GPIO_PORTE_AFSEL_R &= ~0x0F;
    GPIO_PORTE_DEN_R   |= 0x0F;
}

//--------------------------------------------
// Same EXACT function logic as your original
//--------------------------------------------
void Motors::pwmDuty(unsigned long dutyL, unsigned long dutyR) {
    PWM0_0_CMPA_R = dutyR - 1;
    PWM0_0_CMPB_R = dutyL - 1;
}

unsigned long Motors::getCurrDuty() {
    return (unsigned long)currDuty;
}

void Motors::incrementSpeed() {
    // EXACT copy from your original:
    // if (currDuty + SPEED_STEP < PERIOD) currDuty += SPEED_STEP; else currDuty = PERIOD - 1;
    if((currDuty + SPEED_STEP) < PERIOD) {
        currDuty += SPEED_STEP;
    } else {
        currDuty = PERIOD - 1;  
    }
    pwmDuty(currDuty, currDuty);
}

void Motors::decrementSpeed() {
    // EXACT copy from your original:
    // if (0 < currDuty - SPEED_STEP) currDuty -= SPEED_STEP; else currDuty = STOP;
    if(0 < (currDuty - SPEED_STEP)) {
        currDuty -= SPEED_STEP;
    } else {
        currDuty = STOP;
    }
    pwmDuty(currDuty, currDuty);
}

//--------------------------------------------
// Old C function wrappers
//--------------------------------------------
void Motors_Init(void) {
    Motors::init();
}
void PWM_Duty(unsigned long dutyL, unsigned long dutyR) {
    Motors::pwmDuty(dutyL, dutyR);
}
unsigned long GetCurrDuty(void) {
    return Motors::getCurrDuty();
}
void IncrementSpeed(void) {
    Motors::incrementSpeed();
}
void DecrementSpeed(void) {
    Motors::decrementSpeed();
}

