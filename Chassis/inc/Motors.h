#ifndef MOTORS_H
#define MOTORS_H

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "PLL.h"

#define STOP        1
#define MAX_SPEED   (PERIOD - 1)
#define HALF_SPEED  (PERIOD * 0.5)
#define SPEED_STEP  (PERIOD * 0.1)

// C++ Motors class
class Motors {
public:
    static void init();
    static void pwmDuty(unsigned long dutyL, unsigned long dutyR);
    static unsigned long getCurrDuty();
    static void incrementSpeed();
    static void decrementSpeed();
private:
    static void leftMotorInit();
    static void rightMotorInit();
    static void motorDirectionInit();
    static uint64_t currDuty;
};

#endif // MOTORS_H

