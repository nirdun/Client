#pragma once

#include "BasePacket.h"
#include <string>

class ERRORPacket : public BasePacket {
private:
    std::wstring ErrMsg;
    short endByte = 0;
    short ErrorCode = 0;

public:
    ERRORPacket(short errorType);

    ERRORPacket(short errorType, const std::wstring &errMsg);

private:
    void difineErrMsg();

public:
    virtual bool haveEndByte() override;


    virtual std::wstring getErrMsg();

    virtual void setErrMsg(const std::wstring &errMsg);

    virtual short getEndByte();

    virtual void setEndByte(short endByte);

    virtual int getErrorType();

    virtual void setErrorType(short errorType);

    virtual short getErrorCode();

    virtual void setErrorCode(short errorCode);
};