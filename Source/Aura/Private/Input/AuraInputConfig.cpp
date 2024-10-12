// Copyright LaadieYao


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag Tag, bool bLogNotFound) const
{
	for (const auto& [InputAction, InputTag] : AbilityInputActions)
	{
		if(InputAction != nullptr && InputTag == Tag)
		{
			return InputAction;
		}
	}
	if(bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't Find InputAction For The Tag! [%s], On InputConfig [%s]"), *Tag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
