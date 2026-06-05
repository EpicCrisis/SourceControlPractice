// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_EnemyManager.generated.h"

class UMyGameInstance;
class AC_Enemy;
class AMyCharacter;

UCLASS()
class SOURCECONTROLPROJECT_API AC_EnemyManager : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_SpawnInterval = 3.0f;
	UPROPERTY()
	float m_SpawnRand = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AC_Enemy> m_EnemyClass = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AC_Enemy* m_CurrentEnemy = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMyCharacter* m_CurrentPlayer = nullptr; //spawn the enemy relative to player location

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* m_SceneComponent = nullptr;
	UPROPERTY()
	UMyGameInstance* m_GameInstance = nullptr;
	
	UPROPERTY()
	FVector m_SpawnLocation = FVector::ZeroVector;

	AC_EnemyManager();

	UFUNCTION()
	void SpawnEnemyAt(FVector spawnLoc);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
