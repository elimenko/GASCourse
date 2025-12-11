// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GC_GameplayAbility.h"
#include "GC_SearchForTarget.generated.h"

namespace EPathFollowingResult
{
	enum Type : int;
}

class AGC_BaseCharacter;
class UGC_WaitGameplayEvent;
class AAIController;
class AGC_EnemyCharacter;
class UAbilityTask_WaitDelay;
class UAITask_MoveTo;

UCLASS()
class GASCOURSE_API UGC_SearchForTarget : public UGC_GameplayAbility
{
	GENERATED_BODY()

public:
	UGC_SearchForTarget();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	TWeakObjectPtr<AGC_EnemyCharacter> OwningEnemy;
	TWeakObjectPtr<AAIController> OwningAIController;
	TWeakObjectPtr<AGC_BaseCharacter> TargetBaseCharacter;

private:
	UPROPERTY()
	TObjectPtr<UGC_WaitGameplayEvent> WaitGameplayEventTask;

	UPROPERTY()
	TObjectPtr<UAbilityTask_WaitDelay> SearchDelayTask;

	UPROPERTY()
	TObjectPtr<UAITask_MoveTo> MoveToLocationOrActorTask;
	
	UPROPERTY()
	TObjectPtr<UAbilityTask_WaitDelay> AttackDelayTask;
	
	UFUNCTION()
	void EndAttackEventReceived(FGameplayEventData Payload);

	UFUNCTION()
	void Search();

	UFUNCTION()
	void AttackTarget(TEnumAsByte<EPathFollowingResult::Type> Result, AAIController* AIController);

	UFUNCTION()
	void Attack();

	void StartSearch();
	void MoveToTargetAndAttack();
};
