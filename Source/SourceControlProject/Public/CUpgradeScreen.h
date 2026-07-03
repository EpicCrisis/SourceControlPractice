// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUpgradeScreen.generated.h"

class UButton;
class UTextBlock;
class UMyGameInstance;

UCLASS()
class SOURCECONTROLPROJECT_API UCUpgradeScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ReturnButton = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* MaxBulletUpgradeButton = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* MaxHealthUpgradeButton = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* PlayerMoneyText = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* TimesBulletText = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* TimesHealthText = nullptr;

	UPROPERTY()
	UMyGameInstance* m_GameInstance = nullptr;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void CheckPlayerMoney(int32 playerMoney);
	UFUNCTION(BlueprintCallable)
	void OnReturnButtonClicked();
	UFUNCTION(BlueprintCallable)
	void OnMaxBulletUpgradeClicked();
	UFUNCTION(BlueprintCallable)
	void OnMaxHealthUpgradeClicked();
	UFUNCTION()
	void UpdateTimesBullet(int32 number);
	UFUNCTION()
	void UpdateTimesHealth(int32 number);
};
