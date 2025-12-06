// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GC_GameplayAbility.h"
#include "GC_Primary.generated.h"

/**
 * 
 */
UCLASS()
class GASCOURSE_API UGC_Primary : public UGC_GameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GC|Abilities")
	TArray<AActor*> HitBoxOverlapTest();
	
	UFUNCTION(BlueprintCallable, Category = "GC|Abilities")
	void SendHitReactEventToActors(const TArray<AActor*> ActorsHit);

private:
	void DrawHitboxOverlapDebugs(const TArray<FOverlapResult>& OverlapResults, const FVector& HitBoxLocation) const;
	
	UPROPERTY(EditDefaultsOnly, Category = "GC|Abilities")
	float HitBoxRadius = 100.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "GC|Abilities")
	float HitBoxForwardOffset = 200.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "GC|Abilities")
	float HitBoxElevationOffset = 20.f;

};
