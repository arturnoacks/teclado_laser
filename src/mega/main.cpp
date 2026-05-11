#include <Arduino.h>

typedef struct _tMIDI
{
    byte cmd, data1, data2;
}tMIDI;



void setup(){
    Serial.begin(9600);
    Serial1.begin(9600);
}


void loop(){
    delay(1000);
    Serial1.write("tchaur\n");
}