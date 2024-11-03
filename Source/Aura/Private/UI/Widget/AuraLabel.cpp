// Copyright Na9i Studio 2024.


#include "UI/Widget/AuraLabel.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UAuraLabel::SetLabelName(const FText NameTxt) {
	LabelName->SetText(NameTxt);
}
void UAuraLabel::SetLabelValue(const FText ValueTxt) {
	LabelValue->SetText(ValueTxt);
}