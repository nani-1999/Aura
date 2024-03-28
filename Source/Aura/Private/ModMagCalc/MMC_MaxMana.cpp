// Copyright Na9i Studio


#include "ModMagCalc/MMC_MaxMana.h"
#include "AbilitySystem/AuraAttributeSet.h"

UMMC_MaxMana::UMMC_MaxMana() {
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const {
	Super::CalculateBaseMagnitude_Implementation(Spec);

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = SourceTags;
	EvaluateParams.TargetTags = TargetTags;

	float IntelligenceMag = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluateParams, IntelligenceMag);
	IntelligenceMag = FMath::Max<float>(IntelligenceMag, 0.f);

	return IntelligenceMag;
}