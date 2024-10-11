// Copyright LaadieYao


#include "AbilitySystem/Data/AttributeInfo.h"

/**
 * 根据AttributeTag参数返回AttributeInformation数组中保存的FAuraAttributeInfo结构体信息
 * @param AttributeTag 
 * @param bLogNotFound 
 * @return 
 */
FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FAuraAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}
	// 此时没有提前Return
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(),*GetNameSafe(this));
	}
	return FAuraAttributeInfo();
}