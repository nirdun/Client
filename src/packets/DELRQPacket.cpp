#include "DELRQPacket.h"


DELRQPacket::DELRQPacket(std::vector<char> &bytes) {
    this->opCode = 8;
    bytyarr = bytes;
}

DELRQPacket::DELRQPacket(const std::wstring &fileName) {
    this->opCode = 8;
    this->fileName = fileName;
}

std::wstring DELRQPacket::getFileName() {
    return fileName;
}

void DELRQPacket::setFileName(const std::wstring &fileName) {
    this->fileName = fileName;
}

wchar_t DELRQPacket::getEndByte() {
    return endByte;
}

void DELRQPacket::setEndByte(wchar_t endByte) {
    this->endByte = endByte;
}

bool DELRQPacket::haveEndByte() {
    return true;
}
