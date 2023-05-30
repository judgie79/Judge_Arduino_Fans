#ifndef __FANCONTROL_H
#define __FANCONTROL_H

#include "Arduino.h"

class FanControl
{
private:
    /* data */

    #if !defined(ESP32)
    void setupTimer();
    void setPWM1A(float f);
    void setPWM1B(float f);
    #else
    const int pwmFreq              = 25000;
    const int pwmChannel           = 0;
    const int pwmResolution        = 8;
    uint8_t channel;
    #endif
    uint8_t pin;
public:
    FanControl();
    void Begin(uint8_t pin);
    #if defined(ESP32)
    void Begin(uint8_t pin, uint8_t channel);
    #endif
    void SetFanSpeed(int speed);
    void SetFanSpeedPercent(float speedInPercent);
};

#endif