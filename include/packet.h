#pragma once
#include <Arduino.h>
#include <Base64.h>

class Packet {
    private:
    String transmitData;
    public:
    bool sent = false;
    bool empty = true;

    Packet(char type);
    void appendData(const char* data);
    void appendData(char data);
    void appendData(int data);
    void transmit();
};