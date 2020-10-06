// ILikeBanas

#include "FIUSATSActor.h"
#include "util/Logging.h"
#include <iostream>
#include <future>
#include <string>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
//#include "player/PlayerUtility.h"
#include "Socket.h"

#pragma comment(lib, "ws2_32.lib")
SOCKET sock;
using namespace std;

Socket factory;
// Sets default values
AFIUSATSActor::AFIUSATSActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AFIUSATSActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFIUSATSActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AFIUSATSActor::IniWin() 
{
	int iResult;

	WSAData wsData;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsData);
	if (iResult != 0) {

		return false;
	}
	else {
		return true;
	}
	
	/*bool iniWin = factory.IniWin();
	
	return iniWin;*/
}

bool AFIUSATSActor::ConnectTCP(FString ip, int port, int &output) {
	output = 20;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	bool Connect(const FInternetAddr & ip);
	//string ipAdress = "192.168.178.53";
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	std::string w(TCHAR_TO_UTF8(*ip));
	inet_pton(AF_INET, w.c_str(), &hint.sin_addr);

	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR) {
		closesocket(sock);
		WSACleanup();

		//SML::Logging::info("[FIUSATS] - Can't connect to: ");
		return false;
	}
	else {
		return true;
		//SML::Logging::info("[FIUSATS] - Connect to: ");
		//auto asyncstart = std::async(std::launch::async, __SocketStart__);
	}
}

void AFIUSATSActor::CreateSocket(bool &result) {
	if (sock != INVALID_SOCKET) {
		result = true;
	}
	else {
		result = false;
	}
}

bool AFIUSATSActor::Sending(FString string, int32 leng) {
	std::string sendString = std::string(TCHAR_TO_UTF8(*string));
	int sent = send(sock, sendString.c_str(), leng, 0);
	if (sent != SOCKET_ERROR) {
		//SML::Logging::info("[FIUSATS] - String sent!");
		return true;
	}
	else {
		//SML::Logging::info("[FIUSATS] - String failed to send!");
		return false;
	}
}

void  AFIUSATSActor::GetData(FString string, int32 leng, FString &data) {
	char buf[100];
	bool sent = Sending(string, leng);
	if (sent == true) {
		int result = recv(sock, buf, sizeof(buf), 0);
		data = std::string(buf, 0, result).c_str();
	}
}

void AFIUSATSActor::Disconnect() {
	closesocket(sock);
	if (sock) {
		//SML::Logging::info("[FIUSATS] - Socket is still there");
	}
	else {
		//SML::Logging::info("[FIUSATS] - Socket is not there");
	}
	sock = 0;
	WSACleanup();
}

