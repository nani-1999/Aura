// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController; //Widget doesn't need to know WidgetController, because includes and effeciency 

	FORCEINLINE void SetWidgetController(UObject* NewWidgetController) { WidgetController = NewWidgetController; }
	FORCEINLINE UObject* GetWidgetController() const { return WidgetController; }
};
