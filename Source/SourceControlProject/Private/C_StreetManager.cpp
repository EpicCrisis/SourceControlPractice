// This project is made by EpicCrisis
#include "C_StreetManager.h"
#include "Engine/LevelStreamingDynamic.h"

AC_StreetManager::AC_StreetManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AC_StreetManager::BeginPlay()
{
	Super::BeginPlay();
	
	m_LoadedStreetIndex = 0;
	if (m_MapRefList.Num() > 0)
	{
		for (int32 i = 0; i < m_MapRefList.Num(); ++i)
		{
			bool successMapSpawn = false;
			float yOffset = i * 5000.0f;
			m_LoadedStreetList.Add(
				ULevelStreamingDynamic::LoadLevelInstance(
					GetWorld(),
					m_MapRefList[i],
					FVector(0.0f, yOffset, 0.0f),
					FRotator::ZeroRotator,
					successMapSpawn
				));
			++m_LoadedStreetIndex;
			//we only spawn the first three streets, then load in new streets as the game progresses
			if (i == 3)
			{
				continue;
			}
		}
	}
}

void AC_StreetManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

