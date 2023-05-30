#include "FanControl.h"

FanControl::FanControl()
{
}

#if defined(ESP32)
void FanControl::Begin(uint8_t pin, uint8_t channel)
{
    this->channel = channel;
    // configure Fan PWM functionalitites
    ledcSetup(channel, pwmFreq, pwmResolution);
  
    // attach the channel to the GPIO to be controlled
    ledcAttachPin(pin, channel);

    SetFanSpeed(0);
}
#endif


void FanControl::Begin(uint8_t pin)
{
    this->pin = pin;
#if defined(ESP32)
    Begin(pin, 0);
#else
    pinMode(pin,OUTPUT); //1A
    setupTimer1();
    if (pin == 9) {
        setPWM1A(0.0f); //set duty to 0% on pin 9
    } else if (pin == 10) {
        setPWM1B(0.0f); //set duty to 0% on pin 10
    }
#endif
}

void FanControl::SetFanSpeed(int speed) {
#if defined(ESP32)
    ledcWrite(this->channel, speed);
#else

    float speedInPercent = float(map(speed, 0, 255, 0, 100)) / 100;
    if (pin == 9) {
        setPWM1A(speedInPercent); //set duty to 0% on pin 9
    } else if (pin == 10) {
        setPWM1B(speedInPercent); //set duty to 0% on pin 10
    }
#endif
}

void FanControl::SetFanSpeedPercent(float speedInPercent) {
#if defined(ESP32)
    int speed = map(speedInPercent * 100, 0, 100, 0, 255);
    ledcWrite(this->channel, speed);
#else
    if (pin == 9) {
        setPWM1A(speedInPercent); //set duty to 0% on pin 9
    } else if (pin == 10) {
        setPWM1B(speedInPercent); //set duty to 0% on pin 10
    }
#endif
}

#if !defined(ESP32)
void Fan::setupTimer(uint8_t pin) {
//Set PWM frequency to about 25khz on pins 9,10 (timer 1 mode 10, no prescale, count to 320)
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
    TCCR1B = (1 << CS10) | (1 << WGM13);
    ICR1 = 320;
    OCR1A = 0;
    OCR1B = 0;
}

//equivalent of analogWrite on pin 9
void Fan::setPWM1A(float f) {
    f=f<0?0:f>1?1:f;
    OCR1A = (uint16_t)(320*f);
}
//equivalent of analogWrite on pin 10
void Fan::setPWM1B(float f) {
    f=f<0?0:f>1?1:f;
    OCR1B = (uint16_t)(320*f);
}

#endif