//
// Created by Oliver on 18.10.2018.
//

#ifndef AQUARIUM_AUTOMATED_CONFIG_DUMMY_H
#define AQUARIUM_AUTOMATED_CONFIG_DUMMY_H

#include <stdint.h>
#include <stdio.h>

typedef uint8_t byte;

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
        fwrite(data,1,512,pFile);
        fclose(pFile);
    }
    void dummyInit(){
        FILE* pFile;
        pFile = fopen("file.binary", "rb");
        fread(data,1,512,pFile);
        fclose(pFile);
    }
    void dummyInitZero(){
        for (int i = 0; i < 512; ++i) {
           data[0] = 0;
        }
        write(0,0);
    }

};


//Definition Wie Der Fader Speicher aussieht
#define FADER_START 0
#define FADER_SIZE 6
#define FADER_VAL_SIZE 4

class ConfigDummy {
public:
    void dummyInit();
    void writeInt(int adr, int val);
    void writeByte(int adr, byte byt);
    int readInt(int adr);
    byte readByte(int adr);

    int getFader(int faderIndex, int valueIndex);
    void setFader(int faderIndex, int valueIndex, int value);



};


#endif //AQUARIUM_AUTOMATED_CONFIG_DUMMY_H
