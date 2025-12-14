// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Player/GC_Primary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTags/GCTags.h"

void UGC_Primary::SendHitReactEventToActors(const TArray<AActor*> ActorsHit)
{
	for (AActor* HitActor : ActorsHit)
	{
		FGameplayEventData Payload;
		Payload.Instigator = GetAvatarActorFromActorInfo();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, GCTags::Events::Enemy::HitReact, Payload);
	}
}
