// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CGameOver.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class SOURCECONTROLPROJECT_API UCGameOver : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* RestartButton = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* QuitButton = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* WinLoseText = nullptr;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetGameOverMessage(bool isWin);

	UFUNCTION()
	void OnRestartButtonClicked();
	UFUNCTION()
	void OnQuitButtonClicked();
};
