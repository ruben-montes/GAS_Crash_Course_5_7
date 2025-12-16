// Copyright Mendeja Productions


#include "UI/CC_AttributeWidget.h"

void UCC_AttributeWidget::OnAttributeChanged(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair,
                                             UCC_AttributeSet* AttributeSet)
{
	const float AttributeValue = Pair.Key.GetNumericValue(AttributeSet);
	const float MaxAttributeValue = Pair.Value.GetNumericValue(AttributeSet);

	BP_OnAttributeChanged(AttributeValue, MaxAttributeValue);
}

bool UCC_AttributeWidget::MatchesAttributes(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	return Attribute == Pair.Key && MaxAttribute == Pair.Value;
}
