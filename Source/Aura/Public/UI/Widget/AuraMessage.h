// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraMessage.generated.h"

class UImage;
class UTextBlock;
class UWidgetAnimation;

UCLASS()
class AURA_API UAuraMessage : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	// Widget
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Icon;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Title;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> Detail;

	// Animation
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> SlideFadeOut;

	// Called when any Animation is Finished Playing
	virtual void OnAnimationFinishedPlaying(UUMGSequencePlayer& Player) override { RemoveFromParent(); }

public:
	virtual void RemoveFromParent() override { UE_LOG(LogTemp, Warning, TEXT("AuraMessage | Widget Removed")); Super::RemoveFromParent(); }

	static UAuraMessage* CreateMessage(UWorld* WorldContext, TSubclassOf<UAuraMessage> MessageClass, UTexture2D* IconTexture, const FText& TitleText, const FText& DetailText);
};