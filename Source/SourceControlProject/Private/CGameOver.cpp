// This project is made by EpicCrisis
#include "CGameOver.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MyGameStateBase.h"

void UCGameOver::NativeConstruct()
{
	Super::NativeConstruct();

	RestartButton->OnClicked.AddDynamic(this, &UCGameOver::OnRestartButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UCGameOver::OnQuitButtonClicked);
}

void UCGameOver::SetGameOverMessage(bool isWin)
{
	if (isWin)
	{
		FText newText = FText::FromString(TEXT("YOU SURVIVED THE"));
		WinLoseText->SetText(newText);
	}
	else
	{
		FText newText = FText::FromString(TEXT("YOU DIED TO"));
		WinLoseText->SetText(newText);
	}
}

void UCGameOver::OnRestartButtonClicked()
{
	if (AMyGameStateBase* tempGS = GetWorld()->GetGameState<AMyGameStateBase>())
	{
		tempGS->RestartMap();
	}
}

void UCGameOver::OnQuitButtonClicked()
{
	if (AMyGameStateBase* tempGS = GetWorld()->GetGameState<AMyGameStateBase>())
	{
		tempGS->QuitGameNow();
	}
}