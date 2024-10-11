// Copyright LaadieYao


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGameplayTags.h"
#include "Engine/Engine.h"

/**
 * 进行一些委托的绑定
 */ 
void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}
void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
												const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagsContainer;
	EffectSpec.GetAllAssetTags(TagsContainer);
	
	// 在此进行广播
	EffectAssetTags.Broadcast(TagsContainer);
}
