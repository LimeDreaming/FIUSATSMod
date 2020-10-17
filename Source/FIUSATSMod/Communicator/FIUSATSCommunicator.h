// ILikeBanas

#include "util/Logging.h"
#include <iostream>
#include <string>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include "IPAddress.h"
#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "Buildables/FGBuildableFactory.h"
#include "FIUSATSCommunicator.generated.h"


#pragma comment(lib, "ws2_32.lib")

/**
 * 
 */
UCLASS()
class FIUSATSMOD_API AFIUSATSCommunicator : public AFGBuildableFactory
{
	GENERATED_BODY()
public:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "RefinedPower|Reactor|ArcReactor")
		void SetUsername(FString username);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FIUSATS")
		bool mUserStatus;

	UPROPERTY(EditDefaultsOnly, SaveGame,BlueprintReadWrite, Category = "FIUSATS")
		FString mUsername;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FIUSATS")
		FString mName;

protected:

	//Ini WinSocket
	bool IniWin();

	//Create Socket
	bool CreateSocket();

	//Create Connection
	void ConnectTCP(FString ip, int port);
	
	void SendStatus();

	void EndConnection();

	FString GetPlayerUserId(AFGPlayerController* playerController);

	UPROPERTY(EditDefaultsOnly, SaveGame, BlueprintReadWrite, Category = "FIUSATS")
		FString mIpAdress;

	UPROPERTY(EditDefaultsOnly, SaveGame, BlueprintReadWrite, Category = "FIUSATS")
		int32 mPort;

	UPROPERTY(EditDefaultsOnly, SaveGame, BlueprintReadWrite, Category = "FIUSATS")
		FString mEpicSteamId;

	UPROPERTY(EditDefaultsOnly, SaveGame, BlueprintReadWrite, Category = "FIUSATS")
		FString mEpicId;

	UPROPERTY(EditDefaultsOnly, SaveGame, BlueprintReadWrite, Category = "FIUSATS")
		FString mSteamId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FIUSATS")
		bool mIsConnected;

};
