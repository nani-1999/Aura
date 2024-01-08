// Copyright Na9i Studio


#include "AuraEffectActor.h"
#include "Components/BoxComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "GameplayEffect.h"



AAuraEffectActor::AAuraEffectActor() :
	EffectActorPolicy{ EEffectActorPolicy::DoNotApply },
	ActorLevel{ 1.f }
{
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(Box);
	Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Box->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	Box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	if (EffectActorPolicy != EEffectActorPolicy::DoNotApply) {
		UE_LOG(LogTemp, Warning, TEXT("%s OverlapBegin"), *GetName());
		Box->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::BoxOverlapBegin);
		if (EffectActorPolicy == EEffectActorPolicy::ApplyAndRemove) {
			UE_LOG(LogTemp, Warning, TEXT("%s OverlapEnd"), *GetName());
			Box->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::BoxOverlapEnd);
		}
	}
}

void AAuraEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAuraEffectActor::BoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (EffectActorPolicy != EEffectActorPolicy::DoNotApply && OtherActor) {
		ApplyEffectToTarget(OtherActor, this, GameplayEffectClass);
		if (EffectActorPolicy == EEffectActorPolicy::ApplyAndDestroy) Destroy();
	}
}
void AAuraEffectActor::BoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (EffectActorPolicy != EEffectActorPolicy::DoNotApply && OtherActor) {
		//UE_LOG(LogTemp, Warning, TEXT("EndOverlap"));
		RemoveEffectOnTarget(OtherActor);
	}
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* Target, AActor* Context, TSubclassOf<UGameplayEffect> EffectClass) {
	checkf(GameplayEffectClass, TEXT("Unable to Apply GameplayEffect due to invalid GameplayEffectClass"));
	IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(Target);
	if (AbilitySystemInterface == nullptr) return;
	UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();

	// ContextHandle
	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext(); //constructing contexthandle
	EffectContextHandle.AddSourceObject(Context); //context is the source
	// EffectHandle
	FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, ActorLevel, EffectContextHandle);

	// Active EffectHandle
	FActiveGameplayEffectHandle ActiveEffectSpecHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	if (EffectActorPolicy == EEffectActorPolicy::ApplyAndRemove) {
		ActiveEffectHandles.Add(AbilitySystemComponent, ActiveEffectSpecHandle); //Keeping tracks on Active Effect
	}
}
void AAuraEffectActor::RemoveEffectOnTarget(AActor* Target) {
	IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(Target);
	if (AbilitySystemInterface == nullptr) return;
	UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();

	FActiveGameplayEffectHandle ActiveEffectHandle = ActiveEffectHandles.FindAndRemoveChecked(AbilitySystemComponent); //finds key, returns its value, removes key and value from map

	AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveEffectHandle, 1); //what if aura in another fire overlap while first fire overlap end, draining must still continues, but i will not stack the infinite tho
}
