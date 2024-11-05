// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AuraCharacterClassInfo.generated.h"

class UGameplayEffect;
class UGameplayAbility;

USTRUCT()
struct FCharacterClassSpecificInfo {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag CharacterClassTag;

	// Effect
	UPROPERTY(EditDefaultsOnly, Category = "ClassSpecificDefaults|Attributes")
	TSubclassOf<UGameplayEffect> Primary_AttributeDefaults = nullptr; //data in struct must be pointered or reffered

	// Ability
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TArray<TSubclassOf<UGameplayAbility>> ClassSpecificAbilities;
};

UCLASS()
class AURA_API UAuraCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()
	
protected:
	// ClassSpecific
	//UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults|Attributes|ClassSpecific")
	//TMap<FGameplayTag, FCharacterClassSpecificInfo> ClassSpecificInfo;

	UPROPERTY(EditDefaultsOnly, Category = "ClassSpecificDefaults")
	TArray<FCharacterClassSpecificInfo> ClassSpecificInfo;

public:
	// Common
	//// Effect
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults|Attributes")
	TSubclassOf<UGameplayEffect> Vital_AttributeDefaults;
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults|Attributes")
	TSubclassOf<UGameplayEffect> Secondary_AttributeDefaults;
	//// Ability
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults|Ability")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;

	// Getters
	TSubclassOf<UGameplayEffect> GetPrimaryAttributeDefaults(const FGameplayTag& ClassTag);
};
