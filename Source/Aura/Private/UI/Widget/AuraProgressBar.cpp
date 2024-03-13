// Copyright Na9i Studio


#include "UI/Widget/AuraProgressBar.h"
#include "Components/ProgressBar.h"

void UAuraProgressBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	ShadowProgressBar->SetPercent(FMath::FInterpConstantTo(ShadowProgressBar->GetPercent(), ProgressBar->GetPercent(), InDeltaTime, 0.1f));
}

void UAuraProgressBar::SetPercent(float NewPercent) {
	ProgressBar->SetPercent(NewPercent);
}