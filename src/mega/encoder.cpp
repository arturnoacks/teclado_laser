#include "encoder.hpp"
#include <ArduinoJson.h>

//////////////////// instrument and octave
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
}

void send_to_esp(){
    String json = "{\"v\":";
    json += volume;
    json += ",\"i\":";
    json += instrumento;
    json += ",\"o\":";
    json += oitava;
    json += "}";
    
    Serial2.println(json);
    Serial.println("Enviado: " + json);
}

void receive_from_esp() {
    if (Serial2.available()) {
        String input = Serial2.readStringUntil('\n');

        StaticJsonDocument<200> doc; 
        
        DeserializationError error = deserializeJson(doc, input);

        if (!error) {
            if (doc.containsKey("v")) {
                volume = doc["v"];
                setVolume(volume);
            }
            if (doc.containsKey("i")) {
                instrumento = doc["i"];
                setInstrument(instrumento);
            }
            if (doc.containsKey("o")) {
                oitava = doc["o"];
            }
        } else {
            Serial.print("Erro ao ler JSON da ESP: ");
            Serial.println(error.c_str());
        }
    }
}

void read_encoder(){
    
    if(millis() - last_encoder_rotation > 50){ // debouncer
       last_encoder_rotation = millis();

        int clkState = digitalRead(ENCODER_CLK);
    
        if (clkState != lastClkState) {
            lastClkState = clkState;
            bool clockwise = (digitalRead(ENCODER_DT) != clkState); //sentido

            bool alterado = false;
            
            switch (modo)
            {
                case VOLUME:
                    if(clockwise) volume = constrain((int)volume+16,0,127);
                    else volume = constrain((int)volume-16,0,127);
                    setVolume(volume);
                    alterado = true;
                    Serial.print("Volume "); Serial.println(volume);
                    break;
                case INSTRUMENTO:
                    if(clockwise) instrumento = constrain((int)instrumento+1,0,127);
                    else instrumento = constrain((int)instrumento-1,0,127);
                    setInstrument(instrumento);
                    alterado = true;
                    Serial.print("instrumento "); Serial.println(instrumento);
                    break;
                case OITAVA:
                    if(clockwise) oitava++;
                    else oitava--;
                    oitava = constrain(oitava, -3, 4);
                    alterado = true;
                    Serial.print("oitava "); Serial.println(oitava);
                    break;
                // case VOLUME:
                // /* code */
                // break;
                default:
                    break;
            }

            if (alterado) {
                send_to_esp();
            }
        }
    }
}

int get_octave(){
    return oitava;
}