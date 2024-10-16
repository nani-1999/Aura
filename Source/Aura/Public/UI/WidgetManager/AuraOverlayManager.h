// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AuraOverlayManager.generated.h"

class UAuraOverlay;
class APlayerController;
struct FOnAttributeChangeData;

UCLASS()
class AURA_API UAuraOverlayManager : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	TObjectPtr<UAuraOverlay> Overlay;

	// Callbacks
	void HealthChanged(const FOnAttributeChangeData& Data);
	void ManaChanged(const FOnAttributeChangeData& Data);
	void MaxHealthChanged(const FOnAttributeChangeData& Data);
	void MaxManaChanged(const FOnAttributeChangeData& Data);

public:
	void SetupOverlay(UAuraOverlay* OverlayVal);
};
