// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h" // @For FActiveGameplayEffectHandle
#include "AuraEffectActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UAbilitySystemComponent;
class UGameplayEffect;

UENUM()
enum class EEffectPolicy : uint8 {
	//EEP_Apply,           //ApplyEffect OnOverlapBegin
	EEP_ApplyAndDestroy, //ApplyEffect OnOverlapBegin and Destroy Immediately
	EEP_ApplyAndRemove,  //ApplyEffect OnOverlapBegin and RemoveEffect OnOverlapEnd
	EEP_None,
	EEP_MAX
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	TObjectPtr<UBoxComponent> BoxCollision;

	UFUNCTION()
	void BoxCollisionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void BoxCollisionOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Gameplay Effect
	void ApplyEffectOnASC(TSubclassOf<UGameplayEffect> Effect, UAbilitySystemComponent* ASC);
	void RemoveEffectOnASC(UAbilitySystemComponent* ASC);
public:
	UPROPERTY(EditAnywhere, Category = "Ability System")
	TSubclassOf<UGameplayEffect> EffectBP;

	UPROPERTY(EditAnywhere, Category = "Ability System")
	float EffectLevel;

	UPROPERTY(EditAnywhere, Category = "Ability System")
	EEffectPolicy EffectPolicy;

	UPROPERTY(VisibleAnywhere, Category = "Ability System")
	TMap<UAbilitySystemComponent*, FActiveGameplayEffectHandle> ActiveEffectHandles; //effect per percollision, if applying two or more effects
};
