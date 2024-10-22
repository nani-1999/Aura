// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"


UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

//	DECLARE_MULTICAST_DELEGATE_OneParam(FAppliedEffectTagsDelegate, const FGameplayTagContainer&);
//
//protected:
//	void EffectAppliedToSelf(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
//	void EffectAppliedToTarget(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
//
//public:
//	void BindAppliedEffectTags();
//
//	FAppliedEffectTagsDelegate OnAppliedEffectAssetTags;
};
