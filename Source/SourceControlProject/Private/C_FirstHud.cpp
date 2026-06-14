// This project is made by EpicCrisis
#include "C_FirstHud.h"
#include "Components/TextBlock.h"

void UC_FirstHud::SetHealthText(const FString& newMessage)
{
	m_HealthText->SetText(FText::FromString(newMessage));
}
