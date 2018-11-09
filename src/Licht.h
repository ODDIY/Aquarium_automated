#ifndef LICHT_H
#define LICHT_H


#ifdef TEST
//Test Dummys
#include "../test/config_dummy.h"
#include "../test/pwmdummy.h"
//Alias namen für die dummies;
typedef PwmDummy PCA9685;
typedef ConfigDummy Config;
#else

#include <SunFounder_PCA9685.h>
#include "Config.h"

#endif

#include "fade.h"


#define FADE_TIME_MAX 68000
#define PWM_PIN_WW 0
#define PWM_PIN_KW 1
#define PWM_PIN_R 2
#define PWM_PIN_B 3
#define PWM_PIN_RGB_R 4
#define PWM_PIN_RGB_G 5
#define PWM_PIN_RGB_B 6

#define PWM_PIN_CO2 7

/**
  * class Licht
  *
  */
class Licht
{
private:
    //Test Dummys Hier mussen dann die echten Objecte rein;
    PCA9685 * pwm;
    Config * config;

    Fader rF_rise;
    Fader bF_rise;
    Fader wwF_rise;
    Fader kwF_rise;
    Fader rgb_rF_rise;
    Fader rgb_gF_rise;
    Fader rgb_bF_rise;

    Fader rF_set;
    Fader bF_set;
    Fader wwF_set;
    Fader kwF_set;
    Fader rgb_rF_set;
    Fader rgb_gF_set;
    Fader rgb_bF_set;

    uint16_t rgb_r;
    uint16_t rgb_g;
    uint16_t rgb_b;
    uint16_t Rval;
    uint16_t Bval;
    uint16_t ww;
    uint16_t kw;
    bool co2;
    unsigned long lasttime; //last update time
    unsigned long starttime; //sunrise sunset time
    bool start; //wird gesetzt um den sunset/sunrise zu staten
    bool sunrise;
    bool sunset;
    int speed; // Geschwindichkeit des an / auschalten

public:
    // Empty Constructor
    Licht (PCA9685 *pwm, Config * config );


    // setup beim starten
    void setup ();

    // Fadet das licht nach bedarf an und aus Und steuert die C02 zufur
    void update (unsigned long milis);

    // gibt das signal das licht mit einer bestimmten geschwindichkeit zu starten
    void an (int speed);

    // Schaltet das licht mit einer bestimmten geschwindichket aus
    void aus (int speed);

    //liest die aktuellen fader werte aus dem speicher
    void readFaderValues();

    //Führt alle fader für eine bestimmte Zeit aus
    void runFaders(int time);

    // Schaltet sofort die RGB lampen auf einen bestimten wert
    void setRGB (uint16_t red, uint16_t green, uint16_t blue);
    void getRGB(uint16_t &red, uint16_t &green, uint16_t &blue) {red = rgb_r; green = rgb_g; blue=rgb_b;}

    // setzt die Warm Weiß sofort auf einen bestimmten wert
    void setWW (uint16_t value);
    uint16_t getWW() {return ww;}

    // setzt die Kalt Weiß sofort auf einen bestimmten wert
    void setKW (uint16_t value);
    uint16_t getKW() {return kw;}

    // setzt die Roten LEDs sofort auf einen bestimmten wert
    void setR (uint16_t value);
    uint16_t getR() {return Rval;}
    // setzt die Blauen LEDs sofort auf einen bestimmten wert
    void setB (uint16_t value);
    uint16_t getB() {return Bval;}

    void setCO2(bool on);

    //Gibt den CO2 status züruck
    bool getC02();

};

#endif // LICHT_H
