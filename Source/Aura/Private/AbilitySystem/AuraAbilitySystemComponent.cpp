// Copyright Na9i Studio


#include "AbilitySystem/AuraAbilitySystemComponent.h"


void UAuraAbilitySystemComponent::BindAppliedEffects() {

	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectAppliedToSelf);
	OnGameplayEffectAppliedDelegateToTarget.AddUObject(this, &UAuraAbilitySystemComponent::EffectAppliedToTarget);
}

void UAuraAbilitySystemComponent::EffectAppliedToSelf(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle) {

	// Called after ApplyGameplayEffectSpecToSelf called with no target

	FString EffectName = EffectSpec.ToSimpleString();
	FString EffectActor = EffectSpec.GetEffectContext().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s Self Applied on %s"), *EffectName, *EffectActor);

	// Broadcasting Effect GameplayTags
	//here, since ApplyGameplayEffectSpecToTarget()  also calling EffectAppliedToSelf()
	FGameplayTagContainer AssetTags;
	EffectSpec.GetAllAssetTags(AssetTags);
	OnAppliedEffectAssetTags.Broadcast(AssetTags);

	//displaying effect tags
	for (FGameplayTag Tag : AssetTags) {
		UE_LOG(LogTemp, Warning, TEXT("Applied Effect Asset Tag: %s"), *Tag.ToString());
	}
}
void UAuraAbilitySystemComponent::EffectAppliedToTarget(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle) {

	// Called after ApplyGameplayEffectSpecToTarget called with target

	FString EffectName = EffectSpec.ToSimpleString();
	FString EffectActor = EffectSpec.GetEffectContext().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s Targeted Applied on %s"), *EffectName, *EffectActor);
}
