// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "EffectActor.generated.h"

UENUM()
enum class EEffectPolicy : uint8 {
	//EEP_Apply,           //ApplyEffect OnOverlapBegin
	EEP_ApplyAndDestroy,   //ApplyEffect OnOverlapBegin and Destroy Immediately
	EEP_ApplyAndRemove,    //ApplyEffect OnOverlapBegin and RemoveEffect OnOverlapEnd
	EEP_None,              //disables collision
	EEP_MAX
};

class UBoxComponent;
class UGameplayEffect;
struct FActiveGameplayEffectHandle;
class UAbilitySystemComponent;

UCLASS()
class AURA_API AEffectActor : public AActor
{
	GENERATED_BODY()
	
public:
	AEffectActor();

protected:
	virtual void BeginPlay() override;

	// BoxCollision
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxCollision;

	UFUNCTION()
	void BoxCollisionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void BoxCollisionOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Effect Policy
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults | EffectPolicy")
	EEffectPolicy EffectPolicy;

	// GameplayEffect
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults | Effect")
	TSubclassOf<UGameplayEffect> EffectBP;

	UPROPERTY()
	TMap<UAbilitySystemComponent*, FActiveGameplayEffectHandle> ActiveEffects;

	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults | EffectLevel")
	float EffectLevel;
};
