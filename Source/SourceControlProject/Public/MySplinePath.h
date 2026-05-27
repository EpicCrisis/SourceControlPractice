// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "MySplinePath.generated.h"

UCLASS()
class SOURCECONTROLPROJECT_API AMySplinePath : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* m_SceneComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent* m_PathingSpline = nullptr;

	AMySplinePath();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
