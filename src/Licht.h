#ifndef LICHT_H
#define LICHT_H

//Test Dummys Hier müssen dann die echten klassen rein
#include "../test/config_dummy.h"
#include "../test/pwmdummy.h"

#include "fade.h"

//Alias namen für die dummies;
typedef PwmDummy PCA9685;
typedef ConfigDummy Config;

/**
  * class Licht
  * 
  */

#define PWM_PIN_WW 0
#define PWM_PIN_KW 1
#define PWM_PIN_R 2
#define PWM_PIN_B 3
#define PWM_PIN_RGB_R 4
#define PWM_PIN_RGB_G 5
#define PWM_PIN_RGB_B 6



class Licht
{
private:
    //Test Dummys Hier mussen dann die echten Objecte rein;
    PCA9685 * pwm;
    Config * config;

    Fader wwF;
    Fader kwF;
    Fader rF;
    Fader bF;
    Fader rgb_rF;
    Fader rgb_gF;
    Fader rgb_bF;

    unsigned long lasttime;
    unsigned long starttime;
    bool sunrise;
    bool sunset;
    int speed;

public:
  // Empty Constructor
  Licht (PCA9685 *pwm, Config * config );



  // setup beim starten
  void setup ();

  //liest die aktuellen fader werte aus dem speicher
  void readFaderValues();

  // Fadet das licht nach bedarf an und aus Und steuert die C02 zufur
  void update (unsigned long milis);


  // gibt das signal das licht mit einer bestimmten geschwindichkeit zu starten
  void an (int speed);

  // Schaltet das licht mit einer bestimmten geschwindichket aus
  void aus (int speed);


  // Schaltet sofort die RGB lampen auf einen bestimten wert
  void setRGB (uint16_t red, uint16_t green, uint16_t blue);

  // setzt die Warm Weiß sofort auf einen bestimmten wert
  void setWW (uint16_t value);

  // setzt die Kalt Weiß sofort auf einen bestimmten wert
  void setKW (uint16_t value);

  // setzt die Roten LEDs sofort auf einen bestimmten wert
  void setR (uint16_t value);

  // setzt die Blauen LEDs sofort auf einen bestimmten wert
  void setB (uint16_t value);


};

#endif // LICHT_H
