// Copyright Mendeja Productions

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "AttributeSet.h"
#include "CC_WidgetComponent.generated.h"


class UCC_AttributeSet;
class UCC_AbilitySystemComponent;
class ACC_BaseCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GASCRASHCOURSE_API UCC_WidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TMap<FGameplayAttribute, FGameplayAttribute> AttributeMap;

private:
	TWeakObjectPtr<ACC_BaseCharacter> CrashCharacter;
	TWeakObjectPtr<UCC_AbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<UCC_AttributeSet> AttributeSet;

	void InitAbilitySystemData();
	bool IsASCInitialized() const;
	void InitializeAttributeDelegate();
	void BindWidgetToAttributeChanges(UWidget* WidgetObject,
	                                  const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;

	UFUNCTION()
	void OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UFUNCTION()
	void BindToAttributeChanges();
};
