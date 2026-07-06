#include <WiFi.h>
#include <WebSocketsServer.h>

// Configurações de rede
const char* ssid = "";
const char* password = "";

// Inicia o servidor WebSocket na porta 81
WebSocketsServer webSocket = WebSocketsServer(81);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED:
            break;
        case WStype_CONNECTED:
            Serial.printf("[%u] Cliente conectado!\n", num);
            break;
        case WStype_TEXT:
            Serial.printf("%s\n", payload);
            break;
    }
}

void setup() {
    Serial.begin(115200);

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

    if (Serial.available() > 0) {
        String msgFromMega = Serial.readStringUntil('\n');
        msgFromMega.trim();

        if (msgFromMega.length() > 0) {
            webSocket.broadcastTXT(msgFromMega);
        }
    }
}