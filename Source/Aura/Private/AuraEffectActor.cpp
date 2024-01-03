// Copyright Na9i Studio


#include "AuraEffectActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "GameplayEffect.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>("SceneRoot");

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(RootComponent);
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Sphere->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	Sphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); //unable to click on instance

	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::SphereOverlapBegin);
}

void AAuraEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAuraEffectActor::SphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor) {
		ApplyEffectToTarget(OtherActor, InstantGameplayEffectClass);
	}

}

void AAuraEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass) {
	checkf(GameplayEffectClass, TEXT("Unable to Apply Effect due to invalid GameplayEffectClass"));

	IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(Target);
	if (AbilitySystemInterface == nullptr) return;
	UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();

	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

}