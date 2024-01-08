// Copyright Na9i Studio


#include "Character/AuraCharacterBase.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "GameplayEffect.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Weapon"));
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::BeginPlay() {
	Super::BeginPlay();

	AActor* Onar = GetOwner();

	if (Onar) {
		UE_LOG(LogTemp, Warning, TEXT("%s Owner is %s"), *GetName(), *Onar->GetName());
	}

}

//void AAuraCharacterBase::EffectAppliedOnASC(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle) {
//	// called when GameplayEffects Applied to AbilitySystemComponent, where we get Applied GameplayEffects
//
//	UE_LOG(LogTemp, Warning, TEXT("Effect Applied on ASC"));
//
//	FGameplayTagContainer TagContainer; // ASC/GE alrealy knows FGameplayTagContainer
//	//EffectSpec.GetAllGrantedTags(TagContainer); //Only gets GrantedTags // visible on asc debug
//	EffectSpec.GetAllAssetTags(TagContainer); //Only gets GameplayEffectAssetTag // not visible on asc debug
//
//	for (const FGameplayTag& Tag : TagContainer) {
//		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 8.f, FColor::Blue, *Tag.ToString()); // -1 so new messages can't replace older messages
//	}
//}
