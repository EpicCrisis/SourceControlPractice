// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/LevelStreamingDynamic.h"
#include "C_StreetManager.generated.h"

UCLASS()
class SOURCECONTROLPROJECT_API AC_StreetManager : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> m_MapRefList;
	UPROPERTY()
	TArray<ULevelStreamingDynamic*> m_LoadedStreetList;
	UPROPERTY()
	int32 m_LoadedStreetIndex = 0;

	AC_StreetManager();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
