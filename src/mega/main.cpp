#include <Arduino.h>
#include "encoder.hpp"

#define NUM_NOTES 24
#define FIRST_PIN_NOTES 22
#define LAST_PIN_NOTES 45
#define ON 0
#define OFF 1

//////////////// notes
byte note_status[24];
byte pin_to_note(uint8_t pin){
    return constrain(int(pin + 26 + (get_octave() * 12)), 0, 127);
}


void setup(){
    Serial.begin(9600);
    Serial1.begin(9600);
    Serial2.begin(115200);
    
    for(int i=0; i<NUM_NOTES; i++){
        note_status[i] = digitalRead(FIRST_PIN_NOTES + i);
    }
    
    encoder_setup();
}


void loop(){
    
    handle_encoder_press();

    receive_from_esp();
    
    for(int i=0; i<NUM_NOTES; i++){
        uint8_t pin = FIRST_PIN_NOTES + i;
        byte note = pin_to_note(pin);

        int stateAtual = digitalRead(pin);
        if(stateAtual != note_status[i]){
            note_status[i] = 1 - note_status[i];

            String jsonNota = "{\"n\":";
            jsonNota += note;
            jsonNota += ",\"s\":";
            
            if(note_status[i] == ON){
                noteON(note);
                jsonNota += "1}";
                Serial.print("Note ");Serial.print(note);Serial.println(" ON");
            }
            else{
                noteOFF(note);
                jsonNota += "0}";
                Serial.print("Note ");Serial.print(note);Serial.println(" OFF");
            }

            Serial2.println(jsonNota);
        }
    }
    
    delay(10); // Small stability delay
}