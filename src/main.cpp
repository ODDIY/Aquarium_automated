#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <SunFounder_PCA9685.h>
#include <XPT2046_Touchscreen.h>
#include "gui.h"


Gui gui = Gui();



void setup() {
        // put your setup code here, to run once:
        Serial.begin(9600);
        Serial.println("ILI9341 Test!");
        gui.setup();
}

void loop() {
        // put your main code here, to run repeatedly:
        gui.update();
}
