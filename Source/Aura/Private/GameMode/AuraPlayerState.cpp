// Copyright Na9i Studio 2024.


#include "GameMode/AuraPlayerState.h"
#include "GameplayAbilitySystem/AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameplayAbilitySystem/AbilitySystem/AuraAttributeSet.h"

#include "Aura/Nani/NaniUtility.h"

AAuraPlayerState::AAuraPlayerState() :
	CharacterLevel{ 1 }
{

	NetUpdateFrequency = 100.f;

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>(FName("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>(FName("AttributeSet"));
}
