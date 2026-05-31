// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BillboardComponent.h"
#include "Components/SceneComponent.h"
#include "C_Skyline.generated.h"

UCLASS()
class SOURCECONTROLPROJECT_API AC_Skyline : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* m_SceneComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBillboardComponent* m_SkylineBB = nullptr;

	AC_Skyline();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
