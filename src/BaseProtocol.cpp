#include "BaseProtocol.h"
#include "BidiEncoderDecoder.h"


using bgu::spl171::net::api::bidi::BidiMessagingProtocol;
using bgu::spl171::net::api::bidi::Connections;
using namespace bgu::spl171::net::impl::Packets;

BaseProtocol::BaseProtocol() {

}

void BaseProtocol::start(int connectionId, Connections<BasePacket *> *connections) {
    this->connectionId = connectionId;
    this->connections = static_cast<ConnectionsImpl *>(connections);
    shuoldTerminate = false;
    (static_cast<ConnectionsImpl *>(connections))->addConnection(connectionId);
    dataMap = std::unordered_map<short, DATAPacket *>();
    shouldSendMoreData = false;
    this->logedIn = false;
}

void BaseProtocol::process(BasePacket *message) {

    logedIn = connections->isLogedIn(connectionId);
    short opCode = message->getOpCode();
    if (!logedIn) {
        if (opCode == 7) {
            connections->logIn(connectionId, (static_cast<LOGRQPacket *>(message))->getUserName());
            ACKPacket tempVar();
            connections->send(connectionId, &tempVar);
        } else {
            ERRORPacket tempVar2(static_cast<short>(7));
            connections->send(connectionId, &tempVar2);
        }
    } else {
        switch (opCode) {
            case 1: {
                std::wstring currentReadFileName = (static_cast<RRQWRQPacket *>(message))->getFileName();
                if (!fileExist(currentReadFileName)) {
                    ERRORPacket tempVar3(static_cast<short>(1));
                    connections->send(connectionId, &tempVar3);
                } else {
                    this->fileName = currentReadFileName;
                    sendData(0);
                }

                break;
            }
            case 2: {

                std::wstring currentWriteFileName = (static_cast<RRQWRQPacket *>(message))->getFileName();

                if () {
                    ERRORPacket tempVar4(static_cast<short>(5));
                    connections->send(connectionId, &tempVar4);
                } else {
                    this->fileName = currentWriteFileName;
                    connections->addFile(fileName);
                    ACKPacket tempVar5();
                    connections->send(connectionId, &tempVar5);
                }
                break;
            }
            case 3:
                writeData(static_cast<DATAPacket *>(message));
                break;
            case 4:
                if (shouldSendMoreData) {
                    sendData((static_cast<ACKPacket *>(message))->getBlockNum());
                }
                break;
            case 6: {
                std::wstring files = connections->allCompletedFiles();
                //todo case files is null
                if (files != L"") {
                    try {
                        DATAPacket *dataPacket = new DATAPacket(files.getBytes(L"UTF-8"));
                        dataPacket->setBlockNum(static_cast<short>(1));
                        connections->send(connectionId, dataPacket);
                    }
                    catch (const UnsupportedEncodingException &e) {
                        e->printStackTrace();
                    }
                }
                break;
            }
            case 7:
                //todo specific error for already logged in?
                ERRORPacket tempVar6(static_cast<short>(7));
                connections->send(connectionId, &tempVar6);
                break;
            case 8: {
                //A DELRQ packet is used to request the deletion of a file in the server.
                std::wstring currentFileNameDelete = (static_cast<DELRQPacket *>(message))->getFileName();
                if (fileExist(currentFileNameDelete)) {
                    Path *path = Paths->get(std::wstring(L"//Files") + fileName);
                    connections->deleteFile(fileName);

                    try {
                        Files::
                        delete (path);
                    }
                    catch (const NoSuchFileException &x) {
                        System::err::format(std::wstring(L"%s: no such") + std::wstring(L" file or directory%n"), path);
                    }
                    catch (const DirectoryNotEmptyException &x) {
                        System::err::format(L"%s not empty%n", path);
                    }
                    catch (const IOException &x) {
                        // File permission problems are caught here.
                        System::err::println(x);
                    }
                    broadCast(false);
                }
            }
            case 10:
                ACKPacket tempVar7();
                connections->send(connectionId, &tempVar7);
                connections->disconnect(connectionId);
                break;
            default:
                std::wcout << std::wstring(L"wrong op code in  process") << std::endl;


        }
    }

}

void BaseProtocol::sendData(int numBlock) {
    std::vector<char> data;
    long long leftTosend = (file->length()) - ((numBlock) * 512);
    if (leftTosend > 512) {
        shouldSendMoreData = true;
        data = std::vector<char>(512);
    } else {
        shouldSendMoreData = false;
        data = std::vector<char>(static_cast<int>(leftTosend));
    }
    FileInputStream *stream = nullptr;
    BufferedInputStream *bufStream = nullptr;
    try {
        stream = new FileInputStream(file);
        bufStream = new BufferedInputStream(stream);
        //todo delete comment
        //            bufStream.skip((int)(numBlock)*512);
        //add bytes to data array acording to array size.
        bufStream->read(data, (numBlock) * 512, data.size());
    }
    catch (const FileNotFoundException &e) {
        e->printStackTrace();
    }
    catch (const IOException &e) {
        e->printStackTrace();
    }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
    finally
    {
        try {
            delete stream;
            delete bufStream;
        }
        catch (const IOException &e) {
            e->printStackTrace();
        }
        DATAPacket *dataPacket = new DATAPacket(data);
        dataPacket->setBlockNum(static_cast<short>(numBlock + 1));
        connections->send(connectionId, dataPacket);
    }
}

bool BaseProtocol::fileExist(const std::wstring &currentFileName) {
    file = new File(std::wstring(L"//Files/") + currentFileName);
    return file->exists();

}

void BaseProtocol::writeData(DATAPacket *dpacket) {
    dataMap[dpacket->getBlockNum()] = dpacket;
    if (dpacket->getPacketSize() != 512) {
        FileOutputStream *stream = nullptr;
        try {
            stream = new FileOutputStream(file);
            int lastBlock = dpacket->getBlockNum();
            for (int i = 1; i <= lastBlock; i++) {
                std::wcout << std::wstring(L"writing to file") << std::endl;
                stream->write(dataMap[i]->getData());
            }
            connections->completeFile(fileName);
            broadCast(true);
        }
        catch (const std::exception &e) {
            e.printStackTrace();
        }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
        finally
        {
            try {
                delete stream;
            }
            catch (const IOException &e) {
                e->printStackTrace();
            }
        }


    }
    ACKPacket tempVar(dpacket->getBlockNum());
    connections->send(connectionId, &tempVar);

}

void BaseProtocol::broadCast(bool add) {
    try {
        std::vector<char> filenamebytes = fileName.getBytes(L"UTF-8");
        BCASTPacket *bcastPacket = new BCASTPacket(filenamebytes);
        bcastPacket->setFileAdded(add);
        connections->broadcast(bcastPacket);
    }
    catch (const UnsupportedEncodingException &e) {
        e->printStackTrace();
    }

}

bool BaseProtocol::shouldTerminate() {
    return shuoldTerminate;
}

short BaseProtocol::getOpCode(std::vector<char> &byteArr) {
    short result = static_cast<short>((byteArr[0] & 0xff) << 8);
    result += static_cast<short>(byteArr[1] & 0xff);
    return result;
}

