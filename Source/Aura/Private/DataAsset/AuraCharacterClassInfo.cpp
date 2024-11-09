// Copyright Na9i Studio 2024.


#include "DataAsset/AuraCharacterClassInfo.h"
#include "GameplayEffect.h"
#include "Abilities/GameplayAbility.h"

FCharacterClassSpecificInfo& UAuraCharacterClassInfo::GetCharacterClassSpecificInfo(const FGameplayTag& ClassTag) {
	for (FCharacterClassSpecificInfo& Info : ClassSpecificInfo) {
		if (Info.CharacterClassTag.MatchesTagExact(ClassTag)) return Info;
	}
	checkf(false, TEXT("AuraCharacterClassInfo | Not a Valid CharacterClass Tag when Accessing FCharacterClassSpecificInfo"));
	return ClassSpecificInfo[0];
}