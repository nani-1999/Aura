// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAppliedEffectTagsDelegate, const FGameplayTagContainer&, Tags);

UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()


public:
	// Is this ASC Locally Owned
	bool IsLocalASC();

	// Called Locally whenever a GE is applied to self/target
	FAppliedEffectTagsDelegate OnAppliedEffectAssetTags;
};
