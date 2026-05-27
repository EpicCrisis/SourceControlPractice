// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class SOURCECONTROLPROJECT_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyActor();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
