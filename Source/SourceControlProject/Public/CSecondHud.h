// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSecondHud.generated.h"

class UTextBlock;

UCLASS()
class SOURCECONTROLPROJECT_API UCSecondHud : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_HealthText = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_DistanceText = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_BulletText = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_EnemyText = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_MoneyText = nullptr;

	UFUNCTION(BlueprintCallable)
	void SetHealthText(int32 health);
	UFUNCTION(BlueprintCallable)
	void SetDistanceText(float distance);
	UFUNCTION(BlueprintCallable)
	void SetBulletText(int32 bullet);
	UFUNCTION(BlueprintCallable)
	void SetEnemyText(int32 enemy);
	UFUNCTION(BlueprintCallable)
	void SetMoneyText(int32 money);
};
