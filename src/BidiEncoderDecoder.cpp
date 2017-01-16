//
// Created by ניר דוניץ on 16.1.2017.
//

#include "BidiEncoderDecoder.h"
#include "packets/BasePacket.h"
#include "packets/DIRQPacket.h"
#include "packets/DISCPacket.h"
#include "packets/ACKPacket.h"
#include "packets/ERRORPacket.h"


#include <string>
#include <vector>
#include <iostream>
;


BidiEncoderDecoder::BidiEncoderDecoder(){
    std::wcout << std::wstring(L"inside BidiEncoderDecoder c-tor") << std::endl;
    counterRead = 0;
    this->opCode = opCode;
    byteArr = std::vector<char>(1024); // todo size?
}
//
//BasePacket* BidiEncoderDecoder::decodeNextByte(char nextByte){
//        byteArr[counterRead] = nextByte;
//        counterRead++;
//        BasePacket *packet = nullptr;
//    std::set<short > haveEndByte={1,2,4};
//    std::set<short >::iterator it;
//
//
//
//        //initialize op code.
//        if (counterRead == 2) {
//            opCode = byteArr[0]);
//
//            // directory listing
//            if (opCode == 6) {
//                return new DIRQPacket();
//            } else if (opCode == 10) {
//                //disconnect
//                return new DISCPacket();
//            }
//        }
//    it=haveEndByte.find(opCode);
//        if ( it!=&& opCode != 0) {
//            if (opCode == 4) {
//                return new ACKPacket();
//            } else if (opCode == 3) {
//                packet = createDataPacket();
//            }
//        } else if (!shouldContinueRead(nextByte) && opCode != 0) {
//            packet = createPacket(opCode, byteArr);
//        }
//        return packet;
//    }
//
//    DATAPacket* BidiEncoderDecoder:: createDataPacket() {
//        DATAPacket *dPacket = nullptr;
//        // make a one bigger
//
//
//        if (counterRead == 4) {
//            //size of data and first six bytes.
//            packetSize = bytesToShort(byteArr) + 6;
//        } else if (counterRead == packetSize) {
//            //todo divide packet
//            dPacket = new DATAPacket(Arrays::copyOf(byteArr, packetSize));
//        }
//
//        return dPacket;
//    }
//
//    virtual BasePacket *createPacket(short opCode, std::vector<char> &bytes) {
//        BasePacket *packet = nullptr;
//        switch (opCode) {
//            //Read request.
//            case 1: {
//                std::wstring fileNameWRQ = bytesArrToString((Arrays::copyOfRange(bytes, 2, counterRead - 1)));
//                packet = new RRQWRQPacket(bytes, opCode, fileNameWRQ);
//                std::wstring fileName = bytesArrToString((Arrays::copyOfRange(bytes, 2, counterRead - 1)));
//                (static_cast<RRQWRQPacket *>(packet))->setFileName(fileName);
//
//
//                break;
//                //Write request
//            }
//            case 2: {
//                std::wstring fileNameRRQ = bytesArrToString((Arrays::copyOfRange(bytes, 2, counterRead - 1)));
//                packet = new RRQWRQPacket(bytes, opCode, fileNameRRQ);
//                break;
//                //Error request.
//            }
//            case 5: {
//                //todo - check if insert err msg different from value code optional
//                int errorCode = bytesToShort(Arrays::copyOfRange(bytes, 2, 4));
//                packet = new ERRORPacket(static_cast<short>(errorCode));
//                break;
//                //Login request
//            }
//            case 7: {
//                packet = new LOGRQPacket();
//                std::wstring userName = bytesArrToString((Arrays::copyOfRange(bytes, 2, counterRead - 1)));
//                (static_cast<LOGRQPacket *>(packet))->setUserName(userName);
//
//                break;
//                //Delete request
//            }
//            case 8: {
//                std::wstring fileNameDelrq = bytesArrToString((Arrays::copyOfRange(bytes, 2, counterRead - 1)));
//                packet = new DELRQPacket(fileNameDelrq);
//                break;
//                //Broadcast request
//            }
//            case 9: {
//                std::wstring fileNameBcast = bytesArrToString((Arrays::copyOfRange(bytes, 3, counterRead - 1)));
//                packet = new BCASTPacket(bytes, static_cast<short>(bytes[2]), fileNameBcast);
//                break;
//            }
//            default:
//                std::wcout << std::wstring(L"Wrong OpCode") << std::endl;
//        }
//        return packet;
//    }
//
//
//    virtual std::wstring bytesArrToString(std::vector<char> &bytes) {
//        //notice that we explicitly requesting that the string will be decoded from UTF-8
//        //this is not actually required as it is the default encoding in java.
//        std::wstring result = std::wstring(bytes, 0, bytes.size(), StandardCharsets::UTF_8);
//        return result;
//    }
//
//    //return true if finish byte-0 is reading
//private:
//    bool shouldContinueRead(char nextByte) {
//        return (nextByte != 0);
//    }
std::vector<char>BidiEncoderDecoder:: encode(BasePacket *message){
        opCode = message->getOpCode();
        switch (opCode) {
            //todo : should be more packets? example DELRQ ?
            case 3:
                byteArr = encodeDataPacket(static_cast<DATAPacket *>(message));
                break;
            case 4:
                byteArr = encodeACK(static_cast<ACKPacket *>(message));
                break;
            case 5:
                byteArr = encodeERROR(static_cast<ERRORPacket *>(message));
                break;
            case 9:
                byteArr = encodeBCAST(static_cast<BCASTPacket *>(message));
                break;
            default:
                std::wcout << std::wstring(L"Wrong OpCode") << std::endl;
        }
        return byteArr;
    }

