#include "RRQWRQPacket.h"

RRQWRQPacket::RRQWRQPacket(std::vector<char> &bytes, short opCode, const std::wstring &fileName) {
    this->opCode = opCode;
    this->bytyarr = bytes;
    this->fileName = fileName;

}

std::wstring RRQWRQPacket::getFileName() {
    return fileName;
}

void RRQWRQPacket::setFileName(const std::wstring &fileName) {
    this->fileName = fileName;
}

wchar_t RRQWRQPacket::getEndByte() {
    return endByte;
}

void RRQWRQPacket::setEndByte(wchar_t endByte) {
    this->endByte = endByte;
}

bool RRQWRQPacket::haveEndByte() {
    return true;
}
