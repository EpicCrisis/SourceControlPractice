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
	void SetHealthText(const FText& newMessage);
	UFUNCTION(BlueprintCallable)
	void SetDistanceText(const FText& newMessage);
	UFUNCTION(BlueprintCallable)
	void SetBulletText(const FText& newMessage);
	UFUNCTION(BlueprintCallable)
	void SetEnemyText(const FText& newMessage);
	UFUNCTION(BlueprintCallable)
	void SetMoneyText(int32 money);
};
