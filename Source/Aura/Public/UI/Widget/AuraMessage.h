// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"
#include "AuraMessage.generated.h"

class UImage;
class UTextBlock;
class UWidgetAnimation;

UCLASS()
class AURA_API UAuraMessage : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	// GameplayTag
	FGameplayTag MessageTag;

	// Widget
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Icon;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Title;

	// Animation
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> SlideFadeOut;

	// Called when any Animation is Finished Playing
	virtual void OnAnimationFinishedPlaying(UUMGSequencePlayer& Player) override { RemoveFromParent(); UE_LOG(LogTemp, Warning, TEXT("Widget Removed")); }

public:
	static UAuraMessage* CreateMessage(UWorld* WorldContext, TSubclassOf<UAuraMessage> MessageBP, const FGameplayTag& Tag, UTexture2D* IconTexture, const FText TitleText);
};