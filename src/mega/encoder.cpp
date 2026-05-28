#include "encoder.hpp"

//////////////////// instrument and octave
volatile int current_instrument = 0;
int lastInstrument = 0;
volatile int octaveOffset = 0;     // e.g., -2, -1, 0, +1, +2
int lastOctaveOffset = 0;

int lastClkState;
unsigned long last_encoder_press = 0;
unsigned long last_encoder_rotation = 0;
encoderMode modo = INSTRUMENTO;

byte volume = 63;
byte instrumento = 0;
int oitava = 0; //-3 a 4

void encoder_setup(){
    // Setup Encoder Pins with Internal Pull-ups
    pinMode(ENCODER_CLK, INPUT_PULLUP);
    pinMode(ENCODER_DT, INPUT_PULLUP);
    pinMode(ENCODER_SW, INPUT_PULLUP); // Enable pull-up for the switch

    lastClkState = digitalRead(ENCODER_CLK);
    attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), read_encoder, CHANGE);
}

void handle_encoder_press(){
    int btnState = digitalRead(ENCODER_SW);
  
    if (btnState == LOW && (millis() - last_encoder_press > 200)) {
        modo = (encoderMode)((modo+1)%ENCODER_MODES);

        last_encoder_press = millis();
        
        Serial.print("Ja muda, agora é ");
        Serial.println(modo);
    }

    // if (instrument_mode) {
    //     // INSTRUMENT MODE
    //     if (current_instrument != lastInstrument) {
    //         setInstrument(current_instrument);
    //         lastInstrument = current_instrument;
    //     }
    // }
}

void read_encoder(){
    
    if(millis() - last_encoder_rotation > 50){ // debouncer
       last_encoder_rotation = millis();

        int clkState = digitalRead(ENCODER_CLK);
    
        if (clkState != lastClkState) {
            lastClkState = clkState;
            bool clockwise = (digitalRead(ENCODER_DT) != clkState); //sentido
            
            switch (modo)
            {
                case VOLUME:
                    if(clockwise) volume = constrain((int)volume+16,0,127);
                    else volume = constrain((int)volume-16,0,127);
                    setVolume(volume);
                    Serial.print("Volume "); Serial.println(volume);
                    break;
                case INSTRUMENTO:
                    if(clockwise) instrumento = constrain((int)instrumento+1,0,127);
                    else instrumento = constrain((int)instrumento-1,0,127);
                    setInstrument(instrumento);
                    Serial.print("instrumento "); Serial.println(instrumento);
                    break;
                case OITAVA:
                    if(clockwise) oitava++;
                    else oitava--;
                    oitava = constrain(oitava, -3, 4);
                    Serial.print("oitava "); Serial.println(oitava);
                    break;
                // case VOLUME:
                // /* code */
                // break;
                default:
                    break;
            }
        }
    }
}

int get_octave(){
    return oitava;
}