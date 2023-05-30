#include "SpeedFanControl.h"

SpeedFanControl::SpeedFanControl()
    : FanControl()
{

}

void SpeedFanControl::SetSpeed(uint16_t speed)
{
    SetFanSpeed(speed);
}

void SpeedFanControl::Stop()
{
    SetFanSpeed(0);
}