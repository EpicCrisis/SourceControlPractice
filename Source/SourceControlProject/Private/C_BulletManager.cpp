// This project is made by EpicCrisis
#include "C_BulletManager.h"
#include "Components/SceneComponent.h"

AC_BulletManager::AC_BulletManager()
{
	PrimaryActorTick.bCanEverTick = true;

	m_SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("m_SceneComponent"));
	RootComponent = m_SceneComponent;
}

void AC_BulletManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (m_BulletClass)
	{
		for (int32 i = 0; i < m_PooledBullets; ++i)
		{

		}
	}
}

void AC_BulletManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

