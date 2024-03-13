// Copyright Na9i Studio


#include "Actor/AuraEffectActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraEffectActor::AAuraEffectActor() :
	EffectLevel{ 1 }
{
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SetRootComponent(SphereCollision);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(SphereCollision);
}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::SphereCollisionOverlapBegin);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::SphereCollisionOverlapEnd);
}

void AAuraEffectActor::SphereCollisionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (IAbilitySystemInterface* AbilitySystemActor = Cast<IAbilitySystemInterface>(OtherActor)) {

		UAbilitySystemComponent* ASC = AbilitySystemActor->GetAbilitySystemComponent();
		const UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(ASC->GetAttributeSet(UAuraAttributeSet::StaticClass()));

		UAuraAttributeSet* AuraAS_notconst = const_cast<UAuraAttributeSet*>(AuraAS);
		AuraAS_notconst->SetHealth(AuraAS_notconst->GetHealth() + 15.f);
		Destroy();

		//// Const required     and Source not required, for ApplyGameplayEffectSpecToSelf()
		//// Const not required and Source required    , for ApplyGameplayEffectSpecToTarget();
		//FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
		//EffectContextHandle.AddSourceObject(this); //source is this, target is AbilitySystemActor 

		//const FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(Effect, EffectLevel, EffectContextHandle);

		//FActiveGameplayEffectHandle ActiveEffectHandle = ASC->ApplyGameplayEffectSpecToTarget(EffectSpecHandle.Data.ToSharedRef().Get(), ASC);
	}
}
void AAuraEffectActor::SphereCollisionOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

}

//void AAuraEffectActor::ApplyEffectToASC(TSubclassOf<UGameplayEffect> Effect) {
//
//}