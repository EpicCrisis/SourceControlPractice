// This project is made by EpicCrisis
#include "C_BuildingBlock.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

AC_BuildingBlock::AC_BuildingBlock()
{
	PrimaryActorTick.bCanEverTick = true;
	
	m_SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("m_SceneComponent"));
	RootComponent = m_SceneComponent;
	m_BuildingCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_BuildingCube"));
	//m_BuildingCube->SetupAttachment(m_SceneComponent);
	m_BuildingCube->AttachToComponent(m_SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AC_BuildingBlock::BeginPlay()
{
	Super::BeginPlay();
	
	RandomizeBuildingMaterial();

	int32 currentZScale = GetActorScale3D().Z;
	float randIndex = FMath::FRandRange(0.3f, 1.7f);
	float newScale = currentZScale * randIndex;
	FVector currentScale = GetActorScale3D();
	currentScale.Z = newScale;
	SetActorScale3D(currentScale);
}

void AC_BuildingBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_BuildingBlock::RandomizeBuildingMaterial()
{
	if (m_MaterialList.Num() == 0) 
	{
		return;
	}

	int32 randIndex = FMath::RandRange(0, m_MaterialList.Num() - 1);

	if (m_BuildingCube)
	{
		m_BuildingCube->SetMaterial(0, m_MaterialList[randIndex]);
	}
}

