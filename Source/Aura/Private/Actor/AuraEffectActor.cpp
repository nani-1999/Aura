// Copyright Na9i Studio


#include "Actor/AuraEffectActor.h"
#include "Components/BoxComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"

AAuraEffectActor::AAuraEffectActor() :
	EffectLevel{ 1 },
	EffectPolicy{ EEffectPolicy::EEP_None }
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	SetRootComponent(BoxCollision);
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (EffectPolicy != EEffectPolicy::EEP_None) {
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::BoxCollisionOverlapBegin);
		if (EffectPolicy == EEffectPolicy::EEP_ApplyAndRemove) BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::BoxCollisionOverlapEnd);
	}
}

void AAuraEffectActor::BoxCollisionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin")); // @LOG
	if (IAbilitySystemInterface* AbilitySystemActor = Cast<IAbilitySystemInterface>(OtherActor)) {
		ApplyEffectOnASC(EffectBP, AbilitySystemActor->GetAbilitySystemComponent());

		if (EffectPolicy == EEffectPolicy::EEP_ApplyAndDestroy) Destroy();
	}
}
void AAuraEffectActor::BoxCollisionOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	UE_LOG(LogTemp, Warning, TEXT("Overlap End")); // @LOG
	if (IAbilitySystemInterface* AbilitySystemActor = Cast<IAbilitySystemInterface>(OtherActor)) {
		RemoveEffectOnASC(AbilitySystemActor->GetAbilitySystemComponent());
	}
}

void AAuraEffectActor::ApplyEffectOnASC(TSubclassOf<UGameplayEffect> Effect, UAbilitySystemComponent* ASC) {
	if (Effect && ASC) {
		// Const required     and Source not required, for ApplyGameplayEffectSpecToSelf()
		// Const not required and Source required    , for ApplyGameplayEffectSpecToTarget();
		FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);

		FGameplayEffectSpecHandle EffectspecHandle = ASC->MakeOutgoingSpec(Effect, EffectLevel, EffectContextHandle);

		FActiveGameplayEffectHandle ActiveEffectHandle = ASC->ApplyGameplayEffectSpecToTarget(*EffectspecHandle.Data.Get(), ASC); // Handle to Shared_ptr to raw Ptr to *Ptr(value)

		if (EffectPolicy == EEffectPolicy::EEP_ApplyAndRemove) ActiveEffectHandles.Add(ASC, ActiveEffectHandle);
	}
}
void AAuraEffectActor::RemoveEffectOnASC(UAbilitySystemComponent* ASC) {
	if (ASC && ActiveEffectHandles.Contains(ASC)) {

		UE_LOG(LogTemp, Warning, TEXT("Contains Effect")); //@LOG

		FActiveGameplayEffectHandle* ActiveEffectHandle = ActiveEffectHandles.Find(ASC);
		bool bRemoveSuccessful = ASC->RemoveActiveGameplayEffect(*ActiveEffectHandle, 1); //for EEffectPolicy::EEP_ApplyAndRemove remove stacks properly

		if (!bRemoveSuccessful) UE_LOG(LogTemp, Error, TEXT("Unable to Remove Effect On ASC | %s"), *GetName());

		ActiveEffectHandles.FindAndRemoveChecked(ASC);

		// @LOG
		bool bContains = ActiveEffectHandles.Contains(ASC);
		if (!bContains) UE_LOG(LogTemp, Warning, TEXT("Does not Contains Effect"));
	}
}
