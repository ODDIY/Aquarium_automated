#include "Timer.h"


Timer::Timer(NTPClient *timeClient, Config* config, Licht* licht) {
        this->timeClient = timeClient;
        this->conf = config;
        this->licht= licht;
}


void Timer::update() {
        timeClient->update();

        int secondOfTheDay = TIME_TO_SEC(timeClient->getHours(),timeClient->getMinutes(),timeClient->getSeconds());


        //Serial.print("Time:");
        //Serial.print(timeClient->getFormattedTime());
        //Serial.print(":::");
        //Serial.println(secondOfTheDay);


        for (int i = 0; i < 2; ++i) {
                if(secondOfTheDay == riseTimes[i] && !an) {
                        Serial.println("TIMER LICHT AN");
                        licht->an(1);
                        an = true;
                        aus = false;
                }

                if(secondOfTheDay == fallTimes[i] && !aus) {
                        Serial.println("TIMER LICHT AUS");
                        licht->aus(1);
                        an = false;
                        aus = true;
                }
        }


}

void Timer::setup() {
        timeClient->begin();
        an = false;
        aus = true;

        riseTimes[0] = conf->getTimer(T_RISE1);
        riseTimes[1] = conf->getTimer(T_RISE2);
        fallTimes[0] = conf->getTimer(T_FALL1);
        fallTimes[1] = conf->getTimer(T_FALL2);

        timeClient->setTimeOffset(3600);
}
