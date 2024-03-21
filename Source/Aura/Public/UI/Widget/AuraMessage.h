// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h" // @For FGameplayTag
#include "AuraMessage.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class AURA_API UAuraMessage : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	// Tag
	FGameplayTag MessageTag;

	// Widget
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Icon;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Title;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> Detail;

	// Animation
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> Fadeout;

	// Called when any Animation is Finished Playing
	virtual void OnAnimationFinishedPlaying(UUMGSequencePlayer& Player) override { RemoveFromParent(); }

public:
	// Properties Setter
	void DisplayMessage(FGameplayTag NewMessageTag, UTexture2D* NewIcon, FText NewTitle, FText NewDetail = FText());
};
