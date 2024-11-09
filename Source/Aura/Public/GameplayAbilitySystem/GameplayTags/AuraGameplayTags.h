// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/*
* Native GameplayTags
*/

struct FAuraAttributeTags {
	FGameplayTag Attribute_Parent;
	// Vital
	FGameplayTag Attribute_Vital_Health;
	FGameplayTag Attribute_Vital_Mana;
	// Primary
	FGameplayTag Attribute_Primary_Strength;
	FGameplayTag Attribute_Primary_Intelligence;
	FGameplayTag Attribute_Primary_Resilience;
	FGameplayTag Attribute_Primary_Vigor;
	// Secondary
	FGameplayTag Attribute_Secondary_Armor;
	FGameplayTag Attribute_Secondary_ArmorPenetration;
	FGameplayTag Attribute_Secondary_BlockChance;
	FGameplayTag Attribute_Secondary_CriticalHitChance;
	FGameplayTag Attribute_Secondary_CriticalHitDamage;
	FGameplayTag Attribute_Secondary_CriticalHitResistance;
	FGameplayTag Attribute_Secondary_HealthRegeneration;
	FGameplayTag Attribute_Secondary_ManaRegeneration;
	FGameplayTag Attribute_Secondary_MaxHealth;
	FGameplayTag Attribute_Secondary_MaxMana;
};
struct FAuraMessageTags {
	FGameplayTag Message_Parent;
	// Pick Up
	FGameplayTag Message_PickUp_Parent;
	FGameplayTag Message_PickUp_HealthPotion;
	FGameplayTag Message_PickUp_HealthCrystal;
	FGameplayTag Message_PickUp_ManaPotion;
	FGameplayTag Message_PickUp_ManaShard;
	// Quest
	FGameplayTag Message_Quest_Parent;
	FGameplayTag Message_Quest_Beginner;
};
struct FAuraCharacterClassTags {
	FGameplayTag CharacterClass_Parent;
	FGameplayTag CharacterClass_Elementalist;
	FGameplayTag CharacterClass_Ranger;
	FGameplayTag CharacterClass_Warrior;
};
struct FAuraAbilityTags {
	FGameplayTag Ability_Parent;
	FGameplayTag Ability_HitReact;
	FGameplayTag Ability_FireBall;
};
struct FAuraInputTags {
	FGameplayTag Input_Parent;
	FGameplayTag Input_1;
	FGameplayTag Input_2;
	FGameplayTag Input_3;
};

struct FAuraGameplayTags {
private:
	static FAuraAttributeTags AttributeTags;
	static FAuraMessageTags MessageTags;
	static FAuraCharacterClassTags CharacterClassTags;
	static FAuraAbilityTags AbilityTags;
	static FAuraInputTags InputTags;

public:
	/** Do not call this, can only be called by UAssetManager on InitialLoading */
	static void AddNativeGameplayTags();
	/** Do not call this, automatically called by UAssetManager when PIE starts */
	static void CopyNativeGameplayTags();

	static const FAuraAttributeTags& GetAttributeTags() { return AttributeTags; }
	static const FAuraMessageTags& GetMessageTags() { return MessageTags; }
	static const FAuraCharacterClassTags& GetCharacterClassTags() { return CharacterClassTags; }
	static const FAuraAbilityTags& GetAbilityTags() { return AbilityTags; }
	static const FAuraInputTags& GetInputTags() { return InputTags; }
};