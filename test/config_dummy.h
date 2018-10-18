//
// Created by Oliver on 18.10.2018.
//

#ifndef AQUARIUM_AUTOMATED_CONFIG_DUMMY_H
#define AQUARIUM_AUTOMATED_CONFIG_DUMMY_H

#include <stdint.h>
#include <stdio.h>

typedef uint8_t byte;


/**
 * EEPROM Dummy
 * Simuliert den EEPORM des ESP8266
 * Zum testen Unter POSIX winows
 */
class EepromDummy {

public:
    uint8_t data[512];

    uint8_t read(int address) {
        return data[address];
    }

    void write(int addr, byte val) {
        data[addr] = val;

        FILE* pFile;
        pFile = fopen("file.binary", "wb");
        fwrite(data, 1, 512, pFile);
        fclose(pFile);
    }

    void dummyInit(){
        FILE* pFile;
        pFile = fopen("file.binary", "rb");
        fread(data, 1, 512, pFile);
        fclose(pFile);
    }

    void dummyInitZero(){
        for (int i = 0; i < 512; ++i) {
            data[0] = 0;
        }
        write(0, 0);
    }

};


//Definition Wie Der Fader Speicher aussieht
#define FADER_START 0
#define FADER_SIZE 6
#define FADER_VAL_SIZE 4

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

class ConfigDummy {
public:
    void setup();
    void dummyInit();
    void writeInt(int adr, int val);
    void writeByte(int adr, byte byt);
    int readInt(int adr);
    byte readByte(int adr);

    int getFader(int faderIndex, int valueIndex);

    void setFader(int faderIndex, int valueIndex, int value);

    int setFader_fadein(int faderIndex, int start, int end, int val);

    int setFader_fadeinout(int faderIndex, int start, int end, int val, int offstart, int offEnd, int offval);




};


#endif //AQUARIUM_AUTOMATED_CONFIG_DUMMY_H
