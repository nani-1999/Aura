// Copyright Na9i Studio


#include "UI/Widget/AuraProgressGlobe.h"
#include "Components/ProgressBar.h"

void UAuraProgressGlobe::SetProgressGlobePercent(float Percent) {
	if (ProgressBar) ProgressBar->SetPercent(Percent);
}
float UAuraProgressGlobe::GetProgressGlobePercent() const {
	if (ProgressBar) return ProgressBar->GetPercent();
	return 0.f;
}