// This project is made by EpicCrisis
#include "CSecondHud.h"
#include "Components/TextBlock.h"

void UCSecondHud::SetHealthText(int32 health)
{
	FText newText = FText::Format(FText::FromString(TEXT("HEALTH : {0}")), FText::AsNumber(health));
	m_HealthText->SetText(newText);
}

void UCSecondHud::SetDistanceText(float distance)
{
	FNumberFormattingOptions tempOption;
	tempOption.SetMaximumFractionalDigits(1);
	tempOption.SetMinimumFractionalDigits(1);

	FText newText = FText::Format(
		FText::FromString(TEXT("DISTANCE : {0}")),
		FText::AsNumber(distance, &tempOption)
	);

	m_DistanceText->SetText(newText);
}

void UCSecondHud::SetBulletText(int32 bullet)
{
	FText newText = FText::Format(FText::FromString(TEXT("BULLET : {0}")), FText::AsNumber(bullet));
	m_BulletText->SetText(newText);
}

void UCSecondHud::SetEnemyText(int32 enemy)
{
	FText newText = FText::Format(FText::FromString(TEXT("ENEMY : {0}")), FText::AsNumber(enemy));
	m_EnemyText->SetText(newText);
}

void UCSecondHud::SetMoneyText(int32 money)
{
	FText newText = FText::Format(FText::FromString(TEXT("MONEY : {0}")), FText::AsNumber(money));
	m_MoneyText->SetText(newText);
}


