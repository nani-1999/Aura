// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraProjectile.generated.h"

class UProjectileMovementComponent;
class UBoxComponent;
class UNiagaraSystem;
class UImpactSound;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FProjectileHitActorDelegate, AActor*, HitActor);

UCLASS()
class AURA_API AAuraProjectile : public AActor
{
	GENERATED_BODY()

public:
	AAuraProjectile();

protected:
	virtual void BeginPlay() override;

	// Components
	UPROPERTY()
	TObjectPtr<UProjectileMovementComponent> ProjectileComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults | GFX")
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults | SFX")
	TObjectPtr<USoundBase> ImpactSound;

	// Callbacks
	UFUNCTION()
	void BoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	// Delegate
	UPROPERTY()
	FProjectileHitActorDelegate OnProjectileHit;

	// UserData
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults")
	float ProjectileLifeSpan;
};