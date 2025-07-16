#include "packet.h"

Packet::Packet(char type) {
    transmitData = type;
}

void Packet::appendData(const char* data) {
    uint8_t len = strlen(data);
    char b64[base64_enc_len(len)];
    char buffer[len+1];    
    strncpy(buffer, data, len+1);
    base64_encode(b64, buffer, len);
    
    if (!empty) transmitData += ':';
    transmitData += String(b64);
    empty = false;
}

void Packet::appendData(char data) {
    if (!empty) transmitData += ':';
    transmitData += data;
    empty = false;
}

void Packet::appendData(int data) {
    if (!empty) transmitData += ':';
    transmitData += String(data);
    empty = false;
}

void Packet::transmit() {
    sent = true;
    Serial.print(transmitData);
    Serial.write('\n');
}