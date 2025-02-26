#ifndef MOVE_H
#define MOVE_H

#include "LED.h"
#include "tm4c123gh6pm.h"

class Move {
public:
    static void forward();
    static void backward();
    static void leftPivot();
    static void rightPivot();
    static void leftTurn();
    static void rightTurn();
    static void leftBackTurn();
    static void rightBackTurn();
    static void stop();
};

#endif
