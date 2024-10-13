// Copyright Na9i Studio 2024.


#include "Actor/EffectActor.h"
#include "Components/BoxComponent.h"
#include "GameplayEffect.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

#include "Aura/Nani/NaniUtility.h"

AEffectActor::AEffectActor() :
	EffectPolicy{ EEffectPolicy::EEP_None },
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

	if (EffectPolicy != EEffectPolicy::EEP_None) {
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AEffectActor::BoxCollisionOverlapBegin);
		if (EffectPolicy == EEffectPolicy::EEP_ApplyAndRemove) BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AEffectActor::BoxCollisionOverlapEnd);
	}
}

void AEffectActor::BoxCollisionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (EffectPolicy == EEffectPolicy::EEP_ApplyAndDestroy) Destroy();

	if (!HasAuthority()) return;

	if (const IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(OtherActor)) {
		NANI_LOG(Warning, "%s is Begin Overlap on %s", *OtherActor->GetName(), *GetName());

		UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent();

		FGameplayEffectContextHandle EffectContextHandle;
		EffectContextHandle.AddSourceObject(this);

		ASC->ApplyGameplayEffectToTarget(EffectBP.GetDefaultObject(), ASC, EffectLevel, EffectContextHandle); 

		// valid checking since applying instant effects don't give FActiveGameplayEffectHandle
		// does it requre to store FActiveGameplayEffectHandle?, since ASC::RemoveActiveGameplayEffectBySourceEffect() does the trick.
		//if (ActiveEffect.IsValid() && EffectPolicy == EEffectPolicy::EEP_ApplyAndRemove) ActiveEffects.Add(ActiveEffect);
	}
}

void AEffectActor::BoxCollisionOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (!HasAuthority()) return;

	if (const IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(OtherActor)) {
		NANI_LOG(Warning, "%s is End Overlap on %s", *OtherActor->GetName(), *GetName());

		UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent();

		ASC->RemoveActiveGameplayEffectBySourceEffect(EffectBP, ASC);
	}
}
