// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_BulletManager.generated.h"

class AC_Bullet;
class UMyGameInstance;
class UCSecondHud;
class AMyCharacter;
class AMyGameStateBase;

UCLASS()
class SOURCECONTROLPROJECT_API AC_BulletManager : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* m_SceneComponent = nullptr;
	UPROPERTY()
	UMyGameInstance* m_GameInstance = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMyCharacter* m_PlayerCharacter = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCSecondHud* m_NewPlayerHud = nullptr;

	UPROPERTY()
	AMyGameStateBase* m_GameState = nullptr;

	UPROPERTY()
	bool m_DoOnce = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_PooledBullet = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_GotBullet = 10;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AC_Bullet> m_BulletClass;
	UPROPERTY(VisibleAnywhere)
	TArray<AC_Bullet*> m_BulletList;

	AC_BulletManager();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void UpdatePooledBullets();

	void CheckShootBullet(FVector shootLoc, FVector playerDirection);
	void SetBulletText(int32 numberBullet);
};
