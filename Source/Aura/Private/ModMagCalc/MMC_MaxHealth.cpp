// Copyright Na9i Studio


#include "ModMagCalc/MMC_MaxHealth.h"
#include "AbilitySystem/AuraAttributeSet.h"

UMMC_MaxHealth::UMMC_MaxHealth() {
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const {

	// getting tags
	//since, getcaptureattributemagnitude() requires these
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags(); //tags that are active on source or source has
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags(); //tags that are active on target or target has
	//type for combining source tags and target tags in one
	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = SourceTags;
	EvaluationParams.TargetTags = TargetTags;

	float VigorMag = 0.f;
	bool bCaptureMagnitudeSuccessful = GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluationParams, VigorMag);
	VigorMag = FMath::Max<float>(VigorMag, 0.f);

	return VigorMag;

	//source level
	//we can get from spec's contexthandle
	//optional, since we provide in applygameplayeffecttoself or applygameplayeffecttotarget
}
