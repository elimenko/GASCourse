// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/GC_BlueprintLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/GC_AttributeSet.h"
#include "Characters/GC_BaseCharacter.h"
#include "GameplayTags/GCTags.h"
#include "Kismet/GameplayStatics.h"

EHitDirection UGC_BlueprintLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
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
	return EHitDirection::Forward;
}

FName UGC_BlueprintLibrary::GetHitDirectionName(const EHitDirection HitDirection)
{
	switch (HitDirection)
	{
		case EHitDirection::Left: return FName("Left");
		case EHitDirection::Right: return FName("Right");
		case EHitDirection::Back: return FName("Back");
		case EHitDirection::Forward: return FName("Forward");
		default: return FName("None");
	}
}

FClosestActorWithTagResult UGC_BlueprintLibrary::FindClosestActorWithTag(const UObject* WorldContextObject, const FVector& Origin, const FName& Tag)
{
	TArray<AActor*> ActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(WorldContextObject, Tag, ActorsWithTag);

	float ClosestDistance = TNumericLimits<float>::Max();
	AActor* ClosestActor = nullptr;

	for (AActor* Actor : ActorsWithTag)
	{
		if (!IsValid(Actor)) continue;
		AGC_BaseCharacter* BaseCharacter = Cast<AGC_BaseCharacter>(Actor);
		if (!IsValid(BaseCharacter) || !BaseCharacter->IsAlive()) continue;
		
		const float Distance = FVector::Dist(Origin, Actor->GetActorLocation());
		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ClosestActor = Actor;
		}
	}

	FClosestActorWithTagResult Result;
	Result.Actor = ClosestActor;
	Result.Distance = ClosestDistance;
	
	return Result;
}

void UGC_BlueprintLibrary::SendDamageEventToPlayer(AActor* Target, const TSubclassOf<UGameplayEffect>& DamageEffect,
	const FGameplayEventData& Payload, const FGameplayTag& DataTag, float Damage)
{
	AGC_BaseCharacter* PlayerCharacter = Cast<AGC_BaseCharacter>(Target);
	if (!IsValid(PlayerCharacter)) return;
	if (!PlayerCharacter->IsAlive()) return;

	UGC_AttributeSet* AttributeSet = Cast<UGC_AttributeSet>(PlayerCharacter->GetAttributeSet());
	if (!IsValid(AttributeSet)) return;

	const bool bLethal = AttributeSet->GetHealth() - Damage <= 0.f;
	const FGameplayTag EventTag= bLethal ? GCTags::Events::Player::Death : GCTags::Events::Player::HitReact;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(PlayerCharacter, EventTag, Payload);

	UAbilitySystemComponent* TargetASC = PlayerCharacter->GetAbilitySystemComponent();
	if (!IsValid(TargetASC)) return;

	FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(DamageEffect, 1.f, ContextHandle);

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DataTag, -Damage);

	TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}
