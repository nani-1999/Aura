// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraOverlay;
class APlayerController;

UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	// Panel Widgets
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraOverlay> OverlayBP;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAuraOverlay> Overlay;

public:
	void SetupOverlay(APlayerController* PC);
};
