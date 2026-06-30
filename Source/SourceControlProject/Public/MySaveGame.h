// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

UCLASS()
class SOURCECONTROLPROJECT_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_PlayerMoney = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_BulletUpgrade = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_HealthUpgrade = 0;
};
