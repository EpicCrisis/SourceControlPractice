// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Wheelchair.generated.h"

class UStaticMeshComponent;
class USceneComponent;

UCLASS()
class SOURCECONTROLPROJECT_API AC_Wheelchair : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* m_SceneComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* m_WheelchairSM = nullptr;

	AC_Wheelchair();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
