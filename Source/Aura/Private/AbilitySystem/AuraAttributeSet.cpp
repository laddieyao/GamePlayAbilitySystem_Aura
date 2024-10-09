// Copyright LaadieYao


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "Engine/Engine.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(40.f);
	InitMaxMana(50.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// REPNOTIFY_Always 将其设定为旧有的相同值，也会进行复制
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}



/**
 * 在AttributeChange生效前调用的函数，NewValue是这次改变后的新值
 * @param Attribute 
 * @param NewValue 
 */
void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if(Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if(Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}

	// if(Attribute == GetHealthAttribute())
	// {
	// 	// GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, FString::Printf(TEXT("HealthBaseValue: %f"),
	// 	// 	GetHealthAttribute().GetGameplayAttributeData(this)->GetBaseValue()));
	// 	// GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, FString::Printf(TEXT("HealthCurrentValue: %f"),
	// 	// 	GetHealthAttribute().GetGameplayAttributeData(this)->GetCurrentValue()));
	// 	UE_LOG(LogTemp, Warning, TEXT("HealthBaseValue: %f"),
	// 		GetHealthAttribute().GetGameplayAttributeData(this)->GetBaseValue());
	// 	UE_LOG(LogTemp, Warning, TEXT("HealthCurrentValue: %f"),
	// 		GetHealthAttribute().GetGameplayAttributeData(this)->GetCurrentValue());
	// }
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	// Source = causer of the effect, Target = target of the effect (owner of this AS)
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			ACharacter* SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}


/**
 * 
 * @param Data 
 */
void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	// 在此处限制Health和Mana在合理范围内，限制的是BaseValue
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}

	// if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	// {
	// 	// GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, FString::Printf(TEXT("HealthBaseValue: %f"),
	// 	// 	GetHealthAttribute().GetGameplayAttributeData(this)->GetBaseValue()));
	// 	// GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, FString::Printf(TEXT("HealthCurrentValue: %f"),
	// 	// 	GetHealthAttribute().GetGameplayAttributeData(this)->GetCurrentValue()));
	// 	UE_LOG(LogTemp, Warning, TEXT("HealthBaseValue: %f"),
	// 		GetHealthAttribute().GetGameplayAttributeData(this)->GetBaseValue());
	// 	UE_LOG(LogTemp, Warning, TEXT("HealthCurrentValue: %f"),
	// 		GetHealthAttribute().GetGameplayAttributeData(this)->GetCurrentValue());
	// }
}