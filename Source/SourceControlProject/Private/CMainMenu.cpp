// This project is made by EpicCrisis
#include "CMainMenu.h"
#include "Components/Button.h"
#include "MyGameStateBase.h"

void UCMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	StartButton->OnClicked.AddDynamic(this, &UCMainMenu::OnStartButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UCMainMenu::OnQuitButtonClicked);
}

void UCMainMenu::OnStartButtonClicked()
{
	if (AMyGameStateBase* tempGS = GetWorld()->GetGameState<AMyGameStateBase>())
	{
		tempGS->StartGameNow(this);
	}
}

void UCMainMenu::OnQuitButtonClicked()
{
	if (AMyGameStateBase* tempGS = GetWorld()->GetGameState<AMyGameStateBase>())
	{
		tempGS->QuitGameNow();
	}
}