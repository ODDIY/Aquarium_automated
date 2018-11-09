#include "Licht.h"

// Constructors/Destructors
//
/*!
 * Erzeugt das Licht Module
 * @param pwm PWM ausgabe Module
 * @param config Configurations Speicher module
 */
Licht::Licht (PCA9685 *pwm, Config * config) {
    this->pwm = pwm;
    this->config = config;
}

/**
  * setup beim starten
  * initaliert alle variabeln
  * und holt zum ersten mal die werte aus der Configuration
  */
void Licht::setup () {
    lasttime = 0;
    starttime = 0;
    sunrise = false;
    sunset = false;
    speed = 0;
    ww = 0;
    kw = 0;
    co2 = false;
    readFaderValues();
}


/*!
 * Liest die Fader-Konfiguration aus dem Config-Speicher
 */
void Licht::readFaderValues() {

    rF_rise.set(config->getFader(FAD_R_rise, 0), config->getFader(FAD_R_rise, 1), config->getFader(FAD_R_rise, 2),
                config->getFader(FAD_R_rise, 3), config->getFader(FAD_R_rise, 4), config->getFader(FAD_R_rise, 5));

    bF_rise.set(config->getFader(FAD_B_rise, 0), config->getFader(FAD_B_rise, 1), config->getFader(FAD_B_rise, 2),
                config->getFader(FAD_B_rise, 3), config->getFader(FAD_B_rise, 4), config->getFader(FAD_B_rise, 5));

    rF_set.set(config->getFader(FAD_R_set, 0), config->getFader(FAD_R_set, 1), config->getFader(FAD_R_set, 2),
               config->getFader(FAD_R_set, 3), config->getFader(FAD_R_set, 4), config->getFader(FAD_R_set, 5));

    bF_set.set(config->getFader(FAD_B_set, 0), config->getFader(FAD_B_set, 1), config->getFader(FAD_B_set, 2),
               config->getFader(FAD_B_set, 3), config->getFader(FAD_B_set, 4), config->getFader(FAD_B_set, 5));

    wwF_rise.set(config->getFader(FAD_WW_rise, 0), config->getFader(FAD_WW_rise, 1), config->getFader(FAD_WW_rise, 2),
                 config->getFader(FAD_WW_rise, 3), config->getFader(FAD_WW_rise, 4), config->getFader(FAD_WW_rise, 5));

    kwF_rise.set(config->getFader(FAD_KW_rise, 0), config->getFader(FAD_KW_rise, 1), config->getFader(FAD_KW_rise, 2),
                 config->getFader(FAD_KW_rise, 3), config->getFader(FAD_KW_rise, 4), config->getFader(FAD_KW_rise, 5));

    wwF_set.set(config->getFader(FAD_WW_set, 0), config->getFader(FAD_WW_set, 1), config->getFader(FAD_WW_set, 2),
                config->getFader(FAD_WW_set, 3), config->getFader(FAD_WW_set, 4), config->getFader(FAD_WW_set, 5));

    kwF_set.set(config->getFader(FAD_KW_set, 0), config->getFader(FAD_KW_set, 1), config->getFader(FAD_KW_set, 2),
                config->getFader(FAD_KW_set, 3), config->getFader(FAD_KW_set, 4), config->getFader(FAD_KW_set, 5));

    rgb_rF_rise.set(config->getFader(FAD_RGB_R_rise, 0), config->getFader(FAD_RGB_R_rise, 1),
                    config->getFader(FAD_RGB_R_rise, 2),
                    config->getFader(FAD_RGB_R_rise, 3), config->getFader(FAD_RGB_R_rise, 4),
                    config->getFader(FAD_RGB_R_rise, 5));

    rgb_gF_rise.set(config->getFader(FAD_RGB_G_rise, 0), config->getFader(FAD_RGB_G_rise, 1),
                    config->getFader(FAD_RGB_G_rise, 2),
                    config->getFader(FAD_RGB_G_rise, 3), config->getFader(FAD_RGB_G_rise, 4),
                    config->getFader(FAD_RGB_G_rise, 5));

    rgb_bF_rise.set(config->getFader(FAD_RGB_B_rise, 0), config->getFader(FAD_RGB_B_rise, 1),
                    config->getFader(FAD_RGB_B_rise, 2),
                    config->getFader(FAD_RGB_B_rise, 3), config->getFader(FAD_RGB_B_rise, 4),
                    config->getFader(FAD_RGB_B_rise, 5));

    rgb_rF_set.set(config->getFader(FAD_RGB_R_set, 0), config->getFader(FAD_RGB_R_set, 1),
                   config->getFader(FAD_RGB_R_set, 2),
                   config->getFader(FAD_RGB_R_set, 3), config->getFader(FAD_RGB_R_set, 4),
                   config->getFader(FAD_RGB_R_set, 5));

    rgb_gF_set.set(config->getFader(FAD_RGB_G_set, 0), config->getFader(FAD_RGB_G_set, 1),
                   config->getFader(FAD_RGB_G_set, 2),
                   config->getFader(FAD_RGB_G_set, 3), config->getFader(FAD_RGB_G_set, 4),
                   config->getFader(FAD_RGB_G_set, 5));

    rgb_bF_set.set(config->getFader(FAD_RGB_B_set, 0), config->getFader(FAD_RGB_B_set, 1),
                   config->getFader(FAD_RGB_B_set, 2),
                   config->getFader(FAD_RGB_B_set, 3), config->getFader(FAD_RGB_B_set, 4),
                   config->getFader(FAD_RGB_B_set, 5));

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

    //nur einmal pro 10 millikesunde ausführen
    if (milis > lasttime + 10) {
        lasttime = milis;

        unsigned long deltaTime = (lasttime - starttime) / 10;

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

            //CO2 Bedingung
            if (kw + ww > 8000) {
                setCO2(true);
            } else {
                setCO2(false);
            }
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
    red = min(red, 4095);
    green = min(green, 4095);
    blue = min(blue, 4095);

    pwm->pwmWrite(PWM_PIN_RGB_R,red);
    pwm->pwmWrite(PWM_PIN_RGB_G,green);
    pwm->pwmWrite(PWM_PIN_RGB_B, blue);
}


void Licht::setRGB_W(uint16_t white) {
  white = min(white, 4095);
  pwm->pwmWrite(PWM_PIN_RGB_W,white);

}


/**
 * setzt die Warm Wei� sofort auf einen bestimmten wert
 * Checkt
 * @param  value
 */
void Licht::setWW (uint16_t value) {
    value = min(value, 4095);
    ww = value;
    pwm->pwmWrite(PWM_PIN_WW,value);

    //CO2 Bedingung
    if (kw + ww > 8000) {
        setCO2(true);
    } else {
        setCO2(false);
    }
}


/**
 * setzt die Kalt Wei� sofort auf einen bestimmten wert
 * @param  value
 */
void Licht::setKW (uint16_t value) {
    value = min(value, 4095);
    kw = value;
    pwm->pwmWrite(PWM_PIN_KW,value);

    //CO2 Bedingung
    if (kw + ww > 8000) {
        setCO2(true);
    } else {
        setCO2(false);
    }

}


/**
 * setzt die Roten LEDs sofort auf einen bestimmten wert
 * @param  value
 */
void Licht::setR (uint16_t value){
  value = min(value, 4095);

    pwm->pwmWrite(PWM_PIN_R,value);
}


/**
 * setzt die Blauen LEDs sofort auf einen bestimmten wert
 * @param  value
 */
void Licht::setB (uint16_t value) {
  value = min(value, 4095);

    pwm->pwmWrite(PWM_PIN_B,value);
}

/*!
 * Schaltet den CO2 ausgang an oder aus
 * @param on   co2 (true-an / false-aus);
 */
void Licht::setCO2(bool on) {
    if (on) {
        pwm->pwmWrite(PWM_PIN_CO2, 4095);
        co2 = true;
    } else {
        pwm->pwmWrite(PWM_PIN_CO2, 0);
        co2 = false;
    }
}

/*!
 * Gibt den C02 Status zurück
 * @return  co2 Status (true / false);
 */
bool Licht::getC02() {
    return co2;
}

/*!
 * Setze alle PWM Werte für alle fader zur einer bestimmten zeit;
 * @param time Zeit in der Fade Kurve
 */
void Licht::runFaders(int time) {

    if (sunrise) {
        setR(static_cast<uint16_t >(rF_rise.fade(time)));
        setB(static_cast<uint16_t >(bF_rise.fade(time)));

        ww = wwF_rise.fade(time);
        setWW(static_cast<uint16_t >(ww));

        kw = kwF_rise.fade(time);
        setKW(static_cast<uint16_t >(kw));

        auto red = static_cast<uint16_t >(rgb_rF_rise.fade(time));
        auto green = static_cast<uint16_t >(rgb_gF_rise.fade(time));
        auto blue = static_cast<uint16_t >(rgb_bF_rise.fade(time));

        setRGB(red, green, blue);

    }

    if (sunset) {
        setR(static_cast<uint16_t >(rF_set.fade(time)));
        setB(static_cast<uint16_t >(bF_set.fade(time)));

        ww = wwF_set.fade(time);
        setWW(static_cast<uint16_t >(ww));

        kw = kwF_set.fade(time);
        setKW(static_cast<uint16_t >(kw));

        auto red = static_cast<uint16_t >(rgb_rF_set.fade(time));
        auto green = static_cast<uint16_t >(rgb_gF_set.fade(time));
        auto blue = static_cast<uint16_t >(rgb_bF_set.fade(time));

        setRGB(red, green, blue);
    }


}
