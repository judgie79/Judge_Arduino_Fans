#ifndef __SpeedFanControl_H
#define __SpeedFanControl_H

#include "Arduino.h"
#include "FanControl.h"

class SpeedFanControl : public FanControl
{
private:

public:
    SpeedFanControl(/* args */);
    void SetSpeed(uint16_t speed);
    void Stop();
};

#endif