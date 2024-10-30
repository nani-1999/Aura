// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AuraCharacterClassInfo.generated.h"

class UGameplayEffect;

USTRUCT()
struct FCharacterClassSpecificInfo {
	GENERATED_BODY()

	// Effect
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults|AttributeDefaults")
	TSubclassOf<UGameplayEffect> Primary_AttributeDefaults = nullptr; //data in struct must be pointered or reffered
};

UCLASS()
class AURA_API UAuraCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// Common
	//// Effect
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults|AttributeDefaults")
	TSubclassOf<UGameplayEffect> Vital_AttributeDefaults;
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults|AttributeDefaults")
	TSubclassOf<UGameplayEffect> Secondary_AttributeDefaults;

	// ClassSpecific
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults|AttributeDefaults|ClassSpecific")
	TMap<FGameplayTag, FCharacterClassSpecificInfo> ClassSpecificInfo;

	// Getters
	TSubclassOf<UGameplayEffect>& GetPrimaryAttributeDefaults(const FGameplayTag& CharacterClassTag);
};
