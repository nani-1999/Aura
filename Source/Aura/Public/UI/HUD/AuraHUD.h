// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraUserWidget;
class APlayerController;
class APlayerState;
class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;
//class UOverlayidgetController;

UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	//virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
};
