#include <WebServer.h>

WebServer server(80);

void init() {
    server.begin();
    server.on("/", HTTP_POST, respondWithSameMessage);
}
void listenForConnections() {
    server.handleClient();
}

void respondWithSameMessage() {
    String message = server.arg("message"); // get the "message" argument from the request
    server.send(200, "text/plain", message.c_str());
}