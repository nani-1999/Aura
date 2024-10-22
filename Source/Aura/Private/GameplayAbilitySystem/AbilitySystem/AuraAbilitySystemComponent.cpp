// Copyright Na9i Studio 2024.


#include "GameplayAbilitySystem/AbilitySystem/AuraAbilitySystemComponent.h"

#include "Aura/Nani/NaniUtility.h"

//void UAuraAbilitySystemComponent::BindAppliedEffectTags() {
//
//
//	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectAppliedToSelf);
//	OnGameplayEffectAppliedDelegateToTarget.AddUObject(this, &UAuraAbilitySystemComponent::EffectAppliedToTarget);
//
//	NANI_LOG(Warning, "%s | BindAppliedEffectTags", *GetAvatarActor()->GetName());
//}
//
//void UAuraAbilitySystemComponent::EffectAppliedToSelf(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle) {
//	NANI_LOG(Warning, "%s | EffectAppliedToSelf", *GetAvatarActor()->GetName());
//
//	FGameplayTagContainer AssetTags;
//	EffectSpec.GetAllAssetTags(AssetTags);
//	OnAppliedEffectAssetTags.Broadcast(AssetTags);
//}
//void UAuraAbilitySystemComponent::EffectAppliedToTarget(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle) {
//	NANI_LOG(Warning, "%s | EffectAppliedToTarget", *GetAvatarActor()->GetName());
//}