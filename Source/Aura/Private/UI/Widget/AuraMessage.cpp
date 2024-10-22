// Copyright Na9i Studio 2024.


#include "UI/Widget/AuraMessage.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"

void UAuraMessage::NativeOnInitialized() {
	Super::NativeOnInitialized();

	PlayAnimation(SlideFadeOut);

	UE_LOG(LogTemp, Warning, TEXT("Widget Animation Playing"));
}

UAuraMessage* UAuraMessage::CreateMessage(UWorld* WorldContext, TSubclassOf<UAuraMessage> MessageBP, const FGameplayTag& Tag, UTexture2D* IconTexture, const FText TitleText) {

	UE_LOG(LogTemp, Warning, TEXT("Before Widget Created"));

	UAuraMessage* AuraMessage = CreateWidget<UAuraMessage>(WorldContext, MessageBP);

	UE_LOG(LogTemp, Warning, TEXT("Widget Created"));

	//AuraMessage->MessageTag = Tag;
	//AuraMessage->Icon->SetBrushFromTexture(IconTexture);
	//AuraMessage->Title->SetText(TitleText);

	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);


	UE_LOG(LogTemp, Warning, TEXT("Widget Added To Viewport"));

	return AuraMessage;
}