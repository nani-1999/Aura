// Copyright Na9i Studio 2024.


#include "DataAsset/AuraCharacterClassInfo.h"
#include "GameplayEffect.h"

TSubclassOf<UGameplayEffect>& UAuraCharacterClassInfo::GetPrimaryAttributeDefaults(const FGameplayTag& CharacterClassTag) {
	return ClassSpecificInfo.FindChecked(CharacterClassTag).Primary_AttributeDefaults;
}
