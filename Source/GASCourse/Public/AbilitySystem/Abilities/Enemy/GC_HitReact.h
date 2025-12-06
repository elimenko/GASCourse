// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GC_GameplayAbility.h"
#include "GC_HitReact.generated.h"

/**
 * 
 */
UCLASS()
class GASCOURSE_API UGC_HitReact : public UGC_GameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GC|Abilities")
	void CacheHitDirectionVectors(AActor* Instigator);
	
	UPROPERTY(BlueprintReadOnly, Category = "GC|Abilities")
	FVector AvatarForward;

	UPROPERTY(BlueprintReadOnly, Category = "GC|Abilities")
	FVector ToInstigator;
};
