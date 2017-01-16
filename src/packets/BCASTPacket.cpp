#include "BCASTPacket.h"


BCASTPacket::BCASTPacket(std::vector<char> &bytes) {
    this->opCode = 9;
    bytyarr = bytes;

}

BCASTPacket::BCASTPacket(std::vector<char> &bytes, short addOrDelete, const std::wstring &filename) {
    this->opCode = 9;
    this->bytyarr = bytes;
    this->fileAdded = addOrDelete == 1 ? true : false;
    this->Filename = filename;

}

BCASTPacket::BCASTPacket(const std::wstring &filename) {
    this->opCode = 9;
    this->Filename = filename;

}

std::wstring BCASTPacket::getFileName() {
    return Filename;
}

void BCASTPacket::setFilename(const std::wstring &filename) {
    Filename = filename;
}

bool BCASTPacket::isFileAdded() {
    return fileAdded;
}

void BCASTPacket::setFileAdded(bool fileAdded) {
    this->fileAdded = fileAdded;
}

bool BCASTPacket::haveEndByte() {
    return true;
}
