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
	m_BuildingCube->SetupAttachment(m_SceneComponent);
	//m_BuildingCube->AttachToComponent(m_SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AC_BuildingBlock::BeginPlay()
{
	Super::BeginPlay();
	
	RandomizeBuildingMaterial();

	float randScale = FMath::FRandRange(3.0f, 20.0f);
	FVector currentScale = GetActorScale3D();
	currentScale.Z = 1.0f;
	SetActorScale3D(currentScale);

	m_TargetHeight = randScale;
}

void AC_BuildingBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector currentScale = GetActorScale3D();
	//if (currentScale.Z > m_TargetHeight)
	//{
	//	currentScale.Z -= 60.0f * DeltaTime;
	//}
	//else if(currentScale.Z < m_TargetHeight)
	//{
	//	currentScale.Z += 60.0f * DeltaTime;
	//}

	if (!FMath::IsNearlyEqual(currentScale.Z, m_TargetHeight, 0.1f))
	{
		SetActorScale3D(FVector(currentScale.X, currentScale.Y, FMath::FInterpTo(currentScale.Z, m_TargetHeight, DeltaTime, 3.0f)));
	}
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

