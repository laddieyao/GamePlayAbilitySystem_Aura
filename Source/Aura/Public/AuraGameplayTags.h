// Copyright LaadieYao

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * AuraGameplayTags
 *
 * Singleton containing native Gameplay Tags
 */
struct FAuraGameplayTags
{
public:
	FORCEINLINE static FAuraGameplayTags& Get()
	{
		static FAuraGameplayTags Instance;
		return Instance;
	}
	static void InitializeNativeGameplayTags();
	FGameplayTag Attributes_Secondary_Armor;
protected:
private:
	// static FAuraGameplayTags GameplayTags;
};