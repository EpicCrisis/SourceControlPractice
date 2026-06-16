// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPlaneFloor.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class SOURCECONTROLPROJECT_API ACPlaneFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* m_SceneComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* m_FloorMesh = nullptr;

	ACPlaneFloor();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
