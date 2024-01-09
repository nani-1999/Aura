// Copyright Na9i Studio


#include "UI/Widget/AuraProgressGlobe.h"
#include "Components/ProgressBar.h"


void UAuraProgressGlobe::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (GhostProgressBar && ProgressBar) { GhostProgressBar->SetPercent(FMath::FInterpTo<float>(GhostProgressBar->GetPercent(), ProgressBar->GetPercent(), InDeltaTime, 1.f)); }
}

void UAuraProgressGlobe::SetProgressGlobeValue(float NewValue) {
	Value = NewValue;
	ProgressBar->SetPercent(Value / MaxValue);
}
void UAuraProgressGlobe::SetProgressGlobeMaxValue(float NewMaxValue) {
	MaxValue = NewMaxValue;
	ProgressBar->SetPercent(Value / MaxValue);
}