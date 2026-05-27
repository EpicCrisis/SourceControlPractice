// This project is made by EpicCrisis
#include "MySplinePath.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"
#include "MySplineComponent.h"

AMySplinePath::AMySplinePath()
{
	m_SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("m_SceneComponent"));
	RootComponent = m_SceneComponent;
	m_PathingSpline = CreateDefaultSubobject<UMySplineComponent>(TEXT("m_NewPathSpline"));
	m_PathingSpline->SetupAttachment(m_SceneComponent);
}

void AMySplinePath::BeginPlay()
{
}

void AMySplinePath::Tick(float DeltaTime)
{
}
