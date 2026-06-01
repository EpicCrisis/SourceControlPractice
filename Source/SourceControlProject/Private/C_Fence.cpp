// This project is made by EpicCrisis
#include "C_Fence.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

AC_Fence::AC_Fence()
{
	PrimaryActorTick.bCanEverTick = true;

	m_SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("m_SceneComponent"));
	RootComponent = m_SceneComponent;
	m_FenceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_FenceMesh"));
	m_FenceMesh->SetupAttachment(m_SceneComponent);
}

void AC_Fence::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_Fence::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

