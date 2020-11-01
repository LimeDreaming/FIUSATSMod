// ILikeBanas

#include "FIUSATSCommunicator.h"
#include "util/Logging.h"
#include <iostream>
#include <future>
#include <string>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <future>
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h" 
#include "FGLocalPlayer.h"


#pragma comment(lib, "ws2_32.lib")
SOCKET sock;
using namespace std;

//Create UserStruct
void AFIUSATSCommunicator::Server_CreateUserStruct_Implementation (){
    UserStruct.Empty();
    for (int i = 0; i< 4; i++){
        APlayerController *tempPc = UGameplayStatics::GetPlayerController(GetWorld(), i);
        AFGPlayerController* player = Cast<AFGPlayerController>(tempPc);
        
        if(player)
            {
                UserStructN.ID = i;
                UserStructN.Username = player->GetPlayerState<APlayerState>()->GetPlayerName();
                UserStructN.UserEpicID = mEpicId;
                UserStructN.UserSteamID = mSteamId;
                if(i == 0){ UserStructN.IsHoster = true; }
                else{ UserStructN.IsHoster = false; }
                UserStruct.Add(UserStructN);
            }
        }
    
}

bool AFIUSATSCommunicator::Server_CreateUserStruct_Validate() {

    return true;
    
}
//End Create UserStruct

void AFIUSATSCommunicator::BeginPlay() {
    
	Super::BeginPlay();
    //Usernames.Add(TEXT("Test"));
    //Usernames.Add(TEXT("Test1"));
	
	
	//APlayerState* pcstate = Cast<APlayerState>(pc);
	APlayerController *tempPc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    mPlayerFGController = Cast<AFGPlayerController>(tempPc);
	
	mLocalUsername = mPlayerFGController->GetPlayerState<APlayerState>()->GetPlayerName();
	
	mEpicSteamId = GetPlayerUserId(mPlayerFGController);
	//if(mLocalUsername == "") {mLocalUsername = }
	
	 if (IniWin()) {
            if (CreateSocket()) {
                ConnectTCP(mIpAdress, mPort);
                if(mIsConnected == true) {
                    SendStatus(mPlayerFGController);
                }
                }
            }
    
	//Server_TCPConnection();
    
}
	
void AFIUSATSCommunicator::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    Server_CreateUserStruct();
    //UserStruct.Empty();
    //for (int i = 0; i< 4; i++){
    
    //    APlayerController *tempPc = UGameplayStatics::GetPlayerController(GetWorld(), i);
    //    AFGPlayerController* pc = Cast<AFGPlayerController>(tempPc);
    //    Server_CreateUserStruct(pc);
    //}
    
}

void AFIUSATSCommunicator::EndPlay(const EEndPlayReason::Type endPlayReason) {
	if (endPlayReason == EEndPlayReason::Destroyed || EEndPlayReason::Quit) {
		mIsConnected = false;
		EndConnection();
	}
	Super::EndPlay(endPlayReason);
}

bool AFIUSATSCommunicator::IniWin() {

	int iResult;

	WSAData wsData;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsData);
	if (iResult != 0) {
		return false;
		SML::Logging::info("[FIUSATS] - Creating WinSock failed - : " + WSAGetLastError());
	}
	else {
		return true;
		SML::Logging::info("[FIUSATS] - WinSock is created! -");
	}
}

bool AFIUSATSCommunicator::CreateSocket() {
	if (sock != INVALID_SOCKET) {
		return true;
		SML::Logging::info("[FIUSATS] - Socket is created! -");
	}
	else {
		return false;
		SML::Logging::info("[FIUSATS] - Creating socket failed! - : " + WSAGetLastError());
	}
}

void AFIUSATSCommunicator::ConnectTCP(FString ip, int port) {

	sock = socket(AF_INET, SOCK_STREAM, 0);
	bool Connect(const FInternetAddr & ip);
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	std::string w(TCHAR_TO_UTF8(*ip));
	inet_pton(AF_INET, w.c_str(), &hint.sin_addr);

	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR) {
		closesocket(sock);
		WSACleanup();
		mIsConnected = false;
		SML::Logging::info("[FIUSATS] - Connection to Server failed! -");
	}
	else {
		mIsConnected = true;
		SML::Logging::info("[FIUSATS] - Connected to Server -");
	}
}

