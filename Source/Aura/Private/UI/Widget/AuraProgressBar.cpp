// Copyright Na9i Studio


#include "UI/Widget/AuraProgressBar.h"
#include "Components/ProgressBar.h"

UAuraProgressBar::UAuraProgressBar(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer), 
	Val{ 1 }, 
	MaxVal{ 1 } 
{
	//since uuseridget only had UUserWidget::UUserWidget(const FObjectInitializer& ObjectInitializer); this constructor
}

void UAuraProgressBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	ShadowProgressBar->SetPercent(FMath::FInterpConstantTo(ShadowProgressBar->GetPercent(), ProgressBar->GetPercent(), InDeltaTime, 0.1f));
}

void UAuraProgressBar::SetPercent(float NewPercent) {
	UE_LOG(LogTemp, Warning, TEXT("%s Percent: %f"), *GetName(), NewPercent);
	ProgressBar->SetPercent(NewPercent);
}
float UAuraProgressBar::GetPercent() const {
	return ProgressBar->GetPercent();
}
void UAuraProgressBar::SetVal(float NewVal) {
	Val = NewVal;
	SetPercent(Val / MaxVal);
}
void UAuraProgressBar::SetMaxVal(float NewMaxVal) {
	MaxVal = NewMaxVal;
	SetPercent(NewMaxVal ? Val / MaxVal : 0); //zero divide prevention
}