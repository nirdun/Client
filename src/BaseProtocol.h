#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <stdexcept>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace bgu { namespace spl171 { namespace net { namespace impl { namespace TFTP { template<typename T>class BidiEncoderDecoder; } } } } }

namespace bgu
{
	namespace spl171
	{
		namespace net
		{
			namespace impl
			{
				namespace TFTP
				{


					using bgu::spl171::net::api::bidi::BidiMessagingProtocol;
					using bgu::spl171::net::api::bidi::Connections;
					using namespace bgu::spl171::net::impl::Packets;


					class BaseProtocol : public BidiMessagingProtocol<BasePacket*>
					{
					private:
						BidiEncoderDecoder *BidiEncoderDecoder;
						ConnectionsImpl<BasePacket*> *connections;
						int connectionId = 0;
						bool shuoldTerminate = false;
						std::unordered_map<short, DATAPacket*> dataMap;
						std::wstring fileName;
						File *file;
						bool shouldSendMoreData = false;
						bool logedIn = false;


					public:
						virtual ~BaseProtocol()
						{
							delete BidiEncoderDecoder;
							delete connections;
							delete file;
						}

						BaseProtocol();

						virtual void start(int connectionId, Connections<BasePacket*> *connections) override;

						virtual void process(BasePacket *message) override;


					private:
						void sendData(int numBlock);


						bool fileExist(const std::wstring &currentFileName);

					public:
						virtual void writeData(DATAPacket *dpacket);

						/// <summary>
						/// send broadcast message if delete/add file.
						/// </summary>
						/// <param name="add"> is true was added,false if need to delete file. </param>
					private:
						void broadCast(bool add);

					public:
						virtual bool shouldTerminate() override;

						virtual short getOpCode(std::vector<char> &byteArr);
					};

				}
			}
		}
	}
}
