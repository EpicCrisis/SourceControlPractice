// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/LevelStreamingDynamic.h"
#include "C_StreetManager.generated.h"

class AMyGameStateBase;

UCLASS()
class SOURCECONTROLPROJECT_API AC_StreetManager : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> m_MapRefList;
	UPROPERTY()
	TArray<ULevelStreamingDynamic*> m_LoadedStreetList;
	//UPROPERTY()
	//TArray<AActor*> m_LoadedStreetListB;
	UPROPERTY()
	int32 m_LoadedStreetIndex = 0;

	UPROPERTY()
	AMyGameStateBase* m_GameState = nullptr;

	UPROPERTY()
	float m_MoveSpeed = 10.0f;
	UPROPERTY()
	float m_MoveDistance = 0.0f;

	AC_StreetManager();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void OnLevelReady();
};
