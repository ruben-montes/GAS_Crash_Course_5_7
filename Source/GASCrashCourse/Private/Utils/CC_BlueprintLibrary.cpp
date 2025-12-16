// Copyright Mendeja Productions


#include "Utils/CC_BlueprintLibrary.h"

#include "Characters/CC_BaseCharacter.h"
#include "Kismet/GameplayStatics.h"

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

FClosestActorWithTagResult UCC_BlueprintLibrary::FindClosestActorWithTag(const UObject* WorldContextObject,
                                                                         const FVector& Origin, const FName& Tag)
{
	TArray<AActor*> ActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(WorldContextObject, Tag, ActorsWithTag);

	float CLosestDistance = TNumericLimits<float>::Max();
	AActor* ClosestActor = nullptr;

	for (AActor* Actor : ActorsWithTag)
	{
		if (!IsValid(Actor)) continue;
		ACC_BaseCharacter* BaseCharacter = Cast<ACC_BaseCharacter>(Actor);
		if (!IsValid(BaseCharacter) || !BaseCharacter->IsAlive()) continue;

		const float Distance = FVector::Dist(Origin, Actor->GetActorLocation());
		if (Distance <= CLosestDistance)
		{
			CLosestDistance = Distance;
			ClosestActor = Actor;
		}
	}

	FClosestActorWithTagResult Result;
	Result.Actor = ClosestActor;
	Result.Distance = CLosestDistance;

	return Result;
}
