#include <WebServer.h>
#include "display.h"
#include <stdint.h>

namespace httpserver {
    WebServer server(80);
    static uint8_t* imageBuffer = nullptr;
    static size_t imageSize = 0;
    static size_t imageCapacity = 0;
    static size_t MAX_IMAGE_SIZE = 30 * 1024; // 30 KB max for now

    void respondWithSameMessage() {
        String reply = "ESP32 received your message: ";
        String message = server.arg("message");
        Serial.printf("Received message: %s\n", message.c_str());
        server.send(200, "text/plain", (reply + message).c_str());
    }

    void resetImageBuffer() {
        free(imageBuffer);
        imageBuffer = nullptr;
        imageSize = 0;
        imageCapacity = 0;
    }

    void receiveImage() {
        HTTPUpload& upload = server.upload();
        HTTPUploadStatus status = upload.status;
        switch (status) {
            case UPLOAD_FILE_START: {
                Serial.printf("Start receiving file: %s\n", upload.filename.c_str());
                resetImageBuffer();
                break;
            }
            case UPLOAD_FILE_WRITE: {
                size_t newSize = imageSize + upload.currentSize;
                if (newSize > MAX_IMAGE_SIZE) {
                    Serial.println("Image upload too large");
                    resetImageBuffer();
                    server.send(413, "text/plain", "Image too large");
                    return;
                }
                // allocate memory if necessary
                if (newSize > imageCapacity) {
                    size_t newCapacity = newSize;
                    uint8_t* newBuffer = (uint8_t*)realloc(imageBuffer, newCapacity);
                    if (!newBuffer) {
                        resetImageBuffer();
                        Serial.println("Failed to allocate memory for image");
                        return;
                    }
                    imageBuffer = newBuffer;
                    imageCapacity = newCapacity;
                }
                memcpy(imageBuffer + imageSize, upload.buf, upload.currentSize);
                imageSize += upload.currentSize;
                break;
            }
            case UPLOAD_FILE_END: {
                Serial.printf("Finished receiving file: %s, total size: %d bytes\n", upload.filename.c_str(), upload.totalSize);
                display::displayImage(upload.buf, upload.currentSize);
                break;
            }
            case UPLOAD_FILE_ABORTED: {
                Serial.printf("File upload aborted: %s\n", upload.filename.c_str());
                resetImageBuffer();
                break;
            }
        }
    }

    // response after request is processed
    void receiveImageResponse() {
        if (!imageBuffer || imageSize == 0) {
            server.send(400, "text/plain", "No image uploaded");
            return;
        }

        server.send(200, "text/plain", "Image received and displayed");
    }
    void init() {
        server.begin();
        server.on("/", HTTP_POST, respondWithSameMessage);
        server.on("/image", HTTP_POST, receiveImageResponse, receiveImage);
    }
    void listenForConnections() {
        server.handleClient();
    }
}