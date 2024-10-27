// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h" // @For FGameplayTagContainer
#include "AuraOverlayManager.generated.h"

class UAuraOverlay;
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
	void StrengthChanged(const FOnAttributeChangeData& Data);
	void IntelligenceChanged(const FOnAttributeChangeData& Data);
	void ResilienceChanged(const FOnAttributeChangeData& Data);
	void VigorChanged(const FOnAttributeChangeData& Data);
	void ArmorChanged(const FOnAttributeChangeData& Data);
	void ArmorPenetrationChanged(const FOnAttributeChangeData& Data);
	void BlockChanceChanged(const FOnAttributeChangeData& Data);
	void CriticalHitChanceChanged(const FOnAttributeChangeData& Data);
	void CriticalHitDamageChanged(const FOnAttributeChangeData& Data);
	void CriticalHitResistanceChanged(const FOnAttributeChangeData& Data);
	void HealthRegenerationChanged(const FOnAttributeChangeData& Data);
	void ManaRegenerationChanged(const FOnAttributeChangeData& Data);
	void MaxHealthChanged(const FOnAttributeChangeData& Data);
	void MaxManaChanged(const FOnAttributeChangeData& Data);

	// ASC AssetTags
	UFUNCTION()
	void AppliedEffectAssetTags(const FGameplayTagContainer& Tags);

	// Message
	void DisplayMessage(const FName MessageName);

public:
	// Overlay
	void SetupOverlay(UAuraOverlay* OverlayVal);

	// Attribute Menu
	UFUNCTION()
	void InitAttributeMenu();
};
