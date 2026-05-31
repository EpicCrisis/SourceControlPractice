// This project is made by EpicCrisis
#include "C_Skyline.h"
#include "Components/BillboardComponent.h"
#include "Components/SceneComponent.h"

AC_Skyline::AC_Skyline()
{
	PrimaryActorTick.bCanEverTick = true;

	m_SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("m_SceneComponent"));
	RootComponent = m_SceneComponent;
	m_SkylineBB = CreateDefaultSubobject<UBillboardComponent>(TEXT("m_SkylineBB"));
	m_SkylineBB->SetupAttachment(m_SceneComponent);
}

void AC_Skyline::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_Skyline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

