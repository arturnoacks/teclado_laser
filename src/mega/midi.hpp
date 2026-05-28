#ifndef MIDI_H
#define MIDI_H

#include <Arduino.h>

void sendMidi(byte cmd, byte a1, byte a2);

void noteON(byte note);

void noteOFF(byte note);

void setVolume(byte volume);

void setInstrument(byte instrument);
#endif