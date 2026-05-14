#include <Arduino.h>

typedef struct _tMIDI
{
    byte cmd, data1, data2;
}tMIDI;


byte liga = 0x90;
byte data1 = 60;


void setup(){
    Serial.begin(9600);
    Serial1.begin(9600);

    randomSeed(analogRead(A5));
}


void loop(){
    delay(150);

    byte volume = 127;

    tMIDI midi = {liga, data1, volume};

    Serial1.write(liga);
    Serial1.write(data1);
    Serial1.write(volume);

    if(liga==0x90) liga = 0x80;
    else if (liga==0x80) {
        liga = 0x90;
        data1 += 1;
        if(data1>90) data1 = 30;
    }
}