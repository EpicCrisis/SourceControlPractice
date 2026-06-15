// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Bullet.generated.h"

class USceneComponent;
class UBillboardComponent;
class USphereComponent;
class AC_BulletManager;

UCLASS()
class SOURCECONTROLPROJECT_API AC_Bullet : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY()
	AC_BulletManager* m_BulletManager = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool m_IsActive = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_LifeTime = 10.0f;
	float m_LifeTimeCounter = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_BulletSpeed = 10.0f;
	UPROPERTY()
	FVector m_FlyingDirection = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_BulletDamage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* m_SceneComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBillboardComponent* m_BulletBB = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* m_SphereCollider = nullptr;

	AC_Bullet();

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
	void ActivateBullet(FVector activeLoc, FVector direction);
	UFUNCTION()
	void DeactivateBullet();
};
