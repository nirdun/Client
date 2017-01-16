#pragma once

#include "BasePacket.h"
#include <string>


class LOGRQPacket : public BasePacket {

private:
    std::wstring userName;
public:
    wchar_t endByte = L'\0';

    LOGRQPacket();

    virtual std::wstring getUserName();

    virtual void setUserName(const std::wstring &userName);

    virtual wchar_t getEndByte();

    virtual void setEndByte(wchar_t endByte);

    virtual bool haveEndByte() override;
};
