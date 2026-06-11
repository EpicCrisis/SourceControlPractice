// This project is made by EpicCrisis
#include "C_Wheelchair.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

AC_Wheelchair::AC_Wheelchair()
{
	PrimaryActorTick.bCanEverTick = true;

	m_SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("m_SceneComponent"));
	RootComponent = m_SceneComponent;

	m_WheelchairSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_WheelchairSM"));
	m_WheelchairSM->SetupAttachment(RootComponent);
	m_WheelchairSM->SetCollisionProfileName(FName("NoCollision"));
}

void AC_Wheelchair::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_Wheelchair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

