// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_MovementManager.generated.h"

UCLASS()
class SOURCECONTROLPROJECT_API AC_MovementManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_MovementManager();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
