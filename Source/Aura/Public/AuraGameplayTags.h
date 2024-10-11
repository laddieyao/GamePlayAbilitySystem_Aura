// Copyright LaadieYao

#pragma once

#include "CoreMinimal.h"

/**
 * AuraGameplayTags
 *
 * Singleton containing native Gameplay Tags
 */
struct FAuraGameplayTags
{
public:
	FORCEINLINE static const FAuraGameplayTags& Get()
	{
		static FAuraGameplayTags Instance;
		return Instance;
	}
	static void InitializeNativeGameplayTags();
protected:
private:
	// static FAuraGameplayTags GameplayTags;
};