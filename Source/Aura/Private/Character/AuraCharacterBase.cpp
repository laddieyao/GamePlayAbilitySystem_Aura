// Copyright LaadieYao


#include "Character/AuraCharacterBase.h"

#include "Components/SkeletalMeshComponent.h"
#include "AbilitySystemComponent.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
	
}

void AAuraCharacterBase::InitializePrimaryAttributes() const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(DefaultPrimaryAttributes);

	// 调用ApplyGameplayEffectSpecToTarget需要创建GameplayEffectContext以及根据GameplayEffectContext创建的GameplayEffectSpecHandle
	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultPrimaryAttributes, 1.f, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

