//
// Created by ניר דוניץ on 15.1.2017.
//

#include <boost/thread/pthread/thread_data.hpp>
#include "serverListener.h"


void ServerListener::run() {

    boost::this_thread::yield(); //Gives up the remainder of the current thread's time slice, to allow other threads to run.
}


#include <iostream>
#include <boost/thread/thread.hpp>
#include "../../../Desktop/ass3ClientNoWorkingRef/include/ServerListener.h"
#include "../../../Desktop/ass3ClientNoWorkingRef/include/KeyboardListener.h"

ServerListener::ServerListener(KeyboardListener *keyboard) : _keyboard(keyboard) {}

void ServerListener::run() {
    bool isKeyboardClosed = false;
    bool isConnectionOk = true;
    bool isFirstTimeConnected = false;
    ConnectionHandler *handler;
    EncodeDecode *encodeDecode;
    while (!isKeyboardClosed && isConnectionOk) {
        //cout << "before while" << endl;
        bool isSetDecodeEncode = false;

        //infitiy loop until client is conected
        while (!_keyboard->isConnected()) {}
        //needed for server closing
        //there is a connection, begin to listen
        if (!isSetDecodeEncode) {
            handler = _keyboard->getConnectionHandler();
            encodeDecode = _keyboard->get_encodeDecode();
            isSetDecodeEncode = true;
        }


        //cout << "server listeneer is waiting for OPCODE" << endl;

        /**GET OPCODE**/

        char opCodeArr[2];
        isConnectionOk = handler->getBytes(&opCodeArr[0], 1);
        isConnectionOk = handler->getBytes(&opCodeArr[1], 1);
        short recievedOpcode = encodeDecode->bytesToShort(opCodeArr);

        //close connection
        if (_keyboard->getOpcode() == 10 && recievedOpcode == 4) {
            //got ACK and DISC req was sent, close connection
            _keyboard->closeKeyboard();
            cout << "got ACK and DISC req was sent, close connection" << endl;

        }
        //cout<<"\n got something from socket  "<<recievedOpcode<<endl;
        encodeDecode->outputProceedReadOpcode(recievedOpcode);

        if (!_keyboard->isConnected()) {
            handler->close();
            cout << "HANDLER IS CLOSED" << endl;
            break;
        }
        //boost::this_thread::yield(); //Gives up the remainder of the current thread's time slice, to allow other threads to run.
    }

    cout << "ServerListener is closed" << endl;
}