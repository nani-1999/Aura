// Copyright Na9i Studio 2024.

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

	// Setters
	void SetLabelName(const FText NameTxt);
	void SetLabelValue(const FText ValueTxt);
};
