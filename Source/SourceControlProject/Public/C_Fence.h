// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "C_Fence.generated.h"

UCLASS()
class SOURCECONTROLPROJECT_API AC_Fence : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* m_SceneComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* m_FenceMesh = nullptr;

	AC_Fence();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
