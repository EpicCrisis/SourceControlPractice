// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_Shake.generated.h"

class UBillboardComponent;

USTRUCT()
struct FShakeTarget
{
	GENERATED_BODY()

	UPROPERTY()
	UBillboardComponent* BBComp = nullptr;

	UPROPERTY()
	FVector OriginalLoc = FVector::ZeroVector;

	UPROPERTY()
	float ElapsedTime = 0.0f;
	UPROPERTY()
	float Duration = 0.25f;
	UPROPERTY()
	float Intensity = 20.0f;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOURCECONTROLPROJECT_API UC_Shake : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<FShakeTarget> m_ShakeList;

	UPROPERTY()
	FTimerHandle m_TimerHandle;

	UC_Shake();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void StartShake(UBillboardComponent* BBComp, float duration = 0.25f, float intensity = 20.0f);
	UFUNCTION()
	void UpdateShake();
	UFUNCTION()
	void EndShake();
};