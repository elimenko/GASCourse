// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AbilityTasks/GC_WaitGameplayEvent.h"

void UGC_WaitGameplayEvent::StartActivation()
{
	Activate();
}

UGC_WaitGameplayEvent* UGC_WaitGameplayEvent::WaitGameplayEventToActorProxy(AActor* TargetActor, FGameplayTag EventTag,
	bool OnlyTriggerOnce, bool OnlyMatchExact)
{
	UGC_WaitGameplayEvent* MyObj = NewObject<UGC_WaitGameplayEvent>();
	MyObj->SetAbilityActor(TargetActor);
	MyObj->Tag = EventTag;
	MyObj->OnlyTriggerOnce = OnlyTriggerOnce;
	MyObj->OnlyMatchExact = OnlyMatchExact;
	return MyObj;
}
