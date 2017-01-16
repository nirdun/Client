//
// Created by lidor on 1/8/17.
//

#include <iostream>
#include <boost/thread/thread.hpp>
#include "../../../Desktop/ass3ClientNoWorkingRef/include/KeyboardListener.h"
#include "../../../Desktop/ass3ClientNoWorkingRef/include/connectionHandler.h"
#include "../../../Desktop/ass3ClientNoWorkingRef/include/EncodeDecode.h"

KeyboardListener::KeyboardListener(short port,string &server ):_port(port),_server(server),_isConnected(false),_cHandler(0),_shouldTerminate(0) {
//    _isConnected=false;
//    _cHandler= nullptr; char *argv[]
}

short KeyboardListener::getOpcode()const {
        return _opCode;
};
void KeyboardListener::run() {

    //192.168.56.1 7777

    ConnectionHandler handler(_server, _port);
    EncodeDecode encodeDecode(_port, _server, handler);
    _cHandler = &handler; //copy reference to the pointer , so server could get this object
    _encodeDecode = &encodeDecode;
    if (!handler.connect()) {
        std::cerr << "Cannot connect to " << _server << ":" << _port << std::endl;

    } else {
        _isConnected = true;
        cout << "connected was ok" << endl;
    }
    while (_isConnected) {
        //Client client(port, host, connectionHandler);

        //bool _shouldTerminate = false;
        //bool _sentDISC = false;
        while (!_shouldTerminate) {
            string name;

            const short bufsize = 1024;
            char buf[bufsize];
            //if(_opCode==10) { //if DISC was sent this is not avialable anymore
            std::cin.getline(buf, bufsize);
            //}

            std::string line(buf);
            int len = line.length();
            //spilt theab input so we could get Command and other string
            int space;
            int countSpaces = 0;
            for (int i = 0; i < len; i++) {
                if (line.at(i) == ' ') {
                    space = i;
                    countSpaces++;
                }
            }
            string opcodeInput;
            if (countSpaces == 1) { //Opcode+name
                opcodeInput = line.substr(0, space);
                name = line.substr(space + 1, line.length());
            } else { //DISC
                opcodeInput = line;
                name = "";
            }
            _opCode = _encodeDecode->getOpcode(opcodeInput);

            //now it's possible to start the request
            if(_opCode==10){ //mark should terminate if its DISC, and wait for response ACK from server, serverListener will change the field _isConnected and exit
                _shouldTerminate=true;
            }
            //save this in order to remember which request keyboardListeneer sent to Server
            switch (_opCode) {//1 for RRQ, 2 for WRQ , 6 for DIRQ
                case 1:
                    _encodeDecode->sendReqType = 1;
                    break;
                case 2:
                    _encodeDecode->sendReqType = 2;
                    break;
                case 6:
                    _encodeDecode->sendReqType = 6;
                    break;
                default:
                    _encodeDecode->sendReqType = 0;
            }
            _encodeDecode->inputFromKeyboard(_opCode, name);
            //char *tempptr=_encodeDecode->_outBytes;

            char *outbytes = _encodeDecode->getOutBytes();
            int outbytesSize = _encodeDecode->_outBytesSize;
//            for (int i = 0; i < outbytesSize; i++) {
//                cout << (*(outbytes + i)) << endl;
//            }
            //
            if (!handler.sendBytes(outbytes, outbytesSize)) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;

                cout<<"BALALBAB"<<endl;
                //break;
            }
            cout << "Succussfuly sent:" << _opCode << endl;
            //safe delete all aloocations
            delete outbytes;
            _encodeDecode->_outBytesSize = 0;
            _encodeDecode->resetOutBytes();
        }
        //boost::this_thread::yield(); //Gives up the remainder of the current thread's time slice, to allow other threads to run.
    }
    cout << "Keyboard is Closed" << endl;
}
