#include "Licht.h"

// Constructors/Destructors
//  

Licht::Licht (PCA9685 *pwm, Config * config) {
    this->pwm = pwm;
    this->config = config;
}

/**
  * setup beim starten
  */
void Licht::setup () {
    lasttime = 0;
    starttime = 0;
    sunrise = false;
    sunset = false;
    speed = 0;

    readFaderValues();
}


void Licht::readFaderValues() {
    rF.set(    config->getFader(0,0), config->getFader(0,1), config->getFader(0,2),config->getFader(0,3),config->getFader(0,4),config->getFader(0,5));
    bF.set(    config->getFader(1,0), config->getFader(1,1), config->getFader(1,2),config->getFader(1,3),config->getFader(1,4),config->getFader(1,5));
    wwF.set(   config->getFader(2,0), config->getFader(2,1), config->getFader(2,2),config->getFader(2,3),config->getFader(2,4),config->getFader(2,5));
    kwF.set(   config->getFader(3,0), config->getFader(3,1), config->getFader(3,2),config->getFader(3,3),config->getFader(3,4),config->getFader(3,5));
    rgb_rF.set(config->getFader(4,0), config->getFader(4,1), config->getFader(4,2),config->getFader(4,3),config->getFader(4,4),config->getFader(4,5));
    rgb_gF.set(config->getFader(5,0), config->getFader(5,1), config->getFader(5,2),config->getFader(5,3),config->getFader(5,4),config->getFader(5,5));
    rgb_bF.set(config->getFader(6, 0), config->getFader(6, 1), config->getFader(6, 2), config->getFader(6, 3),
               config->getFader(6, 4), config->getFader(6, 5));
}


/**
 * Fadet das licht nach bedarf an und aus
Und steuert die C02 zufur
 @param milis Arduino Zeit in milliseconds  !!
 */
void Licht::update (unsigned long milis) {
    if (start) {
        start = false;
        starttime = milis;
    }

    //nur einmal pro millikesunde ausführen
    if (milis > lasttime) {
        lasttime = milis;

        unsigned long deltaTime = lasttime - starttime;

        int time = 0;

        if (sunrise) {
            time = static_cast<int> (deltaTime * speed);
            if (time > FADE_TIME_MAX) {
                sunrise = false;
            }

        } else if (sunset) {
            time = static_cast<int>(FADE_TIME_MAX - (deltaTime * speed));
            if (time < 0) {
                sunset = false;
            }
        }

        if (sunrise || sunset) {
            runFaders(time);

        }
    }
}

/**
 * gibt das signal das licht mit einer bestimmten geschwindichkeit zu starten
 * @param  speed
 */
void Licht::an (int speed) {
    this->speed = speed;
    sunrise = true;
    start = true;
    readFaderValues();
}


/**
 * Schaltet das licht mit einer bestimmten geschwindichket aus
 * @param  speed
 */
void Licht::aus (int speed) {
    this->speed = speed;
    sunset = true;
    start = true;
    readFaderValues();
}


/**
 * Schaltet sofort die RGB lampen auf einen bestimten wert
 * @param  red
 * @param  green
 * @param  blue
 */
void Licht::setRGB (uint16_t red, uint16_t green, uint16_t blue) {
    pwm->pwmWrite(PWM_PIN_RGB_R,red);
    pwm->pwmWrite(PWM_PIN_RGB_G,green);
    pwm->pwmWrite(PWM_PIN_RGB_B, blue);
}


/**
 * setzt die Warm Wei� sofort auf einen bestimmten wert
 * @param  value
 */
void Licht::setWW (uint16_t value) {
    pwm->pwmWrite(PWM_PIN_WW,value);
}


/**
 * setzt die Kalt Wei� sofort auf einen bestimmten wert
 * @param  value
 */
void Licht::setKW (uint16_t value) {
    pwm->pwmWrite(PWM_PIN_KW,value);
}


/**
 * setzt die Roten LEDs sofort auf einen bestimmten wert
 * @param  value
 */
void Licht::setR (uint16_t value){
    pwm->pwmWrite(PWM_PIN_R,value);
}


/**
 * setzt die Blauen LEDs sofort auf einen bestimmten wert
 * @param  value
 */
void Licht::setB (uint16_t value) {
    pwm->pwmWrite(PWM_PIN_B,value);
}

/*!
 * Setze alle PWM Werte für alle fader zur einer bestimmten zeit;
 * @param time Zeit in der Fade Kurve
 */
void Licht::runFaders(int time) {
    setR(static_cast<uint16_t >(rF.fade(time)));
    setB(static_cast<uint16_t >(bF.fade(time)));
    setWW(static_cast<uint16_t >(wwF.fade(time)));
    setKW(static_cast<uint16_t >(kwF.fade(time)));

    auto red = static_cast<uint16_t >(rgb_rF.fade(time));
    auto green = static_cast<uint16_t >(rgb_gF.fade(time));
    auto blue = static_cast<uint16_t >(rgb_bF.fade(time));

    setRGB(red, green, blue);
}


