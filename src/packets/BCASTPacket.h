#pragma once

#include "BasePacket.h"
#include <string>
#include <vector>


class BCASTPacket : public BasePacket {
private:
    std::wstring Filename;
    bool fileAdded = false;

public:
    BCASTPacket(std::vector<char> &bytes);

    BCASTPacket(std::vector<char> &bytes, short addOrDelete, const std::wstring &filename);

    BCASTPacket(const std::wstring &filename);

    //todo initiailize while getting bytes.
    virtual std::wstring getFileName();

    virtual void setFilename(const std::wstring &filename);

    virtual bool isFileAdded();

    virtual void setFileAdded(bool fileAdded);

    virtual bool haveEndByte() override;
};
