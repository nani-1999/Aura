// Copyright Na9i Studio 2024.


#include "GameplayAbilitySystem/GameplayTags/AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraAttributeTags FAuraGameplayTags::AttributeTags;
FAuraMessageTags FAuraGameplayTags::MessageTags;

void FAuraGameplayTags::AddNativeGameplayTags() {

	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();

	// Attribute Tags
	// Vital
	GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Vital.Health"));
	GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Vital.Mana"));
	// Primary
	GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Primary.Strength"));
	GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Primary.Intelligence"));
	GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Primary.Resilience"));
	GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Primary.Vigor"));
	// Secondary
	GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Secondary.Armor"));
	GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Secondary.ArmorPenetration"));
	GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Secondary.BlockChance"));
	GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Secondary.CriticalHitChance"));
	GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Secondary.CriticalHitDamage"));
	GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Secondary.CriticalHitResistance"));
	GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Secondary.HealthRegeneration"));
	GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Secondary.ManaRegeneration"));
	GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Secondary.MaxHealth"));
	GameplayTagsManager.AddNativeGameplayTag(FName("Attribute.Secondary.MaxMana"));

	// Pick Up
	GameplayTagsManager.AddNativeGameplayTag(FName("Message.PickUp.HealthPotion"));
	GameplayTagsManager.AddNativeGameplayTag(FName("Message.PickUp.HealthCrystal"));
	GameplayTagsManager.AddNativeGameplayTag(FName("Message.PickUp.ManaPotion"));
	GameplayTagsManager.AddNativeGameplayTag(FName("Message.PickUp.ManaShard"));
}

void FAuraGameplayTags::CopyNativeGameplayTags() {

	// Attribute Tags
	// Vital
	AttributeTags.Attribute_Vital_Health = FGameplayTag::RequestGameplayTag(FName("Attribute.Vital.Health"));
	AttributeTags.Attribute_Vital_Mana = FGameplayTag::RequestGameplayTag(FName("Attribute.Vital.Mana"));
	// Primary
	AttributeTags.Attribute_Primary_Strength = FGameplayTag::RequestGameplayTag(FName("Attribute.Primary.Strength"));
	AttributeTags.Attribute_Primary_Intelligence = FGameplayTag::RequestGameplayTag(FName("Attribute.Primary.Intelligence"));
	AttributeTags.Attribute_Primary_Resilience = FGameplayTag::RequestGameplayTag(FName("Attribute.Primary.Resilience"));
	AttributeTags.Attribute_Primary_Vigor = FGameplayTag::RequestGameplayTag(FName("Attribute.Primary.Vigor"));
	// Secondary
	AttributeTags.Attribute_Secondary_Armor = FGameplayTag::RequestGameplayTag(FName("Attribute.Secondary.Armor"));
	AttributeTags.Attribute_Secondary_ArmorPenetration = FGameplayTag::RequestGameplayTag(FName("Attribute.Secondary.ArmorPenetration"));
	AttributeTags.Attribute_Secondary_BlockChance = FGameplayTag::RequestGameplayTag(FName("Attribute.Secondary.BlockChance"));
	AttributeTags.Attribute_Secondary_CriticalHitChance = FGameplayTag::RequestGameplayTag(FName("Attribute.Secondary.CriticalHitChance"));
	AttributeTags.Attribute_Secondary_CriticalHitDamage = FGameplayTag::RequestGameplayTag(FName("Attribute.Secondary.CriticalHitDamage"));
	AttributeTags.Attribute_Secondary_CriticalHitResistance = FGameplayTag::RequestGameplayTag(FName("Attribute.Secondary.CriticalHitResistance"));
	AttributeTags.Attribute_Secondary_HealthRegeneration = FGameplayTag::RequestGameplayTag(FName("Attribute.Secondary.HealthRegeneration"));
	AttributeTags.Attribute_Secondary_ManaRegeneration = FGameplayTag::RequestGameplayTag(FName("Attribute.Secondary.ManaRegeneration"));
	AttributeTags.Attribute_Secondary_MaxHealth = FGameplayTag::RequestGameplayTag(FName("Attribute.Secondary.MaxHealth"));
	AttributeTags.Attribute_Secondary_MaxMana = FGameplayTag::RequestGameplayTag(FName("Attribute.Secondary.MaxMana"));

	// Pick Up
	MessageTags.Message_PickUp_HealthPotion = FGameplayTag::RequestGameplayTag(FName("Message.PickUp.HealthPotion"));
	MessageTags.Message_PickUp_HealthCrystal = FGameplayTag::RequestGameplayTag(FName("Message.PickUp.HealthCrystal"));
	MessageTags.Message_PickUp_ManaPotion = FGameplayTag::RequestGameplayTag(FName("Message.PickUp.ManaPotion"));
	MessageTags.Message_PickUp_ManaShard = FGameplayTag::RequestGameplayTag(FName("Message.PickUp.ManaShard"));
}