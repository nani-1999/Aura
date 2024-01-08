// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h" // for FGameplayTag
#include "AuraMessageWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class AURA_API UAuraMessageWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	// Widgets
	UPROPERTY()
	FGameplayTag MessageGameplayTag;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> MessageIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MessageText;

	// Animation
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> MessageAnimation;

	virtual void OnAnimationFinishedPlaying(UUMGSequencePlayer& Player) override { RemoveFromParent(); }

public:
	FORCEINLINE void SetMessageTag(const FGameplayTag& MessageTag) { MessageGameplayTag = MessageTag; }
	void SetMessageText(FText Text);
	void SetMessageIcon(UTexture2D* Icon);
};
