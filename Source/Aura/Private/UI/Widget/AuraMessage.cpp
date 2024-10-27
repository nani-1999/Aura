// Copyright Na9i Studio 2024.


#include "UI/Widget/AuraMessage.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"
#include "Blueprint/UserWidget.h"

void UAuraMessage::NativeConstruct() {
	Super::NativeConstruct();

	PlayAnimation(SlideFadeOut);
}


UAuraMessage* UAuraMessage::CreateMessage(UWorld* WorldContext, TSubclassOf<UAuraMessage> MessageClass, UTexture2D* IconTexture, const FText& TitleText, const FText& DetailText) {

	UAuraMessage* AuraMessage = CreateWidget<UAuraMessage>(WorldContext, MessageClass);

	UE_LOG(LogTemp, Warning, TEXT("AuraMessage | Widget Created"));

	AuraMessage->Icon->SetBrushFromTexture(IconTexture);
	AuraMessage->Title->SetText(TitleText);
	if (AuraMessage->Detail) AuraMessage->Detail->SetText(DetailText);

	return AuraMessage;
}