std::vector<char> BidiEncoderDecoder::encodeDataPacket(DATAPacket *dpacket){
        short packetSize = dpacket->getPacketSize();

        //todo - check id bytes ok
        std::wcout << std::wstring(L"size of data packet in encodeDataPacket fun : ") << packetSize << std::endl;
        std::vector<char> opCodeByte = shortToBytes(opCode);
        std::vector<char> packetSizeBytes = shortToBytes(packetSize);
        std::vector<char> blockNumberBytes = shortToBytes(dpacket->getBlockNum());
        return mergeArrays({opCodeByte, packetSizeBytes, blockNumberBytes, dpacket->getData()});
    }



//    virtual std::vector<char> encodeACK(ACKPacket *packet) {
//        std::vector<char> opCodeByte = shortToBytes(opCode);
//        std::vector<char> blockBytes = shortToBytes(packet->getBlockNum());
//
//        //todo delete comments
//        //        System.arraycopy(opCodeByte, 0, bytes, 0, opCodeByte.length);
//        //        System.arraycopy(blockBytes, 0, bytes, opCodeByte.length, blockBytes.length);
//        return mergeArrays({opCodeByte, blockBytes});
//    }

        std::vector<char> BidiEncoderDecoder::encodeERROR(ERRORPacket *dpacket){
//        std::vector<char> opCodeByte = shortToBytes(opCode);
            char opcode2=dpacket->getOpCode();
            char errorCode=dpacket->getErrorCode();
//        std::vector<char> errorCode = shortToBytes(packet->getErrorCode());
//        std::vector<char> errorMsg;
            char *encodeErr=new char[dpacket->getErrMsg().size()+];
            a[dpacket->getErrMsg().size()]=0;
            memcpy(a,dpacket->getErrMsg().c_str(),s.size());
        try {
            errorMsg = packet->getErrMsg().getBytes("UTF-8");
        }
        catch (const UnsupportedEncodingException &e) {
            e->printStackTrace();
        }


        return mergeArrays({opCodeByte, errorCode, errorMsg, endByte});


    virtual short getOpCode(std::vector<char> &byteArr) {
        short result = static_cast<short>((byteArr[0] & 0xff) << 8);
        result += static_cast<short>(byteArr[1] & 0xff);
        return result;
    }

    virtual std::vector<char> shortToBytes(short num) {
        std::vector<char> bytesArr(2);
        bytesArr[0] = static_cast<char>((num >> 8) & 0xFF);
        bytesArr[1] = static_cast<char>(num & 0xFF);
        return bytesArr;
    }


    virtual short bytesToShort(std::vector<char> &byteArr) {
        short result = static_cast<short>((byteArr[0] & 0xff) << 8);
        result += static_cast<short>(byteArr[1] & 0xff);
        return result;
    }


    /// <summary>
    /// merge multiple byre arrays to one array.
    /// </summary>
    /// <param name="arrays"> is byte arrays. </param>
    /// <returns> merged Array. </returns>
    //todo check if private?
    static std::vector<char> mergeArrays(std::vector<char> &arrays) {
        // Count the number of arrays passed for merging and the total size of resulting array
        int arrCount = 0;
        int count = 0;
        for (char[] array_Renamed :
            arrays)
        {
            arrCount++;
            count += array_Renamed.size();
        }
        std::wcout << std::wstring(L"Arrays passed for merging : ") << arrCount << std::endl;
        std::wcout << std::wstring(L"Array size of resultig array : ") << count << std::endl;

        // Create new array and copy all array contents
        int start = 0;
        std::vector<char> mergedArray(count);
        for (char[] array_Renamed :
            arrays)
        {
            System::arraycopy(array_Renamed, 0, mergedArray, start, array_Renamed.size());
            start += array_Renamed.size();
        }
        return mergedArray;
    }
