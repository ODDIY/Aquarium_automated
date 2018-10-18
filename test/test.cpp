//
// Created by Oliver on 18.10.2018.
//

#include "pwmdummy.h"
#include "config_dummy.h"

ConfigDummy config;
PwmDummy pwm;

void setup();
void loop();

int main() {

    config.dummyInit();
/*
for(int i = 0; i < 7; i++) {
    config.setFader(i,0, 1000 + i*1000);
    config.setFader(i,1, 20000 + i*1000);
    config.setFader(i,2, 4000 + i);
    config.setFader(i,3, 30000 + i*1000);
    config.setFader(i,4, 40000 + i*1000);
    config.setFader(i,5, 512 + i*100);
}*/



    printf("TEST EEPROM\n");
    for(int i = 0; i < 512; i+=4) {
        printf("%6d", config.readInt(i));
        if((i+4) % 40 == 0  ) {
            printf("\n");
        }
    }



    setup();


    bool running = true;
    while (running) {
        loop();
        running = false;
    }



    return 0;
}


void setup() {


}


void loop() {



}