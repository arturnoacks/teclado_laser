#include <WiFi.h>
#include <WebSocketsServer.h>

#define RXD2 16
#define TXD2 17

// Configurações de rede
const char* ssid = "";
const char* password = "";

// Inicia o servidor WebSocket na porta 81
WebSocketsServer webSocket = WebSocketsServer(81);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Cliente desconectado!\n", num);
            break;
        case WStype_CONNECTED:
            Serial.printf("[%u] Cliente conectado!\n", num);
            break;
        case WStype_TEXT:
            Serial.print("Recebendo da web: ");
            Serial.println((char*)payload);
            Serial2.println((char*)payload);
            break;
    }
}

void setup() {
    Serial.begin(115200);
    Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

    WiFi.mode(WIFI_STA); 
    
    // 2. Reduz a potência do rádio ANTES de tentar conectar para evitar o pico
    WiFi.setTxPower(WIFI_POWER_8_5dBm);

    Serial.print("Conectando ao WiFi: ");
    Serial.print(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Tentando conectar");
    }

    Serial.println();
    Serial.print("Conectado! IP da ESP: ");
    Serial.println(WiFi.localIP());

    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
}

void loop() {
    webSocket.loop();

    if (Serial2.available() > 0) {
        String msgFromMega = Serial2.readStringUntil('\n');
        msgFromMega.trim();

        if (msgFromMega.length() > 0) {
            Serial.print("Recebendo do mega: ");
            Serial.println(msgFromMega);

            webSocket.broadcastTXT(msgFromMega);
        }
    }
}