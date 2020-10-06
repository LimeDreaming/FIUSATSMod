// ILikeBanas

#include "util/Logging.h"
#include <iostream>
#include <WS2tcpip.h>
#include <stdio.h>
#include <string> 

#pragma comment (lib, "ws2_32.lib")

using namespace std;
#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FIUSATSMOD_API Socket
{
private:
	SOCKET Sock;
	WSADATA wsData;
	WORD version = MAKEWORD(2, 2);

public:

	/*Socket(SOCKET socket) {
		Sock = socket;
	}

	~Socket() {
		closesocket(Sock);
	}*/

	bool IniWin() {
		int wsResult = WSAStartup(version, &wsData);
		if (wsResult == 0) {
			//SML::Logging::info("[FIUSATS] - WinSock created!");
			return true;
		}
		else {
			//SML::Logging::info("[FIUSATS] - WinSock failed to created!");
			return false;
		}
	}

	bool Connect(FString ipAdress, int port) {
		SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
		std::string ip = std::string(TCHAR_TO_UTF8(*ipAdress));
		if (sock == INVALID_SOCKET) {
			/*cerr << "Can't create Socket! #" << WSAGetLastError() << endl;
			return; */
		}

		sockaddr_in socketset;
		socketset.sin_family = AF_INET;
		socketset.sin_port = htons(port);
		inet_pton(AF_INET, ip.c_str(), &socketset.sin_addr);

		int conSocket = connect(sock, (sockaddr*)&socketset, sizeof(socketset));
		if (conSocket != INVALID_SOCKET) {
			//SML::Logging::info("[FIUSATS] - Connection to "+ ip + ":" + std::to_string(port) + " created!");
			return true;
		}
		else {
			//SML::Logging::info("[FIUSATS] - Connection to " + ip + ":" + std::to_string(port) + " failed!");
			return false;
		}
	}

	bool Send(FString string, int32 leng) {
		std::string sendString = std::string(TCHAR_TO_UTF8(*string));
		int sent = send(Sock, sendString.c_str(), leng, 0);
		if(sent != SOCKET_ERROR) {
			//SML::Logging::info("[FIUSATS] - String sent!");
			return true;
		}
		else {
			//SML::Logging::info("[FIUSATS] - String failed to send!");
			return false;
		}
	}
};
