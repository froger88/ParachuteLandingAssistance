// Access to the Arduino Libraries
#include <Arduino.h>

#define PRODUCTION_MODE
//#define TEST_MODE

#ifdef PRODUCTION_MODE
#include "beeper.h"
#include "proximitysensor.h"
#include "math.h"

int main()
{
    // Initialize Arduino Librairies
    init();
    /*
     * Initialize serial connection
     * For calibration/debbuging purposes
     */
    Serial.begin(115200);

    Serial.println("Good Morning seal!");

    // beeper on pin 3
    Beeper Beeper1(3);

    // trigger pin - 10, echo pin - 9
    ProximitySensor S1(10, 9);

    // trigger pin - 8, echo pin - 7
    ProximitySensor S2(8, 7);


    // 1s blocking beep after turn on to say 'im turned on'
    Beeper1.beep(1000);

    /*
     * wait 100s (60s of freefall + 40s of opening and
     * flying near ground
    */
    delay(3000);

    /*
     * three 1s beeps with extra 1s delay
     * just to say 'im watching'
     */
//    for(int i=0;i<3; ++i)
//    {
//        Beeper1.beep(1000);
//        if(i < 2)
//        {
//            delay(1000);
//        }
//    }

    // set CURRENT_H to 1000 cm (10m)
    int UNDEFINED = 1000;
    int CURRENT_H = UNDEFINED;
    int CURRENT_L1;
    int CURRENT_L2;

    while (true)
    {
        CURRENT_L1 = S1.Get();
        Serial.print("S1: ");
        Serial.println(CURRENT_L1);

        CURRENT_L2 = S2.Get();
        CURRENT_L2= UNDEFINED;
        Serial.print("S2: ");
        Serial.println(CURRENT_L2);

        if (CURRENT_L1 < CURRENT_H)
        {
            CURRENT_H = CURRENT_L1;
        }
        if( CURRENT_L2 < CURRENT_H)
        {
            CURRENT_H = CURRENT_L2;
        }
        if (CURRENT_L1 != UNDEFINED && CURRENT_L2 != UNDEFINED)
        {
            long L1 = CURRENT_L1;
            long L2 = CURRENT_L2;
            long L3 = sqrt(L1*L1 + L2*L2);
            CURRENT_H = (L1*L2)/L3;
        }
        Serial.print("H: ");
        Serial.println(CURRENT_H);

        Serial.println("-------------");

        if (CURRENT_H > 700 || CURRENT_H == UNDEFINED) {
            // 1s beep, 1s delay
            Beeper1.repeat(1000);
            Serial.println("\tBEEP H>700");
        }
        else if (CURRENT_H <= 700 && CURRENT_H > 500)
        {
            // 0.5s beep, 0.5s delay
            Beeper1.repeat(500);
            Serial.println("\tBEEP H<=700 && H>500");
        } else if (CURRENT_H <= 500 && CURRENT_H > 250) {
            // 0.3s beep, 0.3s delay
            Beeper1.repeat(300);
            Serial.println("\tBEEP H<=500&& H>170");
        } else if (CURRENT_H <= 250 && CURRENT_H > 170) {
            // 0.075s beep, 0.075s delay
            Beeper1.repeat(75);
            Serial.println("\tBEEP H<=250 && H>170");

        } else {
            // continous beep for 10s
            Serial.println("\tGONNA CONTIONUSLY BEEP");
            Beeper1.beep(10000);
            break;
        }

        // asynchronously update Beeper
        Beeper1.update();

        // delay 10ms for battery live and measurement precission
        delay(10);
    }
    return 0;
}
#endif

#ifdef TEST_MODE

#include "beeper.h"
#include "math.h"
#include "test.h"

int main()
{
    // Initialize Arduino Librairies
    init();
    Beeper t(2);
    Beeper t2(3);
    Beeper t3(4);
    Beeper t4(5);
    Beeper t5(6);
    Beeper t6(7);
    Beeper t7(8);
    Beeper t8(9);
    Beeper t9(10);
    Beeper t10(11);
    Beeper t11(12);
    Beeper t12(13);

    t.beep(10000, true);
    t2.beep(10000, true);
    t3.beep(10000, true);
    t4.beep(10000, true);
    t5.beep(10000, true);
    t6.beep(10000, true);
    t7.beep(10000, true);
    t8.beep(10000, true);
    t9.beep(10000, true);
    t10.beep(10000, true);
    t11.beep(10000, true);
    t12.beep(10000, true);

    delay(10000);
    t.beep(10000);
    // check all digital pinsj m

    Test x;
    //x.test_digital_pins();

    // beeper on pin 3
    //Beeper Beeper1(3);
    //Test t;

    //t.beeper_test(Beeper1);
    return 0;
}
#endif
