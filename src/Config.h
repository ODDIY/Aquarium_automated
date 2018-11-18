//
// Created by Oliver on 18.10.2018.
//

#ifndef AQUARIUM_AUTOMATED_CONFIG_H
#define AQUARIUM_AUTOMATED_CONFIG_H

#include <Arduino.h>
#include <EEPROM.h>

//Definition Wie Der Fader Speicher aussieht
#define FADER_START 0
#define FADER_SIZE 6
#define FADER_VAL_SIZE sizeof(int)

//Index nummern der Fader im Speicher
#define FAD_R_rise 0
#define FAD_B_rise 1
#define FAD_WW_rise 2
#define FAD_KW_rise 3
#define FAD_RGB_R_rise 4
#define FAD_RGB_G_rise 5
#define FAD_RGB_B_rise 6

#define FAD_R_set 7
#define FAD_B_set 8
#define FAD_WW_set 9
#define FAD_KW_set 10
#define FAD_RGB_R_set 11
#define FAD_RGB_G_set 12
#define FAD_RGB_B_set 13

//Timer Werte im Speicher
#define TIME_START FADER_START+(14*FADER_SIZE*FADER_VAL_SIZE)
#define TIME_SIZE sizeof(int)

//Index nummern der Timer im Speicher
#define T_RISE1 0
#define T_FALL1 1
#define T_RISE2 2
#define T_FALL2 3

#define TIME_TO_SEC(h,m,s) ((((h*60)+m)*60)+s)

/*!
 * class Config
 *
 * Erleichtert das laden und speichen in den EEPROM
 */
class Config {
    //Schreibt ein Einzelnes int in den EEPROM
    void writeInt(int adr, int val);

    //void writeByte(int adr, byte byt);
    int readInt(int adr);
    //byte readByte(int adr);

public:

    // Bereitet den EEPROM vor
    void setup();

    // Läd Standart Werte in den EEPROM
    void initSettings();

    // Speichert die Konfiguration in den EEPROM
    void save();

    //hole EINEN wert eines Faders
    int getFader(int faderIndex, int valueIndex);

    //setze EINEN wert eines Faders
    void setFader(int faderIndex, int valueIndex, int value);

    //setze ALLE Werte eines Faders ohne ausfaden
    void setFader_fadein(int faderIndex, int start, int end, int val);

    //setze ALLE Werte eines Faders mit ausfaden
    void setFader_fadeinout(int faderIndex, int start, int end, int val, int offstart, int offEnd, int offval);

    //
    void setTimer(int timerIndex, int secondOfTheDay);

    //
    int getTimer(int timerIndex);

};


#endif //AQUARIUM_AUTOMATED_CONFIG_H
