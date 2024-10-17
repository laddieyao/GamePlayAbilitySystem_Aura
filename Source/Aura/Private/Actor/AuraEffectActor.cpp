// Copyright LaadieYao


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}



void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	// 如果目标是Enemy，而且此效果不对Enemy有效，那么直接返回
	if(const bool bIsEnemy = TargetActor->ActorHasTag(FName("Enemy")); bIsEnemy && !bApplyEffectsToEnemies) return;
	
	UAbilitySystemComponent* TargetASC =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if(TargetASC == nullptr) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	
	const bool bIsInfinite = EffectSpecHandle.Data->Def->DurationPolicy == EGameplayEffectDurationType::Infinite;
	// if(bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	// {
	// 	ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	// }
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		const auto UID = TargetActor->GetUniqueID();
		ActiveInfiniteEffects.Add(UID, ActiveEffectHandle);
	}

	if (bDestroyOnEffectApplication && !bIsInfinite)
	{
		Destroy();
	}

}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	// 如果目标是Enemy，而且此效果不对Enemy有效，那么直接返回
	if(const bool bIsEnemy = TargetActor->ActorHasTag(FName("Enemy")); bIsEnemy && !bApplyEffectsToEnemies) return;
	if(InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	// 如果目标是Enemy，而且此效果不对Enemy有效，那么直接返回
	if(const bool bIsEnemy = TargetActor->ActorHasTag(FName("Enemy")); bIsEnemy && !bApplyEffectsToEnemies) return;
	if(InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		const auto UID = TargetActor->GetUniqueID();
		if (!ActiveInfiniteEffects.Contains(UID)) return;
 
		const auto &EffectHandle = ActiveInfiniteEffects[UID];
		if (!TargetASC->RemoveActiveGameplayEffect(EffectHandle, 1)) return;
 
		ActiveInfiniteEffects.Remove(UID);
		
		// if (!IsValid(TargetASC)) return;
		// TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		// for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
		// {
		// 	if (TargetASC == HandlePair.Value)
		// 	{
		// 		TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
		// 		HandlesToRemove.Add(HandlePair.Key);
		// 	}
		// }
		// for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
		// {
		// 	ActiveEffectHandles.FindAndRemoveChecked(Handle);
		// }
	}
}

