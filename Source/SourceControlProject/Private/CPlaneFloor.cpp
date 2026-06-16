// This project is made by EpicCrisis
#include "CPlaneFloor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

ACPlaneFloor::ACPlaneFloor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	m_SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("m_SceneComponent"));
	RootComponent = m_SceneComponent;
	m_FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_FloorMesh"));
	m_FloorMesh->SetupAttachment(m_SceneComponent);
	m_FloorMesh->SetCollisionProfileName("BlockAll");
}

void ACPlaneFloor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPlaneFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

