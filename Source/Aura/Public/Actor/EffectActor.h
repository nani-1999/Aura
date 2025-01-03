// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h" // @For FActiveGameplayEffectHandle
#include "EffectActor.generated.h"

UENUM()
enum class EEffectApplicationPolicy : uint8 {
	//EEAP_Apply,                        //ApplyEffect OnOverlapBegin
	//EEAP_ApplyAndDestroyOrWaitDestroy, //ApplyEffect And Destroy OnOverlapBegin Or Destroy itself after sometime
	EEAP_ApplyAndDestroy,                //ApplyEffect And Destroy OnOverlapBegin
	EEAP_ApplyAndRemove,                 //ApplyEffect OnOverlapBegin and RemoveEffect OnOverlapEnd
	EEAP_None                            //disables collision
};

class UBoxComponent;
class UGameplayEffect;
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

	// Overlap
	UFUNCTION()
	void BoxCollisionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwEEAP, const FHitResult& SwEEAPResult) { OverlapBeginActor(OtherActor); }
	UFUNCTION()
	void BoxCollisionOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) { OverlapEndActor(OtherActor); }
	virtual void OverlapBeginActor(AActor* OverlapActor);
	virtual void OverlapEndActor(AActor* OverlapActor);

	// Effect Policy
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults | EffectPolicy")
	EEffectApplicationPolicy EffectApplicationPolicy;

	// GameplayEffect
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults | Effect")
	TSubclassOf<UGameplayEffect> EffectBP;

	void ApplyEffectToTargetASC(UAbilitySystemComponent* TargetASC);

	UPROPERTY()
	TMap<UAbilitySystemComponent*, FActiveGameplayEffectHandle> ActiveEffects;

	void BroadcastAssetTagsToTargetASC(UAbilitySystemComponent* TargetASC);

	// Effect Level
	UPROPERTY(EditAnywhere, Category = "ClassDefaults | EffectLevel")
	float EffectLevel;
};
