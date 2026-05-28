#include "midi.hpp"

/////////// midi commands
void sendMidi(byte cmd, byte a1, byte a2){
    Serial1.write(cmd);
    Serial1.write(a1);
    Serial1.write(a2);
}

void noteON(byte note){
    sendMidi(0x90, note, 127);
}

void noteOFF(byte note){
    sendMidi(0x80, note, 127);
}

void setVolume(byte volume){
    sendMidi(0XB0, 0x07, volume); // Control Change, CC 7 (Volume)
}

void setInstrument(byte instrument){
    sendMidi(0xC0, instrument, 0x00);
}