// Copyright Na9i Studio 2024.


#include "DataAsset/AuraCharacterClassInfo.h"
#include "GameplayEffect.h"
#include "Abilities/GameplayAbility.h"

TSubclassOf<UGameplayEffect> UAuraCharacterClassInfo::GetPrimaryAttributeDefaults(const FGameplayTag& ClassTag) {
	for (FCharacterClassSpecificInfo& Info : ClassSpecificInfo) {
		if (Info.CharacterClassTag.MatchesTagExact(ClassTag)) {
			return Info.Primary_AttributeDefaults;
		}
	}
	checkf(false, TEXT("AuraCharacterClassInfo | Unable to Find PrimaryAttributeDefaults for CharacterClassTag: %s"), *ClassTag.ToString());
	return nullptr;
}