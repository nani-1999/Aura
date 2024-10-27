// Copyright Na9i Studio 2024.


#include "GameplayAbilitySystem/AbilitySystem/AuraAbilitySystemComponent.h"

bool UAuraAbilitySystemComponent::IsLocalASC() {

	APawn* Pawn = Cast<APawn>(GetAvatarActor());

	return (Pawn != nullptr) ? Pawn->IsLocallyControlled() : false;
}