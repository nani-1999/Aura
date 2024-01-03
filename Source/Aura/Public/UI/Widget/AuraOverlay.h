// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraOverlay.generated.h"

class UAuraProgressGlobe;
struct FOnAttributeChangeData;

UCLASS()
class AURA_API UAuraOverlay : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	void InitSubWidgets();
	void BindSubWidgets();

	// Widgets
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraProgressGlobe> HealthProgressGlobe;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraProgressGlobe> ManaProgressGlobe;

	// Binds
	void HealthChanged(const FOnAttributeChangeData& Data);
	void MaxHealthChanged(const FOnAttributeChangeData& Data);
	void ManaChanged(const FOnAttributeChangeData& Data);
	void MaxManaChanged(const FOnAttributeChangeData& Data);

	// Helpers
	float ValueChanged(float NewValue, float OldValue, float Percent);
	float MaxValueChanged(float NewValue, float OldValue, float Percent);
};
