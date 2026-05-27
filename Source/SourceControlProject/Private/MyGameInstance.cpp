// This project is made by EpicCrisis
#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init();

	m_PlayerCoins = 0;

	UE_LOG(LogTemp, Warning, TEXT("GameInstance Initialized"));
}

void UMyGameInstance::Shutdown()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Shutdown"));

	Super::Shutdown();
}
