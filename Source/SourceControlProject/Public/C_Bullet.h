// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BillboardComponent.h"
#include "Components/SphereComponent.h"
#include "C_Bullet.generated.h"

UCLASS()
class SOURCECONTROLPROJECT_API AC_Bullet : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* m_SceneComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBillboardComponent* m_Bullet = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* m_SphereCollider = nullptr;

	AC_Bullet();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
