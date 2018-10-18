//
// Created by Oliver on 18.10.2018.
//

#ifndef AQUARIUM_AUTOMATED_PWMDUMMY_H
#define AQUARIUM_AUTOMATED_PWMDUMMY_H

#include <stdint.h>

class PwmDummy {
public:
    explicit PwmDummy(uint8_t addr = 0x40) {}
    PwmDummy(uint8_t i2c_addr, float freq){}

    void begin() {}
    void reset() {}
    void setFreq(float freq) {}
    void setServo(uint16_t min_pulse_width, uint16_t max_pulse_width){}

    void pwmWrite(uint8_t num, uint16_t val){}
    void angleWrite(uint8_t channel, uint8_t angle){}
};



#endif //AQUARIUM_AUTOMATED_PWMDUMMY_H
