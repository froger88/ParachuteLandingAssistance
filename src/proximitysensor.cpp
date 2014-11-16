#include "proximitysensor.h"

/**
 * @brief ProximitySensor::ProximitySensor - constructor
 * @param echo_pin - digital input echo pin
 * @param trigger_pin - digital output trigger pin
 */
ProximitySensor::ProximitySensor(int echo_pin, int trigger_pin)
{
    // setup echo pin
    this->echo_pin = echo_pin;

    // setup trigger_pin
    this->trigger_pin = trigger_pin;

    // set to 1000 cm (10m)
    this->UNDEFINED = 1000;

    this->TIMEOUT = 60000;
}


/**
 * @brief ProximitySensor::~ProximitySensor - destructor
 */
ProximitySensor::~ProximitySensor()
{
    // nothing to do
}


/**
 * @brief ProximitySensor::Get - blocking method
 *      send pulse to trigger_pin and wait on pulse_in
 *      for maximum TIMEOUT microseconds. Then calculate the
 *      distance in cm. Anomaly protection calculated for
 *      student/night parachute jumps.
 *
 * @return distance in cm
 */
int ProximitySensor::Get()
{
    // setup pins
    pinMode(this->trigger_pin, OUTPUT);
    pinMode(this->echo_pin, INPUT);

    // send HIGH for 10ms
    digitalWrite(this->trigger_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->trigger_pin, LOW);

    /*
     * read reply
     * timeout:
     * t = 2 * 10 [m] / 340 [m/s] *  == 1/17s == 0.06s
     * t = 60000 us
     */
    int distance = pulseIn(this->echo_pin, HIGH)/2;//, this->TIMEOUT) / 2;

    /*
     * calculate distance in cm
     * in 1cm is reached by sound in 29 us at 340m/s sound speed
     */
    distance /= 29;

    // check results for bad data
    if(distance > 700 || distance < 10) {
        distance = this->UNDEFINED;
    }

    // return distance
    return distance;
}
