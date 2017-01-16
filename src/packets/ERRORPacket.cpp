#include "ERRORPacket.h"

ERRORPacket::ERRORPacket(short errorType) {
    this->opCode = 5;
    this->ErrorCode = errorType;
    difineErrMsg();
}

ERRORPacket::ERRORPacket(short errorType, const std::wstring &errMsg) {
    this->opCode = 5;
    this->ErrorCode = errorType;
    this->ErrMsg = errMsg;
}

void ERRORPacket::difineErrMsg() {
    switch (ErrorCode) {
        case 0:
            ErrMsg = L"Not defined, see error message (if any).";
            break;
        case 1:
            ErrMsg = L"File not found – RRQ \\ DELRQ of non-existing file.";
            break;
        case 2:
            ErrMsg = L"Access violation – File cannot be written, read or deleted.";
            break;
        case 3:
            ErrMsg = L"Disk full or allocation exceeded – No room in disk.";
            break;
        case 4:
            ErrMsg = L"Illegal TFTP operation – Unknown Opcode.";
            break;
        case 5:
            ErrMsg = L"File already exists – File name exists on WRQ.";
            break;
        case 6:
            ErrMsg = L"User not logged in – Any opcode received before Login completes.";
            break;
        case 7:
            ErrMsg = L"User already logged in – Login username already connected.";
            break;
        default:
            ErrMsg = L"Wrong error code insert";

    }
}

bool ERRORPacket::haveEndByte() {
    return true;
}

std::wstring ERRORPacket::getErrMsg() {
    return ErrMsg;
}

void ERRORPacket::setErrMsg(const std::wstring &errMsg) {
    ErrMsg = errMsg;
}

short ERRORPacket::getEndByte() {
    return endByte;
}

void ERRORPacket::setEndByte(short endByte) {
    this->endByte = endByte;
}

int ERRORPacket::getErrorType() {
    return ErrorCode;
}

void ERRORPacket::setErrorType(short errorType) {
    this->ErrorCode = errorType;
}

short ERRORPacket::getErrorCode() {
    return ErrorCode;
}

void ERRORPacket::setErrorCode(short errorCode) {
    ErrorCode = errorCode;
}