#ifndef TIMER_H
#define TIMER_H

#include "Config.h"
#include "Licht.h"
#include <NTPClient.h>


class Timer {
private:
    NTPClient* timeClient;
    Config* conf;
    Licht* licht;

    bool an = false;
    bool aus = true;
    int riseTimes[2];
    int fallTimes[2];
public:
    Timer(NTPClient* timeClient, Config* config, Licht* licht);
    void setup();
    void update();


};


#endif // LICHT_H