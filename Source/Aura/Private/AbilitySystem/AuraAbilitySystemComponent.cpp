// Copyright Na9i Studio


#include "AbilitySystem/AuraAbilitySystemComponent.h"


void UAuraAbilitySystemComponent::BindEffectsApplied() {

	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectAppliedToSelf);
	OnGameplayEffectAppliedDelegateToTarget.AddUObject(this, &UAuraAbilitySystemComponent::EffectAppliedToTarget);
}

void UAuraAbilitySystemComponent::EffectAppliedToSelf(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle) {

	UE_LOG(LogTemp, Warning, TEXT("Effect Applied To Self ASC"));

}
void UAuraAbilitySystemComponent::EffectAppliedToTarget(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle) {

	UE_LOG(LogTemp, Warning, TEXT("Effect Applied To Target ASC"));
}
