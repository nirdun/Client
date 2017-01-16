#pragma once

#include "BasePacket.h"
#include <string>
#include <vector>


class DELRQPacket : public BasePacket {
public:
    std::wstring fileName;
    wchar_t endByte = L'\0';

    DELRQPacket(std::vector<char> &bytes);

    DELRQPacket(const std::wstring &fileName);

    virtual std::wstring getFileName();

    virtual void setFileName(const std::wstring &fileName);

    virtual wchar_t getEndByte();

    virtual void setEndByte(wchar_t endByte);

    virtual bool haveEndByte() override;
};
