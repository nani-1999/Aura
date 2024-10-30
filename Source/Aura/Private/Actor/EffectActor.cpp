// Copyright Na9i Studio 2024.


#include "Actor/EffectActor.h"
#include "Components/BoxComponent.h"
#include "GameplayEffect.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySystem/AbilitySystem/AuraAbilitySystemComponent.h"

#include "Aura/Nani/NaniUtility.h"

AEffectActor::AEffectActor() :
	EffectApplicationPolicy{ EEffectApplicationPolicy::EEAP_None },
	EffectLevel{ 1.f }
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollision"));
	SetRootComponent(BoxCollision);
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AEffectActor::BeginPlay() {
	Super::BeginPlay();

	if (EffectApplicationPolicy != EEffectApplicationPolicy::EEAP_None) {
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AEffectActor::BoxCollisionOverlapBegin);
		if (EffectApplicationPolicy == EEffectApplicationPolicy::EEAP_ApplyAndRemove) BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AEffectActor::BoxCollisionOverlapEnd);
	}
}

void AEffectActor::BoxCollisionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwEEAP, const FHitResult& SwEEAPResult) {
	
	if (const IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(OtherActor)) {

		UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(ASI->GetAbilitySystemComponent());

		if (HasAuthority()) {
			NANI_LOG(Warning, "%s | Applying Effect on Authority", *GetName());
			// Applying Effect on Authority
			ApplyEffectToTargetASC(AuraASC);
		}
		if (AuraASC->IsLocalASC()) {
			// this will only be happening locally
			BroadcastAssetTagsToTargetASC(AuraASC);
		}

		// Destroying irrespective of proxy
		if (EffectApplicationPolicy == EEffectApplicationPolicy::EEAP_ApplyAndDestroy) Destroy();
	}
}

void AEffectActor::BoxCollisionOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

	if (const IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(OtherActor)) {
		if (!HasAuthority()) return;

		UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent();
		ASC->RemoveActiveGameplayEffect(ActiveEffects.FindAndRemoveChecked(ASC));
	}
}

void AEffectActor::ApplyEffectToTargetASC(UAbilitySystemComponent* TargetASC) {
	// ContextHandle
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext(); //instigator is set by makecontexthandle
	EffectContextHandle.AddSourceObject(this); //source is setting here

	// EffectSpecHandle
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(EffectBP, EffectLevel, EffectContextHandle);

	// Applying Effecct
	FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), TargetASC);

	// @Important, ActiveEffect must be stored inside who ever casted it
	// valid checking since applying instant effects don't give FActiveGameplayEffectHandle, welp instant effects don't binded to EndOverlap
	if (EffectApplicationPolicy == EEffectApplicationPolicy::EEAP_ApplyAndRemove) ActiveEffects.Add(TargetASC, ActiveEffectHandle);
}

void AEffectActor::BroadcastAssetTagsToTargetASC(UAbilitySystemComponent* TargetASC) {
	// Getting AssetTags from Effect Blueprint
	const FGameplayTagContainer AssetTags = EffectBP.GetDefaultObject()->InheritableGameplayEffectTags.CombinedTags;

	// If there are no asset tags we are returning
	if (AssetTags.Num() <= 0) return;

	// Broadcasting it to AuraASC
	Cast<UAuraAbilitySystemComponent>(TargetASC)->OnAppliedEffectAssetTags.Broadcast(AssetTags);

	//
	for (const FGameplayTag& Tag : AssetTags) {
		NANI_LOG(Warning, "%s Applying AssetTag: %s on %s", *GetName(), *Tag.ToString(), *TargetASC->GetAvatarActor()->GetName());
	}
}