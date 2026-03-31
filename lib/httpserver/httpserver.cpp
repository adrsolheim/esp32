#include <WebServer.h>

namespace httpserver {
    WebServer server(80);

    void respondWithSameMessage() {
        String reply = "ESP32 received your message: ";
        String message = server.arg("message");
        Serial.printf("Received message: %s\n", message.c_str());
        server.send(200, "text/plain", (reply + message).c_str());
    }
    void init() {
        server.begin();
        server.on("/", HTTP_POST, respondWithSameMessage);
    }
    void listenForConnections() {
        server.handleClient();
    }
}