// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class UMyGameInstance;
class AC_BulletManager;

UCLASS()
class SOURCECONTROLPROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_StartDelay = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_MoveSpeed = 100.0f;
	UPROPERTY()
	float m_IndexCounter = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_MaxHealth = 100;
	UPROPERTY()
	int32 m_CurrentHealth = 100;
	UPROPERTY()
	bool m_IsDownLeftClick = false;
	//UPROPERTY()
	//bool m_IsUpLeftClick = false;
	UPROPERTY()
	bool m_IsDownRightClick = false;
	//UPROPERTY()
	//bool m_IsUpRightClick = false;

	UPROPERTY()
	UMyGameInstance* m_MyGameInstance = nullptr;
	UPROPERTY()
	AC_BulletManager* m_BulletManager = nullptr;

	AMyCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CharacterTurn(float Value);
	void CharacterLookUp(float Value);
	void CharacterDownLeftClick();
	void CharacterUpLeftClick();
	void CharacterDownRightClick();
	void CharacterUpRightClick();
};
