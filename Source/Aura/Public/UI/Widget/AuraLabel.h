// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraLabel.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class AURA_API UAuraLabel : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LabelName;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LabelValue;

public:
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UButton> LabelButton;

	void SetLabelName(FString NewName);
	void SetLabelValue(float NewValue);
};
