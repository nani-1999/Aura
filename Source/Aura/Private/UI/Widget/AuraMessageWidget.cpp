// Copyright Na9i Studio


#include "UI/Widget/AuraMessageWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


void UAuraMessageWidget::NativeConstruct() {
	Super::NativeConstruct();

	if (MessageAnimation) PlayAnimation(MessageAnimation);
}

void UAuraMessageWidget::SetMessageIcon(UTexture2D* Icon) {
	if (MessageIcon && Icon) MessageIcon->SetBrushFromTexture(Icon);
}
void UAuraMessageWidget::SetMessageText(FText Text) {
	if (MessageText) MessageText->SetText(Text);
}
