#ifndef PLL_H
#define PLL_H

#include "tm4c123gh6pm.h"

#define SYSDIV2      7
#define BUS_MHZ_FREQ (400 / (SYSDIV2 + 1))
#define PERIOD       (BUS_MHZ_FREQ * 1000)

class PLL {
public:
    static void init();
};

#endif
