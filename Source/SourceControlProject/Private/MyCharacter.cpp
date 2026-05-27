// This project is made by EpicCrisis
#include "MyCharacter.h"

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
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::CharacterTurn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::CharacterLookUp);
}

void AMyCharacter::CharacterTurn(float Value)
{
	AddControllerYawInput(Value);
}

void AMyCharacter::CharacterLookUp(float Value)
{
	AddControllerPitchInput(Value);
}

