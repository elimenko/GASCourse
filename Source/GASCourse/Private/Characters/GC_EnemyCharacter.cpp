// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GC_EnemyCharacter.h"

#include "AbilitySystem/GC_AbilitySystemComponent.h"

AGC_EnemyCharacter::AGC_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UGC_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

UAbilitySystemComponent* AGC_EnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGC_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(AbilitySystemComponent)) return;

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	if (!HasAuthority()) return;

	GiveStartupAbilities();
}
