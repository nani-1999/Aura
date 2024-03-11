// Copyright Na9i Studio


#include "PlayerState/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState() {
	NetUpdateFrequency = 100.f;

	// Ability System
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed); //Replication Mode for GameplayEffect, Mixed for players

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}