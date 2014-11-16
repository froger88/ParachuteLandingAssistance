#include "test.h"

Test::Test()
{
}

void Test::beeper_test(Beeper& Beeper1)
{
    // 1s blocking beep after turn on to say 'im turned on'
//    Beeper1.beep(1000);

//    // just delay 3000
//    delay(3000);

//    /*
//     * three 1s beeps with extra 1s delay
//     * just to say 'im watching'
//     */
//    for(int i=0;i<3; ++i) {
//        Beeper1.beep(1000);
//        delay(1000);
//    }

//    delay(3000);

    int UNDEFINED = 10000;
    int CURRENT_H = 10000;
    int CURRENT_L1 = 10000;
    int CURRENT_L2 = 10000;

    for (int i=1000;i >0; --i) {
        CURRENT_L1 = i;
        //CURRENT_L2 = i;

        if (CURRENT_L1 < CURRENT_H)
        {
            CURRENT_H = CURRENT_L1;
        }
        if( CURRENT_L2 < CURRENT_H)
        {
            CURRENT_H = CURRENT_L1;
        }
        if (CURRENT_L1 != UNDEFINED && CURRENT_L2 != UNDEFINED)
        {
            long L1 = CURRENT_L1;
            long L2 = CURRENT_L2;
            long L3 = sqrt(L1*L1 + L2*L2);
            CURRENT_H = (L1*L2)/L3;
        }

        if (CURRENT_H > 700 || CURRENT_H == UNDEFINED) {
            // 1s beep, 1s delay
            Beeper1.repeat(1500);
        }
        else if (CURRENT_H <= 700 && CURRENT_H > 500)
        {
            // 0.5s beep, 0.5s delay
            Beeper1.repeat(500);
        } else if (CURRENT_H <= 500 && CURRENT_H > 250) {
            // 0.3s beep, 0.3s delay
            Beeper1.repeat(300);
        } else if (CURRENT_H <= 250  && CURRENT_H > 170) {
            // 0.075s beep, 0.075s delay
            Beeper1.repeat(75);
        } else {
            // continous beep for 10s
            Beeper1.beep(5000, true);
            break;
        }
        Beeper1.update();
        // simulate 1cm every 20ms
        delay(20);
    }
}


void Test::test_digital_pins()
{
    for(int i=0; i<3; ++i) {
        for(int j=2; j<14; ++j){
            Beeper test_pin(j);
            test_pin.beep(1000,false);
            delay(1000);

        }
    }
}
