#include "LOGRQPacket.h"

LOGRQPacket::LOGRQPacket() {
    this->opCode = 7;

}

std::wstring LOGRQPacket::getUserName() {
    return userName;
}

void LOGRQPacket::setUserName(const std::wstring &userName) {
    this->userName = userName;
}

wchar_t LOGRQPacket::getEndByte() {
    return endByte;
}

void LOGRQPacket::setEndByte(wchar_t endByte) {
    this->endByte = endByte;
}

bool LOGRQPacket::haveEndByte() {
    return true;
}