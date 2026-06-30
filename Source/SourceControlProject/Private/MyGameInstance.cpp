// This project is made by EpicCrisis
#include "MyGameInstance.h"
#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"

void UMyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("GameInstance Initialized"));
}

void UMyGameInstance::Shutdown()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Shutdown"));

	Super::Shutdown();
}

void UMyGameInstance::SaveUpgrade()
{
	SaveSlotName = FString("SaveGameZero");
	UserIndex = 0;

	UMySaveGame* SaveGame = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));

	SaveGame->m_PlayerMoney = m_PlayerMoney;
	SaveGame->m_BulletUpgrade = m_BulletUpgradeLevel;
	SaveGame->m_HealthUpgrade = m_HealthUpgradeLevel;

	UGameplayStatics::SaveGameToSlot(SaveGame, SaveSlotName, UserIndex);
}
