#include "DATAPacket.h"


DATAPacket::DATAPacket(std::vector<char> &bytes) {
    this->opCode = 3;
    this->data = bytes;
    this->setPacketSize(static_cast<short>(data.size()));
}

DATAPacket::DATAPacket(short opCode, short size, short block, std::vector<char> &bytes) {
    this->opCode = 3;
    this->data = bytes;
    setBlockNum(block);
    this->setPacketSize(static_cast<short>(data.size()));
}

short DATAPacket::getPacketSize() {
    return packetSize;
}

void DATAPacket::setPacketSize(short packetSize) {
    this->packetSize = packetSize;
}

short DATAPacket::getBlockNum() {
    return blockNum;
}

void DATAPacket::setBlockNum(short blockNum) {
    this->blockNum = blockNum;
}

std::vector<char> DATAPacket::getData() {
    //todo - clone?
    std::wcout << std::wstring(L"returning data without cloning- check") << std::endl;
    return data;
}

void DATAPacket::setData(std::vector<char> &data) {
    this->data = data;
}

std::wstring DATAPacket::getFileName() {
    return fileName;
}

void DATAPacket::setFileName(const std::wstring &fileName) {
    this->fileName = fileName;
}
