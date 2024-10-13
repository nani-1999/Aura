// Copyright Na9i Studio 2024.


#include "UI/Widget/AuraProgressBar.h"
#include "Components/ProgressBar.h"

void UAuraProgressBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (GhostProgressBar->GetPercent() != ProgressBar->GetPercent()) {
		GhostProgressBar->SetPercent(FMath::FInterpConstantTo<float>(GhostProgressBar->GetPercent(), ProgressBar->GetPercent(), InDeltaTime, 0.2f));
	}
}

void UAuraProgressBar::SetPercent() {
	ProgressBar->SetPercent(MaxValue ? Value / MaxValue : 0);
}