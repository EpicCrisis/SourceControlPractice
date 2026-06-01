// This project is made by EpicCrisis
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = false;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("The player character is spawned"));

	m_MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	m_CurrentHealth = m_MaxHealth;
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (m_IndexCounter > m_StartDelay)
	{
		FVector currentLoc = GetActorLocation();
		currentLoc.Y += m_MoveSpeed * DeltaTime;
		SetActorLocation(currentLoc);
	}
	else
	{
		m_IndexCounter += DeltaTime;
	}
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::CharacterTurn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::CharacterLookUp);	
	PlayerInputComponent->BindAction("LeftClick", EInputEvent::IE_Pressed, this, &AMyCharacter::CharacterLeftClick);
	PlayerInputComponent->BindAction("RightClick", EInputEvent::IE_Pressed, this, &AMyCharacter::CharacterRightClick);
}

void AMyCharacter::CharacterTurn(float Value)
{
	AddControllerYawInput(Value);
}

void AMyCharacter::CharacterLookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AMyCharacter::CharacterLeftClick()
{
}

void AMyCharacter::CharacterRightClick()
{
}

