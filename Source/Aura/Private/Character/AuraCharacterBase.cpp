// Copyright Na9i Studio 2024.


#include "Character/AuraCharacterBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "GameplayEffect.h"
#include "DataAsset/AuraCharacterClassInfo.h"
#include "Abilities/GameplayAbility.h"

#include "Aura/Nani/NaniUtility.h"

AAuraCharacterBase::AAuraCharacterBase() :
	CharacterLevel{ 1 }
{
	PrimaryActorTick.bCanEverTick = false;

	// Weapon
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Weapon"));
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// removing camera blocking by Character's Meshes
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::InitAbilitySystem() {
	// must be called after ASC's AbilityActorInfo is set
	NANI_LOG(Warning, "InitAbilitySystem");

	// Attribute Defaults
	InitAttributeDefaults();

	// Startup Abilities
	GiveStartupAbilities();
}

void AAuraCharacterBase::InitAttributeDefaults() {
	// checking
	checkf(CharacterClassInfo, TEXT("AuraCharacterBase | CharacterClassInfo is Invalid | ObjectName: %s"), *GetName());

	// Initializing Attribute Defaults in the form of GameplayEffects
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	const FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();

	// Applying secondaryattributes first, since they are inf effect
	ASC->ApplyGameplayEffectToSelf(CharacterClassInfo->Secondary_AttributeDefaults.GetDefaultObject(), GetCharacterLevel(), EffectContextHandle);
	ASC->ApplyGameplayEffectToSelf(CharacterClassInfo->GetPrimaryAttributeDefaults(GetCharacterClass()).GetDefaultObject(), GetCharacterLevel(), EffectContextHandle);
	ASC->ApplyGameplayEffectToSelf(CharacterClassInfo->Vital_AttributeDefaults.GetDefaultObject(), GetCharacterLevel(), EffectContextHandle);
}

void AAuraCharacterBase::GiveStartupAbilities() {
	// checking
	checkf(CharacterClassInfo, TEXT("AuraCharacterBase | CharacterClassInfo is Invalid | ObjectName: %s"), *GetName());

	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();

	// giving common abilities
	for (TSubclassOf<UGameplayAbility>& AbilityClass : CharacterClassInfo->CommonAbilities) {
		const FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, GetCharacterLevel());
		ASC->GiveAbility(AbilitySpec);
	}
}