void AFIUSATSCommunicator::EndConnection() {
	SendStatus(mPlayerFGController);
	closesocket(sock);
	WSACleanup();
}

//Server Events

//Create Connection

void AFIUSATSCommunicator::Server_TCPConnection_Implementation() {
    if (IniWin()) {
        if (CreateSocket()) {
            ConnectTCP(mIpAdress, mPort);
            }
        }
    SendStatus(mPlayerFGController);
}

bool AFIUSATSCommunicator::Server_TCPConnection_Validate() {return true;}
//End Create Connection

//Destroy Connection

void AFIUSATSCommunicator::Server_DestroyConnection_Implementation() {
    if(UserStruct[0].IsHoster == true){ EndConnection(); }
}

bool AFIUSATSCommunicator::Server_DestroyConnection_Validate() {return true;}
//End Destroy Connection



void AFIUSATSCommunicator::SendStatus(AFGPlayerController* player) {
    
	std::string sendString;
	if (mUsername != "") {
		if (mUserStatus) {
			sendString.append("0;");
		}
		else {
			sendString.append("1;");
		}
		string localUsername = std::string(TCHAR_TO_UTF8(*mLocalUsername));
		string localUserLength = to_string(sizeof(localUsername));
	    sendString.append(localUsername);
	    sendString.append(";");
	    
		int sent = send(sock, sendString.c_str(), sizeof(sendString), 0);
		if (sent != SOCKET_ERROR) {
			SML::Logging::info("[FIUSATS] - User is now Online");
			mUserStatus = true;
		}
		else {
			SML::Logging::error("[FIUSATS] - Status for User can't set to Online! -");
			mUserStatus = false;
		}
	}
}

void AFIUSATSCommunicator::SetUsername(FString username) {
	mUsername = username;
}

FString AFIUSATSCommunicator::GetPlayerUserId(AFGPlayerController* playerController) {

	FString IDToUseStr;
	
	
	if (playerController) {
		UFGLocalPlayer* player = Cast<UFGLocalPlayer>(playerController->GetLocalPlayer());

		if (player) {
			TSharedPtr<const FUniqueNetId> EpicID = player->GetPlayerId();
			TSharedPtr<const FUniqueNetId> SteamID = player->GetPlayerIdSteam();

			//TSharedPtr<const FUniqueNetId> IDToUse = (EpicID) ? EpicID : SteamID;

			if (EpicID && SteamID || EpicID || SteamID) {
				if (EpicID && SteamID) {
					std::string Epic = std::string(TCHAR_TO_UTF8(*EpicID->ToString()));
					std::string REpicID = Epic.substr(0, 32);
					mEpicId = UTF8_TO_TCHAR(REpicID.c_str());
					mSteamId = SteamID->ToString();
				}
				if (EpicID && !SteamID) {
					std::string Epic = std::string(TCHAR_TO_UTF8(*EpicID->ToString()));
					std::string REpicID = Epic.substr(0, 32);
					mEpicId = UTF8_TO_TCHAR(REpicID.c_str());
					std::string Steam = "Undefined";
					mSteamId = UTF8_TO_TCHAR(Steam.c_str());
				}
				if (SteamID && !EpicID) {
					std::string REpicID = "Undefined";
					mEpicId = UTF8_TO_TCHAR(REpicID.c_str());
					mSteamId = SteamID->ToString();
				}
				
			}
            else
            {
                std::string REpicID = "Offline";
                mEpicId = UTF8_TO_TCHAR(REpicID.c_str());
                std::string Steam = "Offline";
                mSteamId = UTF8_TO_TCHAR(Steam.c_str());
            }
			//IDToUseStr = IDToUse->ToString();

		}
	}
	else {
		// Testing stuff
		//IDToUseStr = "123456789";
	}
	
	return IDToUseStr;
}

