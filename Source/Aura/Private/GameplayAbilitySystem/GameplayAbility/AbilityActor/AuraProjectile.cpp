// Copyright Na9i Studio 2024.


#include "GameplayAbilitySystem/GameplayAbility/AbilityActor/AuraProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Aura/Nani/NaniUtility.h" // @For: ECC_NonPhysical, NANI_LOG
#include "NiagaraSystem.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h" // @For: PlaySoundAtLocation()
#include "NiagaraFunctionLibrary.h" // @For: SpawnSystemAtLocation() // @Requires Modules: "NavigationSystem", "Niagara"

AAuraProjectile::AAuraProjectile() :
	ProjectileLifeSpan{ 1.f }
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileComp"));
	ProjectileComp->InitialSpeed = 550.f;
	ProjectileComp->MaxSpeed = 550.f;
	ProjectileComp->ProjectileGravityScale = 0.f;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxComponent"));
	SetRootComponent(BoxCollision);
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxCollision->SetCollisionObjectType(ECC_NonPhysical); // defined in NaniUtility.h
	BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AAuraProjectile::BeginPlay() {
	Super::BeginPlay();

	SetLifeSpan(ProjectileLifeSpan); //set timer instead // explode at end or skip timer if overlap

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AAuraProjectile::BoxCollisionBeginOverlap);
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AAuraProjectile::BoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor) {
		// Broadcasting Hit Actor
		OnProjectileHit.Broadcast(OtherActor);

		// Play Impact Effect
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
		// Play Impact Sound
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	}
	else {
		NANI_LOG(Error, "%s Projectile Overlap Error, Invlaid Overlapped Actor", *GetName());
	}
}