// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "C_BulletManager.h"
#include "MyGameInstance.generated.h"

UCLASS()
class SOURCECONTROLPROJECT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	AC_BulletManager* m_BulletManager = nullptr;

	virtual void Init() override;
	virtual void Shutdown() override;

	UPROPERTY(BlueprintReadWrite, Category = "Game")
	int32 m_PlayerCoins = 0;
};
