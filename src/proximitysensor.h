#ifndef PROXIMITYSENSOR_H
#define PROXIMITYSENSOR_H

#include <Arduino.h>


/**
 * @brief The ProximitySensor class - ultrasonic sensors handling
 *
 *      class used to handle ultrasonic sesnors from US-020 series
 *      (up to 7m distance, 3cm precission range +/- 1%)
 */
class ProximitySensor
{
public:
    /**
     * @brief ProximitySensor - constructor
     * @param echo_pin - digital input echo pin
     * @param trigger_pin - digital output trigger pin
     */
    ProximitySensor(int echo_pin, int trigger_pin);

    /**
     * @brief ProximitySensor - [DO NOT USE] copy constructor.
     */
    ProximitySensor(const ProximitySensor &){}

    /**
     * @brief ~ProximitySensor - destructor
     */
    ~ProximitySensor();

    /**
     * @brief Get - blocking method
     *      send pulse to trigger_pin and wait on pulse_in
     *      for maximum TIMEOUT microseconds. Then calculate the
     *      distance in cm. Anomaly protection calculated for
     *      student/night parachute jumps.
     *
     * @return distance in cm
     */
    int Get();

private:

    // echo pin (input)
    int echo_pin;

    // trigger pin (output)
    int trigger_pin;

    /*
     * value treated as UNDEFINED (more than sensor can detect)
     * at this project, UNDEFINED is set to 1000 (cm)
     */
    int UNDEFINED;

    /*
     * timeout in microseconds - after this time measure should be setted to
     *      UNDEFINED (6000 us == 0.06s == time needed by sound to reach 10m
     *      in both ways)
     */
    unsigned long TIMEOUT;

};

#endif // PROXIMITYSENSOR_H
