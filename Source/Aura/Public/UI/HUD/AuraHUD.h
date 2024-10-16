// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Misc/Crc.h"
#include "AuraHUD.generated.h"

class UAuraOverlay;
class UAuraOverlayManager;

UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

protected:
	// Overlay
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults | Overlay")
	TSubclassOf<UAuraOverlay> OverlayBP;
	UPROPERTY()
	TObjectPtr<UAuraOverlay> Overlay;
	UPROPERTY()
	TObjectPtr<UAuraOverlayManager> OverlayManager;

public:
	void InitOverlay(APlayerController* PC);
};
