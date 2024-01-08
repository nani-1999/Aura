// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h" //must be here, for FActiveGameplayEffectHandle
#include "AuraEffectActor.generated.h"

class UBoxComponent;
class UGameplayEffect;
class UAbilitySystemComponent;

UENUM()
enum class EEffectActorPolicy : uint8 {
	ApplyAndDestroy, //Apply Effect and Destroy on Overlap Begin
	ApplyAndRemove, // Apply Effect on Overlap Begin and Remove Effect on Overlap End
	DoNotApply // Do Not Apply Effect at all
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;
	
	// Collision
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> Box;

	// Effects
	UPROPERTY(EditAnywhere, Category = "Gameplay Effect")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;

	TMap<UAbilitySystemComponent*, FActiveGameplayEffectHandle> ActiveEffectHandles; //must include GameplayEffectTypes.h

	void ApplyEffectToTarget(AActor* Target, AActor* Context, TSubclassOf<UGameplayEffect> EffectClass);
	void RemoveEffectOnTarget(AActor* Target);

	// Policy
	UPROPERTY(EditAnywhere, Category = "Gameplay Effect")
	EEffectActorPolicy EffectActorPolicy;

	// Level
	UPROPERTY(EditAnywhere, Category = "Gameplay Effect")
	float ActorLevel;

public:	
	virtual void Tick(float DeltaTime) override;

	// Binds
	UFUNCTION()
	void BoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void BoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
