// Copyright Na9i Studio


#include "UI/Widget/AuraLabel.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UAuraLabel::SetLabelName(FString NewName) {
	LabelName->SetText(FText::FromString(NewName));
}

void UAuraLabel::SetLabelValue(float NewValue) {
	LabelName->SetText(FText::AsNumber(NewValue));
}
