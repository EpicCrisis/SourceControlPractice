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
class UC_Shake;
class UNiagaraSystem;
class UCSecondHud;

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
	TObjectPtr <UNiagaraSystem> m_ExplodeVFX = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCSecondHud* m_NewPlayerHud = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_SpawnIdleTime = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_SpawnCounter = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_InitialScale = 1.2f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_DeathTime = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_DeathCounter = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool m_IsActive = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_MaxHealth = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_CurrentHealth = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_AttackDamage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector m_AttackLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* m_SceneComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBillboardComponent* m_EnemyBB = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBillboardComponent* m_KillBB = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* m_SphereCollider = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UC_Shake* m_ShakeComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* m_Normal = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* m_DamageFlash = nullptr;

	UPROPERTY()
	FTimerHandle DamageFlashTimer;

	//UPROPERTY()
	//FTimerHandle ShakeTimerHandle;

	//UPROPERTY()
	//FVector m_OriginalLoc = FVector::ZeroVector;

	//UPROPERTY()
	//float m_ShakeElapsed = 0.0f;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float m_ShakeDuration = 0.25f;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float m_ShakeIntensity = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_CrossShakeDuration = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_CrossShakeIntensity = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_DamageShakeDuration = 0.25f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_DamageShakeIntensity = 20.0f;

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
	void HandleChase(float deltaTime);
	UFUNCTION()
	void HandleDeath(float deltaTime);

	UFUNCTION()
	void StartDamageFlash();
	UFUNCTION()
	void EndDamageFlash();

	//UFUNCTION()
	//void StartDamageShake(UBillboardComponent* BBComp);
	//UFUNCTION()
	//void UpdateDamageShake(UBillboardComponent* BBComp);
	//UFUNCTION()
	//void EndDamageShake(UBillboardComponent* BBComp);

	UFUNCTION()
	void ExplodeThenDisappear();
	UFUNCTION()
	void DeactivateEnemy();

	UFUNCTION()
	void SetEnemyState(E_EnemyState state);
};
