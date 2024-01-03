// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UGameplayEffect;

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;

	// Mesh
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	// Collision
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	// Effects
	UPROPERTY(EditAnywhere, Category = "Gameplay Effect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);

public:	
	virtual void Tick(float DeltaTime) override;

	// Binds
	UFUNCTION()
	void SphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
