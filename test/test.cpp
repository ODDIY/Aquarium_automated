//
// Created by Oliver on 18.10.2018.
//

#include "pwmdummy.h"
#include "config_dummy.h"
#include "../src/Licht.h"

ConfigDummy config;
PwmDummy pwm;
Licht licht(&pwm, &config);



int main() {
    config.setup();
    pwm.begin();
    licht.setup();

    config.setFader_fadeinout(FAD_R, 0, 5000, 4095, 6500, 11000, 1024);
    config.setFader_fadeinout(FAD_B, 500, 5500, 4095, 6500, 11000, 1024);
    config.setFader_fadein(FAD_WW, 1500, 6500, 4095);
    config.setFader_fadein(FAD_KW, 3000, 8000, 4095);
    config.setFader_fadein(FAD_RGB_R, 100, 5100, 4095);
    config.setFader_fadein(FAD_RGB_G, 1600, 9000, 4095);
    config.setFader_fadein(FAD_RGB_B, 700, 5700, 4095);


    printf("TEST EEPROM\n");
    for(int i = 0; i < 512; i+=4) {
        printf("%6d", config.readInt(i));
        if((i+4) % 40 == 0  ) {
            printf("\n");
        }
    }
    printf("\n");

    unsigned long time = 0;


    while (time < 60000) {
        licht.update(time);
        printf("%d ", time);
        pwm.debug(0, 7);

        if (time == 0) {
            licht.aus(1);
        }

        if (time == 100000) {
            licht.aus(1);
        }

        time++;
        time++;
        time++;
        time++;
        time++;
    }


    return 0;
}


