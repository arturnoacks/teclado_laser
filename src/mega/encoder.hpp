#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>
#include "midi.hpp"
#define ENCODER_CLK 2
#define ENCODER_DT 3
#define ENCODER_SW 4

#define ENCODER_MODES 3
typedef enum{
    VOLUME, INSTRUMENTO, OITAVA
}encoderMode;

void encoder_setup();

void handle_encoder_press();

void read_encoder();

int get_octave();
#endif