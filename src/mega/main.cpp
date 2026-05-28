#include <Arduino.h>
#include "encoder.hpp"

#define NUM_NOTES 24
#define FIRST_PIN_NOTES 22
#define LAST_PIN_NOTES 45
#define ON 0
#define OFF 1
//#define POT_VOL_PIN A0

//////////////// notes
byte note_status[24];
byte pin_to_note(uint8_t pin){
    return constrain(int(pin + 26 + (get_octave() * 12)), 0, 127);
}


/////////////////////volume
// const int volume_potenciometer_threshold = 2;
// int lastVolume = -1;

// void handle_volume(){
//     int rawPot = analogRead(POT_VOL_PIN);
//     int currentVolume = map(rawPot, 0, 1023, 0, 127); // Map to MIDI range (0-127)

//     // Only send if the volume changed significantly to avoid jitter
//     if (abs(currentVolume - lastVolume) > volume_potenciometer_threshold) {
//         Serial.print("Volume ");
//         Serial.println(currentVolume);
//         setVolume(currentVolume); 
//         lastVolume = currentVolume;
//     }
// }

////////////////////// util

void setup(){
    Serial.begin(9600);
    Serial1.begin(9600);

    for(int i=0; i<NUM_NOTES; i++){
        note_status[i] = digitalRead(FIRST_PIN_NOTES + i);
    }

    encoder_setup();
}


void loop(){
    
    handle_encoder_press();

    for(int i=0; i<NUM_NOTES; i++){
        uint8_t pin = FIRST_PIN_NOTES + i;
        byte note = pin_to_note(pin);

        int stateAtual = digitalRead(pin);
        if(stateAtual != note_status[i]){
            note_status[i] = 1 - note_status[i];

            if(note_status[i] == ON){
                noteON(note);
                Serial.print("Note ");Serial.print(note);Serial.println(" ON");
            }
            else{
                noteOFF(note);
                Serial.print("Note ");Serial.print(note);Serial.println(" OFF");
            }
        }
    }

    delay(10); // Small stability delay
}

// Interrupt Service Routine (ISR)
// void readEncoder() {
//   int clkState = digitalRead(ENCODER_CLK);
  
//   if (clkState != lastClkState) {
//     bool clockwise = (digitalRead(ENCODER_DT) != clkState);
    
//     if (instrument_mode) {
//       // Adjust Instrument
//       if (clockwise) current_instrument++; else current_instrument--;
//       current_instrument = constrain(current_instrument, 0, 127);
//         Serial.println("Mudou instrumento");

//     } else {
//       // Adjust Octave (-4 to +4 is a standard safe range)
//       if (clockwise) octaveOffset++; else octaveOffset--;
//       octaveOffset = constrain(octaveOffset, -4, 4);
//         Serial.println("Mudou oitava");
    
//     }
//   }
//   lastClkState = clkState;
// }