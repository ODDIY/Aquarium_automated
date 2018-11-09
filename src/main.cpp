#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <SunFounder_PCA9685.h>
#include <XPT2046_Touchscreen.h>
#include "gui.h"


Config config = Config();
PCA9685 pwm = PCA9685();
Licht licht = Licht(&pwm, &config);
Gui gui = Gui(&config, &licht);


void setup() {
        // put your setup code here, to run once:
        Serial.begin(9600);
        Serial.println("ILI9341 Test!");
        pwm.begin();
        pwm.setFreq(1000);
        gui.setup();
        config.setup();
        licht.setup();
}

void loop() {
        // put your main code here, to run repeatedly:
        gui.update();
        licht.update();
}
