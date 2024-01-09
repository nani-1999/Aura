// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraProgressGlobe.generated.h"

class UProgressBar;

UCLASS()
class AURA_API UAuraProgressGlobe : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// Widgets
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> GhostProgressBar;

	// Properties
	float Value = 1.f;
	float MaxValue = 1.f;

public:
	void SetProgressGlobeValue(float NewValue);
	void SetProgressGlobeMaxValue(float NewMaxValue);
};
