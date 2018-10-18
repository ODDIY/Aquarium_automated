//
// Created by Oliver on 18.10.2018.
//

#include "pwmdummy.h"
#include "config_dummy.h"

#define TEST
#include "../src/Licht.h"

ConfigDummy config;
PwmDummy pwm;
Licht licht(&pwm, &config);



int main() {
    config.setup();
    pwm.begin();
    licht.setup();

    config.setFader_fadeinout(FAD_R_rise, 0, 24000, 4095, 45000, 66000, 1024);
    config.setFader_fadeinout(FAD_B_rise, 6000, 34500, 4095, 45000, 66000, 1024);

    config.setFader_fadeinout(FAD_R_set, 0, 24000, 4095, 45000, 66000, 1024);
    config.setFader_fadeinout(FAD_B_set, 6000, 34500, 1024, 45000, 66000, 1024);

    config.setFader_fadein(FAD_WW_rise, 12000, 36000, 4095);
    config.setFader_fadein(FAD_KW_rise, 30000, 60000, 4095);

    config.setFader_fadein(FAD_WW_set, 0, 36000, 4095);
    config.setFader_fadein(FAD_KW_set, 30000, 60000, 4095);

    config.setFader_fadeinout(FAD_RGB_R_rise, 0, 24000, 4095, 45000, 66000, 1024);
    config.setFader_fadeinout(FAD_RGB_G_rise, 24000, 42000, 4095, 45000, 66000, 1024);
    config.setFader_fadeinout(FAD_RGB_B_rise, 6000, 34500, 4095, 45000, 66000, 1024);

    config.setFader_fadeinout(FAD_RGB_R_set, 0, 24000, 4095, 45000, 66000, 1024);
    config.setFader_fadeinout(FAD_RGB_G_set, 24000, 42000, 1024, 45000, 66000, 1024);
    config.setFader_fadeinout(FAD_RGB_B_set, 6000, 34500, 1024, 45000, 66000, 1024);

    printf("TEST EEPROM\n");
    for(int i = 0; i < 512; i+=4) {
        printf("%6d", config.readInt(i));
        if((i+4) % 40 == 0  ) {
            printf("\n");
        }
    }
    printf("\n");

    unsigned long time = 0;


    while (time < 140000) {
        licht.update(time);
        printf("%d ", time);
        pwm.debug(0, 7);

        if (time == 0) {
            licht.an(1);
        }

        if (time == 70000) {
            licht.aus(1);
        }

        time++;
    }


    return 0;
}


