// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraLabel.generated.h"

class UTextBlock;

UCLASS()
class AURA_API UAuraLabel : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LabelName;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LabelValue;
};
