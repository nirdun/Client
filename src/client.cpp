#include <stdlib.h>
#include "../../../Desktop/ass3ClientNoWorkingRef/include/connectionHandler.h"
#include <iostream>
#include <boost/thread.hpp>
#include "../../../Desktop/ass3ClientNoWorkingRef/include/EncodeDecode.h"
#include "../../../Desktop/ass3ClientNoWorkingRef/include/KeyboardListener.h"
#include "../../../Desktop/ass3ClientNoWorkingRef/include/ServerListener.h"

using namespace std;


//short bytesToShort(char* bytesArr) {
//    short result = (short)((bytesArr[0] & 0xff) << 8);
//    result += (short)(bytesArr[1] & 0xff);
//    return result;
//}
//void shortToBytes(short num, char* bytesArr) {
//    bytesArr[0] = ((num >> 8) & 0xFF);
//    bytesArr[1] = (num & 0xFF);
//}
//

int main(int argc, char *argv[]) {
    //192.168.56.1 7777
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);



    KeyboardListener keyboardThread(port,host);
    ServerListener serverThread(&keyboardThread);

    boost::thread th1(&KeyboardListener::run,&keyboardThread);
    boost::thread th2(&ServerListener::run,&serverThread);
    th1.join();
    th2.join();
    cout<<"Client is closed"<<endl;

//
//    //192.168.56.1 7777
//    if (argc < 3) {
//        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
//        return -1;
//    }
//    std::string host = argv[1];
//    short port = atoi(argv[2]);
//
//    ConnectionHandler connectionHandler(host, port);
//    if (!connectionHandler.connect()) {
//        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
//        return 1;
//    }
//
//    cout << "connected was ok" << endl;
//    Client client(port, host, connectionHandler);
//
//    //From here we will see the rest of the ehco client implementation:
//    bool _shouldTerminate = false;
//    bool _sentDISC = false;
//    while (!_shouldTerminate) {
//        short opCode = 0;
//        string name;
//
//        const short bufsize = 1024;
//        char buf[bufsize];
//        cout << "->";
//        std::cin.getline(buf, bufsize);
//
//        std::string line(buf);
//        int len = line.length();
//        //spilt theab input so we could get Command and other string
//        int space;
//        int countSpaces = 0;
//        for (int i = 0; i < len; i++) {
//            if (line.at(i) == ' ') {
//                space = i;
//                countSpaces++;
//            }
//        }
//        string opcodeInput;
//        if (countSpaces == 1) { //Opcode+name
//            opcodeInput = line.substr(0, space);
//            name = line.substr(space + 1, line.length());
//        } else { //DISC
//            opcodeInput = line;
//            name = "";
//        }
//        opCode = client.getOpcode(opcodeInput);
//
//        //now it's possible to start the request
//        if (opCode == 10) { //prepere for disconnection
//            _sentDISC = true;
//        }
//        switch(opCode){//1 for RRQ, 2 for WRQ , 6 for DIRQ
//            case 1:client.sendReqType=1;break;
//            case 2:client.sendReqType=2;break;
//            case 6:client.sendReqType=6;break;
//            default:client.sendReqType=0;
//        }
//        client.input(opCode, name);
//        char *outbytes = client._outBytes;
//        int outbytesSize = client._outBytesSize;
//
//        //
//        cout << "Sending to server :" << opCode << endl;
//        if (!connectionHandler.sendBytes(outbytes, outbytesSize)) {
//            std::cout << "Disconnected. Exiting...\n" << std::endl;
//            //break;
//        }
//        cout << "Succussfuly sent:" << opCode << endl;
//        //safe delete all aloocations
//        delete outbytes;
//        client._outBytesSize = 0;
//        client._outBytes = 0;
//        /**GET OPCODE**/
//        char opCodeArr[2];
//        connectionHandler.getBytes(&opCodeArr[0], 1);
//        connectionHandler.getBytes(&opCodeArr[1], 1);
//        short recievedOpcode = client.bytesToShort(opCodeArr);
//        cout<<"got something from server -" <<recievedOpcode<<endl;
//        /**GOT OPCODE**/
//        //for ending the loop
//        if (recievedOpcode == 4 && _sentDISC) { //recieved an ACK for DISC req, end client
//            _shouldTerminate = true;
//        }
//        //continue to read with provided Opcode.
//        client.proceedReadWithOpcode(recievedOpcode);
//
//
//        // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
////        std::cout << "Sent " << len+1 << " bytes to server" << std::endl;
////        if (!connectionHandler.sendLine(line)) {
////            std::cout << "Disconnected. Exiting...\n" << std::endl;
////            //break;
////        }
//        // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
//
//
//        // We can use one of three options to read data from the server:
//        // 1. Read a fixed number of characters
//        // 2. Read a line (up to the newline character using the getline() buffered reader
//        // 3. Read up to the null character
////        std::string answer;
////        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
////        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
////        std::string ans;
////        int strL=(int)ans.length();
////        char byte;
////        cout<<"getting message"<<endl;
////        for(int i=0;i<arrSize;i++){
////            if(arr[i]=='\0'){
////                break;
////            }
////            cout<<arr[i];
////        }
////
//
//
//        //cout<<"\n fished"<<client.bytesToShort(arr)<<endl;
//// if (!connectionHandler.getLine(answer)) {
////            std::cout << "Disconnected. Exiting...\n" << std::endl;
////           // break;
////        }
////
////		len=answer.length();
////		// A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
////		// we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
////        answer.resize(len-1);
////        std::cout << "Reply: " << answer << " " << len << " bytes " << std::endl << std::endl;
////        if (answer == "bye") {
////            std::cout << "Exiting...\n" << std::endl;
////            //break;
////        }
//    }
//
//    connectionHandler.close();
//    cout << "Client is Closed" << endl;

    return 0;
}


