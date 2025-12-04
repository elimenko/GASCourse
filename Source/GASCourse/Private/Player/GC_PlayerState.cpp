// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GC_PlayerState.h"
#include "AbilitySystemComponent.h"

AGC_PlayerState::AGC_PlayerState()
{
	// By default player state updates only once per second. For GAS it's too slow
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}
