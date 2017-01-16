//
// Created by ניר דוניץ on 16.1.2017.
//

#ifndef BIDIENCODERDECODER_H
#define BIDIENCODERDECODER_H


#include "keyboardListener.h"
#include "packets/BasePacket.h"
#include "packets/DIRQPacket.h"
#include "packets/DATAPacket.h"
#include "packets/ERRORPacket.h"

class BidiEncoderDecoder {
private:
    short opCode = 0;
    int packetSize = 0;
    std::vector<char> byteArr;
    int counterRead = 0;

    BidiEncoderDecoder();

    BasePacket *decodeNextByte(char nextByte);

    DATAPacket *createDataPacket();

//    static Set<int> *const haveEndByte = std::unordered_set<int>(Arrays::asList(1, 2, 5, 7, 8, 9));
    std::vector<char> encode(BasePacket *packet);
    std::vector<char> encodeDataPacket(DATAPacket *dpacket);
    std::vector<char> encodeERROR(ERRORPacket *dpacket);

};

#endif //BIDIENCODERDECODER_H
