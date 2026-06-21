// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CMainMenu.generated.h"

class UButton;

UCLASS()
class SOURCECONTROLPROJECT_API UCMainMenu : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* StartButton = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* QuitButton = nullptr;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnStartButtonClicked();
	UFUNCTION()
	void OnQuitButtonClicked();
};
