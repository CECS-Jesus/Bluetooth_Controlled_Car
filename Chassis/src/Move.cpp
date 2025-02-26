#include "Move.h"

#define DIRECTION  (*((volatile unsigned long *)0x4002403C))
#define FORWARD    0x0F
#define BACKWARD   0x0A
#define LEFTPIVOT  0x09
#define RIGHTPIVOT 0x06
#define L_MOTOR    0x02
#define R_MOTOR    0x01

void Move::forward() {
    LED = Green;
    DIRECTION = FORWARD;
    PWM0_ENABLE_R |= L_MOTOR;
    PWM0_ENABLE_R |= R_MOTOR;
}

void Move::backward() {
    LED = Blue;
    DIRECTION = BACKWARD;
    PWM0_ENABLE_R |= L_MOTOR;
    PWM0_ENABLE_R |= R_MOTOR;
}

void Move::leftPivot() {
    LED = Yellow;
    DIRECTION = LEFTPIVOT;
    PWM0_ENABLE_R |= L_MOTOR;
    PWM0_ENABLE_R |= R_MOTOR;
}

void Move::rightPivot() {
    LED = Purple;
    DIRECTION = RIGHTPIVOT;
    PWM0_ENABLE_R |= L_MOTOR;
    PWM0_ENABLE_R |= R_MOTOR;
}

void Move::leftTurn() {
    LED = Yellow;
    DIRECTION = FORWARD;
    PWM0_ENABLE_R &= ~L_MOTOR;
    PWM0_ENABLE_R |= R_MOTOR;
}

void Move::rightTurn() {
    LED = Purple;
    DIRECTION = FORWARD;
    PWM0_ENABLE_R |= L_MOTOR;
    PWM0_ENABLE_R &= ~R_MOTOR;
}

void Move::leftBackTurn() {
    LED = Blue;
    DIRECTION = BACKWARD;
    PWM0_ENABLE_R &= ~L_MOTOR;
    PWM0_ENABLE_R |= R_MOTOR;
}

void Move::rightBackTurn() {
    LED = Blue;
    DIRECTION = BACKWARD;
    PWM0_ENABLE_R |= L_MOTOR;
    PWM0_ENABLE_R &= ~R_MOTOR;
}

void Move::stop() {
    LED = Dark;
    PWM0_ENABLE_R &= ~L_MOTOR;
    PWM0_ENABLE_R &= ~R_MOTOR;
}
