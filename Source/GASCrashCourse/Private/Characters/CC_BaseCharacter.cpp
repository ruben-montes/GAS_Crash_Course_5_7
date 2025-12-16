// Copyright Mendeja Productions


#include "GASCrashCourse/Public/Characters/CC_BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

ACC_BaseCharacter::ACC_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Tick and refresh bone transforms whether rendered or not - for bone updates on a dedicated server
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

void ACC_BaseCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, bAlive);
}

UAbilitySystemComponent* ACC_BaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

void ACC_BaseCharacter::GiveStartupAbilities()
{
	if (!IsValid(GetAbilitySystemComponent())) return;

	for (const auto& Ability : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
		GetAbilitySystemComponent()->GiveAbility(AbilitySpec);
	}
}

void ACC_BaseCharacter::ApplyGameplayEffect(const TSubclassOf<UGameplayEffect> GameplayEffect) const
{
	checkf(IsValid(GameplayEffect), TEXT("GameplayEffect not set."));

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(
		GameplayEffect, 1.f, ContextHandle);

	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void ACC_BaseCharacter::InitializeAttributes()
{
	ApplyGameplayEffect(InitializeAttributesEffect);
}

void ACC_BaseCharacter::ResetAttributes()
{
	ApplyGameplayEffect(ResetAttributesEffect);
}

void ACC_BaseCharacter::OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData)
{
	if (AttributeChangeData.NewValue <= 0.0f)
	{
		HandleDeath();
	}
}

void ACC_BaseCharacter::HandleDeath()
{
	bAlive = false;

	if (IsValid(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,
		                                 FString::Printf(TEXT("%s has died!."),
		                                                 *GetName()));
	}
}

void ACC_BaseCharacter::HandleRespawn()
{
	bAlive = true;
}
