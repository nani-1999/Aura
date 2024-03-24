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

void AAuraCharacterBase::InitAttributeDefaults() {

	if (AttributeDefaults == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AttributeDefaults is InValid, unable to set on %s"), *GetName());
		return;
	}

	checkf(AbilitySystemComponent, TEXT("AbilitySystemComponent is InValid, unable to set AttributeDefaults"));

	const FGameplayEffectContextHandle ContextHandle;
	const FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(AttributeDefaults, 1, ContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}
