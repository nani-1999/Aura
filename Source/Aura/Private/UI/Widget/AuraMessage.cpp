// Copyright Na9i Studio


#include "UI/Widget/AuraMessage.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UAuraMessage::NativeConstruct() {
	Super::NativeConstruct();

	if (Fadeout) PlayAnimation(Fadeout);
}

void UAuraMessage::DisplayMessage(FGameplayTag NewMessageTag, UTexture2D* NewIcon, FText NewTitle, FText NewDetail) {
	MessageTag = NewMessageTag;
	Icon->SetBrushFromTexture(NewIcon);
	Title->SetText(NewTitle);
	if (Detail) Detail->SetText(NewDetail);
}
