// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_FirstHud.generated.h"

class UTextBlock;

UCLASS()
class SOURCECONTROLPROJECT_API UC_FirstHud : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* m_HealthText = nullptr;

	UFUNCTION(BlueprintCallable)
	void SetHealthText(const FString& newMessage);
};
