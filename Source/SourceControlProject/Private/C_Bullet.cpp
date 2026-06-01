// This project is made by EpicCrisis
#include "C_Bullet.h"
#include "Components/SceneComponent.h"

AC_Bullet::AC_Bullet()
{
	PrimaryActorTick.bCanEverTick = true;

	m_SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("m_SceneComponent"));
	RootComponent = m_SceneComponent;
}

void AC_Bullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

