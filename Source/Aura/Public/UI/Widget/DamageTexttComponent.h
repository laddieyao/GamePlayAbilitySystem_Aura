// Copyright LaddieYao

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageTexttComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UDamageTexttComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetDamageText(float Damage);
};
