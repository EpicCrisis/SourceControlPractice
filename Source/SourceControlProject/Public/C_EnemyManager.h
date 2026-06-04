// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_EnemyManager.generated.h"

UCLASS()
class SOURCECONTROLPROJECT_API AC_EnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	FVector m_SpawnLocation = FVector::ZeroVector;

	AC_EnemyManager();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
