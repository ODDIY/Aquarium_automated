//
// Created by Oliver on 18.10.2018.
//

#include "Config.h"




/*!
 * Initaliserit den EEPROM
 */
void Config::setup () {
        EEPROM.begin(512);
        /*
           for(int i = 0; i < 512/4; i++) {

                Serial.print(i);
                Serial.print("::");
                Serial.print(readInt(i*4));
                Serial.print("   ");
                if((i+1) % 8 == 0 ) {
                        Serial.println();
                }
                delay(5);

           }*/

}

/*!
 * Lesen eines Ints an gegebener Addresse im EEPROM
 * @param adr Adresse im EEPROM
 * @return der wert des Ints an dieser stelle
 */
int Config::readInt (int adr) {
        //Baut ein int aus 4 EEPROM bytes zusammen!!
        return (EEPROM.read(adr) << 24) | (EEPROM.read(adr + 1) << 16) | (EEPROM.read(adr + 2) << 8) |
               (EEPROM.read(adr + 3) << 0);
}


/*!
 * Schreiben eines Ints an der gegebnen Adresse in den EEPROM
 *
 * Ein wert Wird erst nach aufrufen von save in den Nicht flüchtigen teil des EEPROM übernommen
 *
 * @param adr Addrese im EEPROM
 * @param val Wert der gespeichert werden soll
 */
void Config::writeInt (int adr, int val) {
        EEPROM.write(adr, (val >> 24) & 0xFF);
        EEPROM.write(adr + 1, (val >> 16) & 0xFF);
        EEPROM.write(adr + 2, (val >> 8) & 0xFF);
        EEPROM.write(adr + 3, (val >> 0) & 0xFF);
}


/*!
 * Lesen eines FaderWerts aus dem EEPROM
 *
 * werte Index:
 * 0 = start FADE-IN Zeit;
 * 1 = ende FADE-IN Zeit;
 * 2 = FADE-IN end Wert;
 * 3 = start FADE-OFF Zeit;
 * 4 = ende FADE-OFF Zeit;
 * 5 = FADE-OFF end Wert
 *
 * @param faderIndex index nummer des Faders
 * @param valueIndex  wert index der gewünschten wertes
 * @return Gewünschter wert des Faders
 */
int Config::getFader (int faderIndex, int valueIndex) {
        return readInt(FADER_START + (faderIndex * FADER_SIZE * FADER_VAL_SIZE) + valueIndex * FADER_VAL_SIZE);
}

/*!
 * Schreiben eines FaderWerts in den EEPROM
 *
 * werte Index:
 * 0 = start FADE-IN Zeit;
 * 1 = ende FADE-IN Zeit;
 * 2 = FADE-IN end Wert;
 * 3 = start FADE-OFF Zeit;
 * 4 = ende FADE-OFF Zeit;
 * 5 = FADE-OFF end Wert
 *
 * @param faderIndex  index nummer des Faders
 * @param valueIndex wert index der an den geschrieben werden soll
 * @param value Wert der Gespeichert werden soll
 */
void Config::setFader (int faderIndex, int valueIndex, int value) {
        writeInt(FADER_START + (faderIndex * FADER_SIZE * FADER_VAL_SIZE) + (valueIndex * FADER_VAL_SIZE), value);
}

/*!
 * Speichert die Konfiguration für einen kompletten fade OHNE FADE-OFF
 *
 * @param faderIndex index nummer des Faders
 * @param start start FADE-IN Zeit
 * @param end ende FADE-IN Zeit
 * @param val FADE-IN end Wert
 */
void Config::setFader_fadein (int faderIndex, int start, int end, int val) {
        setFader(faderIndex, 0, start);
        setFader(faderIndex, 1, end);
        setFader(faderIndex, 2, val);
        setFader(faderIndex, 3, -1);
        setFader(faderIndex, 4, -1);
        setFader(faderIndex, 5, val);
}

/*!
 * Speichert die Konfiguration für einen kompletten fade MIT FADE-OFF
 *
 * @param faderIndex index nummer des Faders
 * @param start start FADE-IN Zeit
 * @param end ende FADE-IN Zeit
 * @param val  FADE-IN end Wert
 * @param offstart  start FADE-OFF Zeit
 * @param offEnd ende FADE-OFF Zeit
 * @param offval  FADE-OFF end Wert
 */
void Config::setFader_fadeinout (int faderIndex, int start, int end, int val, int offstart, int offEnd, int offval) {
        setFader(faderIndex, 0, start);
        setFader(faderIndex, 1, end);
        setFader(faderIndex, 2, val);
        setFader(faderIndex, 3, offstart);
        setFader(faderIndex, 4, offEnd);
        setFader(faderIndex, 5, offval);
}

void Config::setTimer (int timerIndex, int secondOfTheDay) {
        writeInt( TIME_START + (timerIndex*TIME_SIZE), secondOfTheDay);
}

int Config::getTimer (int timerIndex) {
        return readInt(TIME_START + (timerIndex*TIME_SIZE));
}

/*!
 * Speichert den EEPROM in nicht flüchtigen Speicher
 */
void Config::save () {
        EEPROM.commit();
}

/*!
 * Schreibt Standart werte in den EEPROM
 */
void Config::initSettings () {
        setFader_fadeinout(FAD_R_rise, 0, 24000, 4095, 45000, 66000, 1024);
        setFader_fadeinout(FAD_B_rise, 6000, 34500, 4095, 45000, 66000, 1024);
        delay(5);
        setFader_fadeinout(FAD_R_set, 0, 24000, 4095, 45000, 66000, 1024);
        setFader_fadeinout(FAD_B_set, 6000, 34500, 1024, 45000, 66000, 1024);
        delay(5);
        setFader_fadein(FAD_WW_rise, 12000, 36000, 4095);
        setFader_fadein(FAD_KW_rise, 30000, 60000, 4095);
        delay(5);
        setFader_fadein(FAD_WW_set, 0, 36000, 4095);
        setFader_fadein(FAD_KW_set, 30000, 60000, 4095);
        delay(5);
        setFader_fadeinout(FAD_RGB_R_rise, 0, 24000, 4095, 45000, 66000, 1024);
        setFader_fadeinout(FAD_RGB_G_rise, 24000, 42000, 4095, 45000, 66000, 1024);
        setFader_fadeinout(FAD_RGB_B_rise, 6000, 34500, 4095, 45000, 66000, 1024);
        delay(5);
        setFader_fadeinout(FAD_RGB_R_set, 0, 24000, 4095, 45000, 66000, 1024);
        setFader_fadeinout(FAD_RGB_G_set, 24000, 42000, 1024, 45000, 66000, 1024);
        setFader_fadeinout(FAD_RGB_B_set, 6000, 34500, 1024, 45000, 66000, 1024);
        delay(5);
        setTimer(T_RISE1, TIME_TO_SEC(7,0,0));
        setTimer(T_FALL1, TIME_TO_SEC(9,0,0));
        setTimer(T_RISE2, TIME_TO_SEC(13,0,0));
        setTimer(T_FALL2, TIME_TO_SEC(21,0,0));
        delay(5);
        save();
}
