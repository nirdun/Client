#pragma once

#include "BasePacket.h"
#include <string>
#include <vector>
#include <iostream>


class DATAPacket : public BasePacket {
public:
    short packetSize = 0;
    short blockNum = 0;
    // field from zero to 512 bytes long.
private:
    std::vector<char> data;
    std::wstring fileName;

public:
    DATAPacket(std::vector<char> &bytes);

    DATAPacket(short opCode, short size, short block, std::vector<char> &bytes);

    virtual short getPacketSize();

    virtual void setPacketSize(short packetSize);

    virtual short getBlockNum();

    virtual void setBlockNum(short blockNum);

    virtual std::vector<char> getData();

    virtual void setData(std::vector<char> &data);

    virtual std::wstring getFileName();

    virtual void setFileName(const std::wstring &fileName);
};

