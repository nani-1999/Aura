// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UAuraAssetManager& Get();

	virtual void StartInitialLoading() override;
	//virtual void FinishInitialLoading() override;
	
protected:
	virtual void PreBeginPIE(bool bStartSimulate) override;
};
