//
// Created by Oliver on 18.10.2018.
//

#ifndef AQUARIUM_AUTOMATED_PWMDUMMY_H
#define AQUARIUM_AUTOMATED_PWMDUMMY_H

#include <stdint.h>
#include <stdio.h>


#define PWM_PIN_WW 0
#define PWM_PIN_KW 1
#define PWM_PIN_R 2
#define PWM_PIN_B 3
#define PWM_PIN_RGB_R 4
#define PWM_PIN_RGB_G 5
#define PWM_PIN_RGB_B 6

class PwmDummy {
    FILE *pFile;
    uint16_t channels[16];
public:
    explicit PwmDummy(uint8_t addr = 0x40) {
        pFile = fopen("file.log", "wb");
        fprintf(pFile, "WW KW R B RGB_R RGB_G RGB_B\n");

        reset();
    }

    PwmDummy(uint8_t i2c_addr, float freq) {
        pFile = fopen("file.log", "wb");
        fprintf(pFile, "WW KW R B RGB_R RGB_G RGB_B\n");
        reset();
    }

    ~PwmDummy() {
        fclose(pFile);
    }
    void begin() {}

    void reset() {
        for (int i = 0; i < 16; i++) {
            channels[i] = 0;
        }
    }
    void setFreq(float freq) {}
    void setServo(uint16_t min_pulse_width, uint16_t max_pulse_width){}

    void pwmWrite(uint8_t num, uint16_t val) { channels[num] = val; }
    void angleWrite(uint8_t channel, uint8_t angle){}

    void debug(int s, int e) {
        for (int i = s; i < e; i++) {
            printf("ch%d:%d ", i, channels[i]);
            fprintf(pFile, "%d ", channels[i]);
        }
        printf("\n");
        fprintf(pFile, "\n");
    }
};



#endif //AQUARIUM_AUTOMATED_PWMDUMMY_H
