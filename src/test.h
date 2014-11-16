#ifndef TEST_H
#define TEST_H

#include "Arduino.h"
#include "beeper.h"

class Test
{
public:
    Test();

    /**
     * @brief simulation - method simulate ProximitySensor results,
     *      used to test Beeper
     */
    void beeper_test(Beeper& Beeper1);
    void test_digital_pins();
};

#endif // TEST_H
