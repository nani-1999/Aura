// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraProgressBar.generated.h"

class UProgressBar;

UCLASS()
class AURA_API UAuraProgressBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UAuraProgressBar(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ShadowProgressBar;

	float Val;
	float MaxVal;

public:
	void SetPercent(float NewPercent);
	float GetPercent() const;
	void SetVal(float NewVal);
	void SetMaxVal(float NewMaxVal);
};
