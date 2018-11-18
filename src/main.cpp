#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <SunFounder_PCA9685.h>
#include <XPT2046_Touchscreen.h>

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "gui.h"
#include "Licht.h"
#include "Config.h"
#include "Timer.h"

const char *ssid     = "XXXXXXX";
const char *password = "XXXXXXX";

Config config = Config();
PCA9685 pwm = PCA9685();
Licht licht = Licht(&pwm, &config);
Gui gui = Gui(&config, &licht);
WiFiUDP ntpUDP = WiFiUDP();
NTPClient timeClient = NTPClient(ntpUDP);
Timer timer = Timer(&timeClient, &config, &licht);

void setup() {
        // put your setup code here, to run once:
        Serial.begin(9600);
        WiFi.begin(ssid, password);
        Serial.println("ILI9341 Test!");
        pwm.begin();
        pwm.setFreq(1000);
        gui.setup();
        config.setup();

        licht.setup();


        while ( WiFi.status() != WL_CONNECTED ) {
                delay ( 500 );
                Serial.print ( "." );
        }

        timer.setup();
}

void loop() {
        // put your main code here, to run repeatedly:
        gui.update();
        licht.update(millis());
        timer.update();
}
