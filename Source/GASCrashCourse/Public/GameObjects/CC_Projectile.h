// Copyright Mendeja Productions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CC_Projectile.generated.h"

class UGameplayEffect;
class UProjectileMovementComponent;

UCLASS()
class GASCRASHCOURSE_API ACC_Projectile : public AActor
{
	GENERATED_BODY()

public:
	ACC_Projectile();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Crash|Projectile")
	void SpawnImpactEffects();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crash|Damage", meta = (ExposeOnSpawn, ClampMin = "0.0"))
	float Damage{-25.f};

private:
	UPROPERTY(VisibleAnywhere, Category = "Crash|Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, Category = "Crash|Damage")
	TSubclassOf<UGameplayEffect> DamageEffect;
};
