#include "Particle.h"

/* Initialize constants */
const unsigned long SEND_INTERVAL_MS = 1000;
const size_t READ_BUF_SZ = 64;

// Forward declarations
void processBuffer();

/* Initialize variables */
int counter = 0;
unsigned long lastSend = 0;
char readBuf[READ_BUF_SZ];
size_t readBufOffset = 0;

/* Declare pin mapping */
void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
}

void loop() {

    // Read data from serial
    while(Serial1.available()) {
        if (readBufOffset < READ_BUF_SZ) {
            char read_char = Serial1.read();
            // Read as long as read character NOT new line
            if (read_char != '\n') {
                // Add to buffer
                readBuf[readBufOffset++] = c;
            }
            else {
                // End of line character
                // Call processBuffer
                readBuf[readBufOffset] = 0;
                processBuffer();
                readBufOffset = 0;
            }
        }
        else {
            Serial.println("readBuf overflow!!");
            readBufOffset = 0;
        }
    }

}

// Declare helper functions
// Publish to cloud
void processBuffer() {
    Particle.publish(readBuf);
}
