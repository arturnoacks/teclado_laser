#include <Arduino.h>

#define NUM_NOTES 24
#define FIRST_PIN_NOTES 22
#define LAST_PIN_NOTES 45
#define ON 0
#define OFF 1
#define POT_VOL_PIN A0
#define ENCODER_CLK 2
#define ENCODER_DT 3
#define ENCODER_SW 4
void readEncoder();

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
//////////////////// instrument and octave
bool instrument_mode = true;
volatile int current_instrument = 0;
int lastInstrument = 0;
volatile int octaveOffset = 0;     // e.g., -2, -1, 0, +1, +2
int lastOctaveOffset = 0;
int lastClkState;
unsigned long last_encoder_press = 0;

//////////////// notes
byte note_status[24];
byte pin_to_note(uint8_t pin){
    return constrain(pin + 26 + (octaveOffset * 12), 0, 127);
}


/////////////////////volume
const int volume_potenciometer_threshold = 2;
int lastVolume = -1;

void handle_volume(){
    int rawPot = analogRead(POT_VOL_PIN);
    int currentVolume = map(rawPot, 0, 1023, 0, 127); // Map to MIDI range (0-127)

    // Only send if the volume changed significantly to avoid jitter
    if (abs(currentVolume - lastVolume) > volume_potenciometer_threshold) {
        Serial.print("Volume ");
        Serial.println(currentVolume);
        setVolume(currentVolume); 
        lastVolume = currentVolume;
    }
}

////////////////////// util

void setup(){
    Serial.begin(9600);
    Serial1.begin(9600);

    for(int i=0; i<NUM_NOTES; i++){
        note_status[i] = digitalRead(FIRST_PIN_NOTES + i);
    }

    // Setup Encoder Pins with Internal Pull-ups
    pinMode(ENCODER_CLK, INPUT_PULLUP);
    pinMode(ENCODER_DT, INPUT_PULLUP);
    pinMode(ENCODER_SW, INPUT_PULLUP); // Enable pull-up for the switch

    lastClkState = digitalRead(ENCODER_CLK);
    attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), readEncoder, CHANGE);
}


void loop(){
    handle_volume();
   
    int btnState = digitalRead(ENCODER_SW);
  
    if (btnState == LOW && (millis() - last_encoder_press > 200)) {
        instrument_mode = !instrument_mode; // Toggle between modes
        last_encoder_press = millis();
        
        Serial.println("Ja muda");
    }

    if (instrument_mode) {
        // INSTRUMENT MODE
        if (current_instrument != lastInstrument) {
            setInstrument(current_instrument);
            lastInstrument = current_instrument;
        }
    }
    
    for(int i=0; i<NUM_NOTES; i++){
        uint8_t pin = FIRST_PIN_NOTES + i;
        byte note = pin_to_note(pin);

        int stateAtual = digitalRead(pin);
        if(stateAtual != note_status[i]){
            note_status[i] = 1 - note_status[i];

            if(note_status[i] == ON){
                noteON(note);
                Serial.print("Note ");
                Serial.print(note);
                Serial.println(" ON");
            }
            else{
                noteOFF(note);
                Serial.print("Note ");
                Serial.print(note);
                Serial.println(" OFF");
            }
        }
    }

    delay(10); // Small stability delay
}

// Interrupt Service Routine (ISR)
void readEncoder() {
  int clkState = digitalRead(ENCODER_CLK);
  
  if (clkState != lastClkState) {
    bool clockwise = (digitalRead(ENCODER_DT) != clkState);
    
    if (instrument_mode) {
      // Adjust Instrument
      if (clockwise) current_instrument++; else current_instrument--;
      current_instrument = constrain(current_instrument, 0, 127);
        Serial.println("Mudou instrumento");

    } else {
      // Adjust Octave (-4 to +4 is a standard safe range)
      if (clockwise) octaveOffset++; else octaveOffset--;
      octaveOffset = constrain(octaveOffset, -4, 4);
        Serial.println("Mudou oitava");
    
    }
  }
  lastClkState = clkState;
}