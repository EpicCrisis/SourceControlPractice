// This project is made by EpicCrisis
#include "C_Shake.h"
#include "Components/BillboardComponent.h"

UC_Shake::UC_Shake()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UC_Shake::BeginPlay()
{
	Super::BeginPlay();

}


void UC_Shake::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UC_Shake::StartShake(UBillboardComponent* BBComp, float duration, float intensity)
{
	if (BBComp == nullptr)
	{
		return;
	}

	FShakeTarget newShake = FShakeTarget();

	newShake.ElapsedTime = 0.0f;
	newShake.BBComp = BBComp;
	newShake.Duration = duration;
	newShake.Intensity = intensity;
	newShake.OriginalLoc = BBComp->GetComponentLocation();

	//FTimerDelegate timerDel;
	//timerDel.BindUFunction(this, FName("UpdateShake"), m_CurrentBB);

	m_ShakeList.Add(newShake);

	GetWorld()->GetTimerManager().SetTimer(
		m_TimerHandle,
		this,
		&UC_Shake::UpdateShake,
		0.01f,
		true
	);
}

void UC_Shake::UpdateShake()
{
	for (int32 i = 0; i < m_ShakeList.Num(); ++i)
	{
		if (!IsValid(m_ShakeList[i].BBComp))
		{
			continue;
		}

		m_ShakeList[i].ElapsedTime += 0.01f;

		float alpha = m_ShakeList[i].ElapsedTime / m_ShakeList[i].Duration;
		float currentIntensity = m_ShakeList[i].Intensity * (1.0f - alpha);

		FVector randomOffset = FVector(
			FMath::FRandRange(-1.0f, 1.0f),
			FMath::FRandRange(-1.0f, 1.0f),
			FMath::FRandRange(-1.0f, 1.0f)
		) * currentIntensity;

		m_ShakeList[i].BBComp->SetWorldLocation(m_ShakeList[i].OriginalLoc + randomOffset);
		
		if (m_ShakeList[i].ElapsedTime >= m_ShakeList[i].Duration)
		{
			m_ShakeList.RemoveAt(i);
			//EndShake();
		}
	}

	//m_ShakeElapsed += 0.01f;
	//
	//float alpha = m_ShakeElapsed / m_ShakeDuration;
	//
	//// fade-out
	//float currentIntensity = m_ShakeIntensity * (1.0f - alpha);
	//
	//FVector randomOffset = FVector(
	//	FMath::FRandRange(-1.0f, 1.0f),
	//	FMath::FRandRange(-1.0f, 1.0f),
	//	FMath::FRandRange(-1.0f, 1.0f)
	//) * currentIntensity;
	//
	//m_CurrentBB->SetWorldLocation(m_OriginalLoc + randomOffset);
	//
	//if (m_ShakeElapsed >= m_ShakeDuration)
	//{
	//	EndShake();
	//}
}

void UC_Shake::EndShake()
{
	//GetWorld()->GetTimerManager().ClearTimer(ShakeTimerHandle);
	//m_CurrentBB->SetWorldLocation(m_OriginalLoc);
}
