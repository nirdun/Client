cmake_minimum_required(VERSION 3.6)
project(Client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp src/echoClient.cpp src/connectionHandler.cpp include/connectionHandler.h src/serverListener.cpp src/serverListener.h src/keyboardListener.cpp src/keyboardListener.h src/client.cpp src/BidiEncoderDecoder.cpp src/BidiEncoderDecoder.h src/packets/ACKPacket.h
        src/packets/ACKPacket.cpp
        src/packets/BasePacket.cpp
        src/packets/BasePacket.h
        src/packets/BCASTPacket.cpp
        src/packets/BCASTPacket.h
        src/packets/DATAPacket.cpp
        src/packets/DATAPacket.h
        src/packets/DELRQPacket.cpp
        src/packets/DELRQPacket.h
        src/packets/DIRQPacket.cpp
        src/packets/DISCPacket.cpp
        src/packets/DIRQPacket.h
        src/packets/DISCPacket.h
        src/packets/ERRORPacket.h
        src/packets/LOGRQPacket.cpp
        src/packets/ERRORPacket.cpp
        src/packets/LOGRQPacket.h
        src/packets/RRQWRQPacket.cpp
        src/packets/RRQWRQPacket.h)
add_executable(Client ${SOURCE_FILES} main.cpp)
