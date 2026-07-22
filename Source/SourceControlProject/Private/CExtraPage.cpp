// This project is made by EpicCrisis
#include "CExtraPage.h"
#include "MyGameStateBase.h"
#include "Components/Button.h"
#include "MyGameInstance.h"
#include "Components/TextBlock.h"

void UCExtraPage::NativeConstruct()
{
	ReturnButton->OnClicked.AddDynamic(this, &UCExtraPage::OnReturnButtonClicked);
	GainMoneyButton->OnClicked.AddDynamic(this, &UCExtraPage::OnGainMoneyButtonClicked);
}

void UCExtraPage::CheckPlayerMoney(int32 playerMoney)
{
	//m_GameInstance = GetGameInstance<UMyGameInstance>();

	FText newText = FText::Format(FText::FromString(TEXT("${0}")), FText::AsNumber(playerMoney));
	PlayerMoneyText->SetText(newText);
}

void UCExtraPage::OnGainMoneyButtonClicked()
{
	if (AMyGameStateBase* tempGS = GetWorld()->GetGameState<AMyGameStateBase>())
	{
		tempGS->AddMoreMoney(1);
	}
}

void UCExtraPage::OnReturnButtonClicked()
{
	if (AMyGameStateBase* tempGS = GetWorld()->GetGameState<AMyGameStateBase>())
	{
		tempGS->ShowMainScreen();
	}
}
