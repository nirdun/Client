//
// Created by lidor on 1/7/17.
//


#include "../../../Desktop/ass3ClientNoWorkingRef/include/EncodeDecode.h"
#include "../../../Desktop/ass3ClientNoWorkingRef/include/connectionHandler.h"

EncodeDecode::EncodeDecode(short port, string host, ConnectionHandler& connectionHandler):
        _port(port),_addr(host),_chandler(connectionHandler), _outf(filename.c_str(), std::ios::out | std::ios::app) {
}
EncodeDecode::~EncodeDecode(){};
short EncodeDecode::bytesToShort(char *bytesArr) {
    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}
void EncodeDecode::shortToBytes(short num, char *bytesArr) {
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}
short EncodeDecode::getOpcode(string& opcode) {
    short opCode=0;
    if (opcode == "RRQ") {
        opCode = 1;
        return opCode;
    }
    if (opcode == "WRQ") {
        opCode = 2;
        return opCode;
    }

    if (opcode == "LOGRQ") {

        opCode = 7;
        return opCode;
    }
    if (opcode == "DELRQ") {

        opCode = 8;
        return opCode;
    }
    if (opcode == "DIRQ") {
        opCode = 6;
        return opCode;
    }
    if (opcode == "DISC") {
        opCode = 10;
        return opCode;
    }

    return opCode;

}
void EncodeDecode::inputFromKeyboard(short opCode,string& name) {


    switch(opCode){
        case 1:{ //RRQ
            logReadWriteDel(opCode,name);
            filename =name;
        }break;
        case 2:{ //WRQ
            logReadWriteDel(opCode,name);
            filename =name;
        }break;
        case 7:{ //LOGRQ
            logReadWriteDel(opCode,name);
        }break;
        case 8:{ //DELRQ
            logReadWriteDel(opCode,name);
        }break;
        case 6:{ //DIRQ
            dirqDisc(opCode);
        }break;
        case 10:{ //DISC
            dirqDisc(opCode);
        }break;
//        case 4:{ //ACK
//
//        }break;
        default:{ //for OPCODE 0 - NOTDIFIEND
            dirqDisc(opCode);
        }

    }

}
void EncodeDecode::logReadWriteDel(short opCode,string& name){
    cout<<"name ISS:"<<name<<endl;
    _outBytes=new char[3+name.length()];
    _outBytesSize=3+name.length();
    shortToBytes(opCode,_outBytes);
    for(unsigned i=0;i<name.length();i++) {
        _outBytes[i+2] = name.at(i);
    }
    //put last '\0'
    _outBytes[_outBytesSize-1]='\0';
}
void EncodeDecode::dirqDisc(short opCode){
    cout<<"AAA"<<endl;
    _outBytes=new char[2];
    _outBytesSize=2;
    shortToBytes(opCode,_outBytes);
}

void EncodeDecode::outputProceedReadOpcode(short opcode){

    switch (opcode){
        case 3:{//data
            char packetSize[2]; //read block
            _chandler.getBytes(&packetSize[0], 1);
            _chandler.getBytes(&packetSize[1], 1);
            short recievedPacketSize=bytesToShort(packetSize);
            char block[2]; //read block
            _chandler.getBytes(&block[0], 1);
            _chandler.getBytes(&block[1], 1);
            short recievedBlock=bytesToShort(block);
            char data[recievedPacketSize];
            for(int i=0;i<recievedPacketSize;i++){
                _chandler.getBytes(&data[i], 1);
            }

            for(int i=0;i<recievedPacketSize;i++){
                recievedData.push_back(data[i]);
                if(sendReqType==1) {
//                    if(!isInialized) {
//                        outf
//                        //outf(filename.c_str(), std::ios::out | std::ios::app);
//                        isInialized=true;
//                    }
                    string s = "";
                    for (unsigned i = 0; i < recievedData.size(); i++) {
                        s += recievedData.at(i);
                    }
                    _outf << s;
                }
            }
            if(recievedPacketSize==512){ //still waiting for more DATA packets, save them aside


                //cout<<"TOO LARGE"<<endl;
                //SEND ACK TO SERVER:
                _outBytesSize = 4;
                _outBytes=new char[4];
                char outOpcode[2];
                shortToBytes(4,outOpcode);
                _outBytes[0]=outOpcode[0];
                _outBytes[1]=outOpcode[1];
                _outBytes[2]=block[0];
                _outBytes[3]=block[1];
                if (!_chandler.sendBytes(_outBytes, _outBytesSize)) {
                    std::cout << "Error While Sending ACK("<<recievedBlock<<")"<< std::endl;
                    //break;
                }
                //reset
                delete _outBytes;
                _outBytesSize=0;
                _outBytes=0;
            }

            else{
                //packetSize was less than 512, meaning it's the last one, proceed

                cout<<"sendReqType::" <<sendReqType<<endl;
                switch (sendReqType){
                    case 1:{

//                            ofstream  outf(filename.c_str(),std::ios::out | std::ios::app );
//                            if(!outf.is_open()){
//                                cout<<"file is not open"<<endl;
//                            }
//                        else {
//                                string s = "";
//                                for (unsigned i = 0; i < recievedData.size(); i++) {
//                                    s += recievedData.at(i);
//                                }
//                                outf<<s;
                                outf.close();


                    }break;
                    case 2:{

                    }break;
                    case 6:{

                        string filename="";
                        for(int i=0;i<recievedData.size();i++){
                            char ch=recievedData[i];
                            if(ch!='\0'){
                                filename.append(1,ch);
                            }
                            else{
                                cout<<filename<<endl;
                                filename="";
                            }
                        }
                        recievedData.clear();//clear the vector after finish DIRQ
                        cout<<"END DIRQ"<<endl;
                    }break;

                }
            }


        }break;
        case 4:{//ack
            char block[2]; //read block
            _chandler.getBytes(&block[0], 1);
            _chandler.getBytes(&block[1], 1);

            short recievedBlock=bytesToShort(block);
            cout<<"ACK "<<recievedBlock<<endl;
        }break;
        case 5:{//error

            char errorCode[2];//read ErrorCode
            for(int i=0;i<2;i++){
                //connectionHandler.getBytes(&byte, 1);
                _chandler.getBytes(&errorCode[i], 1);
            }
            char ch;
            string s="";
            do{
                _chandler.getBytes(&ch, 1);
                s.append(1,ch);
            }while(ch!='\0');
            s.resize(s.length()-1);
            //cout<<"getting message"<<endl;
            short recievedErrorCode=bytesToShort(errorCode);
            cout<<"ERROR "<<recievedErrorCode<<s<<endl;
            //CONTINUIE WORK ON THE ERROR

        }break;
        case 9:{ //bCAST
            char isAdded; //read block
            _chandler.getBytes(&isAdded, 1);
            char ch='c';
            string s="";
            do{
                _chandler.getBytes(&ch, 1);
                s.append(1,ch);
            }while(ch!='\0');
            s.resize(s.length()-1);
            if(isAdded==1){
                cout<<"BCAST add "<<s<<endl;
            }
            else{
                cout<<"BCAST del "<<s<<endl;
            }
        }break;
        default:{
            cout<<"ERROR OCCURED opcode "<<endl;
        }
    }
}
//void