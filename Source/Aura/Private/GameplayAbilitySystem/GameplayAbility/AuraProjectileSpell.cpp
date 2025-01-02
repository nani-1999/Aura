// Copyright Na9i Studio 2024.


#include "GameplayAbilitySystem/GameplayAbility/AuraProjectileSpell.h"
#include "Aura/Nani/NaniUtility.h"
#include "GameplayAbilitySystem/GameplayAbility/AbilityActor/AuraProjectile.h"
#include "Interface/CombatInterface.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) {
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// this function is automatically called by ASC

	NANI_LOG(Warning, "AuraProjectileSpell Activated");
	if (!HasAuthority(&ActivationInfo)) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetCurrentActorInfo()->AvatarActor.Get());
	FTransform WeaponSocketTransform = CombatInterface->GetCombatWeaponSocketTransform();
	// using weapon socket location and actor rotation
	GetWorld()->SpawnActor<AAuraProjectile>(ProjectileBP, WeaponSocketTransform.GetLocation(), GetCurrentActorInfo()->AvatarActor->GetActorRotation());

}