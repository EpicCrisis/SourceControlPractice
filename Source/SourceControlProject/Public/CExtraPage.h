// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CExtraPage.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class SOURCECONTROLPROJECT_API UCExtraPage : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ReturnButton = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* GainMoneyButton = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* PlayerMoneyText = nullptr;

	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void CheckPlayerMoney(int32 playerMoney);
	UFUNCTION(BlueprintCallable)
	void OnGainMoneyButtonClicked();
	UFUNCTION(BlueprintCallable)
	void OnReturnButtonClicked();
};
