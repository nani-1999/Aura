// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraProgressBar.generated.h"

class UProgressBar;

UCLASS()
class AURA_API UAuraProgressBar : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// Widgets
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> GhostProgressBar;

	// Data
	float MaxValue;
	float Value;

	void SetPercent();

	// Tick
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	FORCEINLINE void SetValue(float NewValue) { Value = NewValue; SetPercent(); }
	FORCEINLINE void SetMaxValue(float NewMaxValue) { NewMaxValue = NewMaxValue; SetPercent(); }
};
