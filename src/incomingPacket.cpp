#include "incomingPacket.h"

IncomingPacket::IncomingPacket(const char* rawBytes, uint16_t rawSize) {
    this->rawData = rawBytes;
    this->dataSize = rawSize;
    this->type = rawBytes[0];

    if (rawSize == 1) {
        argCount = 0;
    } else {
        for (uint8_t i = 0; i < rawSize; i++) {
            char b = rawBytes[i];
            if (b == ':') {
                separatorIndexes[argCount - 1] = i;
                argCount++;
            }
        }
    }
}

String IncomingPacket::getArg(uint8_t index) {
    if (index > argCount - 1) return String();

    char buffer[256];
    uint16_t start = (index == 0) ? 1 : separatorIndexes[index - 1] + 1;
    uint16_t end = (index == argCount - 1) ? dataSize : separatorIndexes[index];
    uint16_t argSize = (end > start) ? (end - start) : 0;

    if (argSize >= sizeof(buffer)) return String();
    strncpy(buffer, &rawData[start], argSize);
    buffer[argSize] = '\0';
    return String(buffer);
}

String IncomingPacket::getArgDecoded(uint8_t index) {
    String encoded = getArg(index);
    int encLen = encoded.length();

    char encCstr[encLen];
    strncpy(encCstr, encoded.c_str(), encLen);

    uint8_t decodedLen = base64_dec_len(encCstr, encLen);
    char decoded[decodedLen];
    base64_decode(decoded, encCstr, encLen);
    
    return String(decoded);
}

int IncomingPacket::getArgInt(uint8_t index) {
    return getArg(index).toInt();
}

char IncomingPacket::getArgChar(uint8_t index) {
    if (index > argCount - 1) return 0;
    return rawData[(index == 0) ? 1 : separatorIndexes[index - 1] + 1];
}