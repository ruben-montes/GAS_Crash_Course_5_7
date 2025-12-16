// Copyright Mendeja Productions


#include "Utils/CC_BlueprintLibrary.h"

EHitDirection UCC_BlueprintLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
{
	const float Dot = FVector::DotProduct(TargetForward, ToInstigator);
	if (Dot < -0.5f)
	{
		return EHitDirection::Back;
	}

	if (Dot < 0.5f)
	{
		// Either left or right
		const FVector Cross = FVector::CrossProduct(TargetForward, ToInstigator);
		return Cross.Z < 0.f ? EHitDirection::Left : EHitDirection::Right;
	}

	return EHitDirection::Front;
}

FName UCC_BlueprintLibrary::GetHitDirectionName(const EHitDirection& HitDirection)
{
	switch (HitDirection)
	{
	case EHitDirection::Left:
		return FName("Left");
	case EHitDirection::Right:
		return FName("Right");
	case EHitDirection::Back:
		return FName("Back");
	case EHitDirection::Front:
		return FName("Front");
	default: return FName("None");
	}
}
