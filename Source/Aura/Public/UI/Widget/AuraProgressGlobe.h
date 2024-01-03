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
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar;

public:
	void SetProgressGlobePercent(float Percent);
	float GetProgressGlobePercent() const;
};
