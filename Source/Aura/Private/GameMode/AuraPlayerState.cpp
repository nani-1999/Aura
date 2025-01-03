// Copyright Na9i Studio 2024.


#include "GameMode/AuraPlayerState.h"
#include "GameplayAbilitySystem/AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameplayAbilitySystem/AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h" // @For DOREPLIFETIME_CONDITION_NOTIFY

AAuraPlayerState::AAuraPlayerState() :
	CharacterLevel{ 1 }
{
	NetUpdateFrequency = 100.f;

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>(FName("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>(FName("AttributeSet"));
}

//
//============================================ Network ============================================
//
void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAuraPlayerState, CharacterLevel);
}

//
//============================================ Combat Interface ============================================
//
FTransform AAuraPlayerState::GetCombatWeaponSocketTransform() const {
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(AbilitySystemComponent->GetAvatarActor());
	return CombatInterface->GetCombatWeaponSocketTransform();
}