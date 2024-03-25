// Copyright Na9i Studio


#include "PlayerState/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

AAuraPlayerState::AAuraPlayerState() {
	NetUpdateFrequency = 100.f;

	// Ability System
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed); //Replication Mode for GameplayEffect, Mixed for players

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

// Boilerplate Code for Replication
void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAuraPlayerState, Lvl);
}
void AAuraPlayerState::OnRep_Lvl(int32 OldLvl) {

}