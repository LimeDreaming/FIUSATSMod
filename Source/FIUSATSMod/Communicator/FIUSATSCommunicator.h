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
//#include "Struct.h"
#include "Buildables/FGBuildableFactory.h"
#include "FIUSATSCommunicator.generated.h"


#pragma comment(lib, "ws2_32.lib")


USTRUCT(BlueprintType)
struct FUserStruct
{
    GENERATED_BODY()
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame, Category = "FIUSATS")
            int ID;
            	
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame, Category = "FIUSATS")
        	FString Username;
        	
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame, Category = "FIUSATS")
            FString UserEpicID;
        	
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame, Category = "FIUSATS")
            FString UserSteamID;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame, Category = "FIUSATS")
            bool IsHoster;
};
 
UCLASS()
class FIUSATSMOD_API AFIUSATSCommunicator : public AFGBuildableFactory
{
	GENERATED_BODY()
public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
	
	UPROPERTY(EditDefaultsOnly, SaveGame, BlueprintReadWrite, Category = "FIUSATS")
    	    TArray<FString> Usernames;
	
	UPROPERTY(EditDefaultsOnly, SaveGame, BlueprintReadWrite, Category = "FIUSATS")
	    TArray<FUserStruct> UserStruct;
	    
	UPROPERTY(EditDefaultsOnly, SaveGame, BlueprintReadWrite, Category = "FIUSATS")
    	    FUserStruct UserStructN;

	UFUNCTION(BlueprintCallable, Category = "FIUSATS")
		void SetUsername(FString username);
		
	//Server Functions
	
	UFUNCTION(Server, WithValidation, Unreliable, BlueprintCallable)
    	void Server_TCPConnection();
    
    UFUNCTION(Server, WithValidation, Unreliable, BlueprintCallable)
        void Server_DestroyConnection();
	
	UFUNCTION(Server, WithValidation, Unreliable, BlueprintCallable)
	    void Server_CreateUserStruct();
	
	//End Server Functions    
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FIUSATS")
		bool mUserStatus;

	UPROPERTY(EditDefaultsOnly, SaveGame,BlueprintReadWrite, Category = "FIUSATS")
		FString mUsername;

	UPROPERTY(EditDefaultsOnly, SaveGame, BlueprintReadWrite, Category = "FIUSATS")
		FString mLocalUsername;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FIUSATS")
    	FString mTest;
    		
protected:

	//Ini WinSocket
	bool IniWin();
	
	//Create Socket
	bool CreateSocket();

	//Create Connection
	void ConnectTCP(FString ip, int port);
	
	void SendStatus(AFGPlayerController* player);

	void EndConnection();

	FString GetPlayerUserId(AFGPlayerController* playerController);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FIUSATS")
    AFGPlayerController* mPlayerFGController;
    
	UPROPERTY(EditDefaultsOnly, SaveGame, BlueprintReadWrite, Category = "FIUSATS")
		FString mIpAdress;

	UPROPERTY(EditDefaultsOnly, SaveGame, BlueprintReadWrite, Category = "FIUSATS")
		int32 mPort;

	UPROPERTY(EditDefaultsOnly, SaveGame, BlueprintReadWrite, Category = "FIUSATS")
		FString mEpicSteamId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FIUSATS")
		FString mEpicId;

	UPROPERTY(EditDefaultsOnly, SaveGame, BlueprintReadWrite, Category = "FIUSATS")
		FString mSteamId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FIUSATS")
		bool mIsConnected;

};
