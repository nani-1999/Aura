// Copyright Na9i Studio 2024.


#include "AuraAssetManager.h"
#include "GameplayAbilitySystem/GameplayTags/AuraGameplayTags.h"

#include "Aura/Nani/NaniUtility.h"

UAuraAssetManager& UAuraAssetManager::Get() {
	check(GEngine);

	UAuraAssetManager* AuraAM = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AuraAM;
}

void UAuraAssetManager::StartInitialLoading() {
	Super::StartInitialLoading();
	UE_LOG(LogTemp, Warning, TEXT("%s | StartInitialLoading()"), *GetName());

	// called before world exist
	// used to setup values

	FAuraGameplayTags::AddNativeGameplayTags();
}


void UAuraAssetManager::PreBeginPIE(bool bStartSimulate) {
	Super::PreBeginPIE(bStartSimulate);
	UE_LOG(LogTemp, Warning, TEXT("%s | PreBeginPIE()"), *GetName());

	// called Before PIE loads
	// called before world exist

	FAuraGameplayTags::CopyNativeGameplayTags();
}