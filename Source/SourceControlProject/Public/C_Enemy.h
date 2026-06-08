// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Enemy.generated.h"

class USceneComponent;
class UBillboardComponent;
class USphereComponent;
class UTexture;
class AMyCharacter;

UENUM(BlueprintType)
enum class E_EnemyState : uint8
{
	Spawn		UMETA(DisplayName = "Spawn"),
	Chase		UMETA(DisplayName = "Chase"),
	Die			UMETA(DisplayName = "Die")
};

UCLASS()
class SOURCECONTROLPROJECT_API AC_Enemy : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_EnemyState m_EnemyState = E_EnemyState::Spawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMyCharacter* m_PlayerChar = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_SpawnIdleTime = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_SpawnCounter = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_InitialScale = 1.2f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_TargetScale = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_CurrentScale = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool m_IsActive = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_MaxHealth = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_CurrentHealth = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* m_SceneComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBillboardComponent* m_EnemyBB = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* m_SphereCollider = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* m_Normal = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* m_DamageFlash = nullptr;

	UPROPERTY()
	FTimerHandle DamageFlashTimer;

	AC_Enemy();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UFUNCTION()
	void SpawnThisEnemy(FVector spawnLoc);

	UFUNCTION()
	void HandleSpawn(float deltaTime);
	UFUNCTION()
	void HandleChase();
	UFUNCTION()
	void HandleDeath();

	UFUNCTION()
	void StartDamageFlash();
	UFUNCTION()
	void EndDamageFlash();

	UFUNCTION()
	void DeactivateEnemy();

	UFUNCTION()
	void SetEnemyState(E_EnemyState state);
};
