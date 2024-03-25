// Copyright Na9i Studio


#include "Character/AuraCharacterBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameplayEffect.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectBP) {

	checkf(EffectBP, TEXT("AttributeDefaults is InValid, in AuraCharacterBase"));

	checkf(AbilitySystemComponent, TEXT("AbilitySystemComponent is InValid, in AuraCharacterBase"));

	const FGameplayEffectContextHandle ContextHandle;
	//calling GetLvl(), since AuraCharacter Lvl is not real level
	//always use GetLvl() instead of directly accessing Lvl
	const FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectBP, GetLvl(), ContextHandle); 
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}
