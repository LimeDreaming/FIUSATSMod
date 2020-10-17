// ILikeBanas

#include "util/Logging.h"
#include <iostream>
#include <string>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include "IPAddress.h"
//#include "Sockets.h"
#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "GameFramework/Actor.h"
#include "FIUSATSActor.generated.h"

//#ifndef FIUSATSACTOR_H
//#define FIUSATSACTOR_H

struct STGetData {
	FString *string;
	int32 *leng;
	FString *data;
};

UCLASS()
class FIUSATSMOD_API AFIUSATSActor : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFIUSATSActor();

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "IniWin FIUSATS Server"), Category = FIUSATSMod, meta = (Keywords = "iniWin FIUSATS tcp server"))
		static bool IniWin();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Connect to FIUSATS Server"), Category = FIUSATSMod, meta = (Keywords = "connection FIUSATS tcp server"))
		static bool ConnectTCP(FString ip, int port, int &output);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create TCP Socket"), Category = FIUSATSMod, meta = (Keywords = "socket FIUSATS tcp server"))
		static void CreateSocket(bool &result);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MultiSend to FIUSATS Server"), Category = FIUSATSMod, meta = (Keywords = "send FIUSATS tcp server"))
		static void MultiSending(FString string, int32 leng, FString &data);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Send to FIUSATS Server"), Category = FIUSATSMod, meta = (Keywords = "send FIUSATS tcp server"))
		static bool Sending(FString string, int32 leng);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetData from FIUSATS Server"), Category = FIUSATSMod, meta = (Keywords = "getdata FIUSATS tcp server"))
		static void GetData(FString string, int32 leng, FString &data);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Disconnect from FIUSATS Server"), Category = FIUSATSMod, meta = (Keywords = "disconnect FIUSATS tcp server"))
		static void Disconnect();
};


//#endif // !FIUSATSACTOR_H

