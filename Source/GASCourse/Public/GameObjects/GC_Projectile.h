// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GC_Projectile.generated.h"

class UProjectileMovementComponent;
class UGameplayEffect; 

UCLASS()
class GASCOURSE_API AGC_Projectile : public AActor
{
	GENERATED_BODY()

public:
	AGC_Projectile();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GC|Damage", meta = (ExposeOnSpawn, ClampMin = "0.0"));
	float Damage{-20.f};
	
	UFUNCTION(BlueprintImplementableEvent, Category = "GC|Projectile")
	void SpawnImpactEffects();

private:
	UPROPERTY(VisibleAnywhere, Category = "GC|Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, Category = "GC|Damage")
	TSubclassOf<UGameplayEffect> DamageEffect;
};
