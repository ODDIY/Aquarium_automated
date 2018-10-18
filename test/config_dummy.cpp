//
// Created by Oliver on 18.10.2018.
//
#include "config_dummy.h"

EepromDummy EEPROM;


int ConfigDummy::readInt(int adr) {
    //Baut ein int aus 4 eeprom bytes zusammen!!
    return (EEPROM.read(adr) << 24) | (EEPROM.read(adr +1) << 16) | (EEPROM.read(adr +2) << 8) | (EEPROM.read(adr +3) << 0);
}
byte ConfigDummy::readByte(int adr) {
    return EEPROM.read(adr);
}

void ConfigDummy::writeInt(int adr, int val) {
    EEPROM.write(adr,(val>>24) & 0xFF);
    EEPROM.write(adr+1,(val>>16) & 0xFF);
    EEPROM.write(adr+2,(val>>8)  & 0xFF);
    EEPROM.write(adr+3,(val>>0)  & 0xFF);
}

void ConfigDummy::writeByte(int adr, byte byt) {
    EEPROM.write(adr,byt);
}

void ConfigDummy::dummyInit() {
EEPROM.dummyInit();
}

int ConfigDummy::getFader(int faderIndex, int valueIndex) {
    return readInt(FADER_START+ (faderIndex*FADER_SIZE*FADER_VAL_SIZE) + valueIndex*FADER_VAL_SIZE );
}

void ConfigDummy::setFader(int faderIndex, int valueIndex, int value) {
    writeInt(FADER_START+ (faderIndex*FADER_SIZE*FADER_VAL_SIZE) + (valueIndex*FADER_VAL_SIZE), value);
}
