// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GC_BaseCharacter.generated.h"

class UGameplayAbility;

UCLASS(Abstract)
class GASCOURSE_API AGC_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGC_BaseCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return nullptr; }

protected:
	void GiveStartupAbilities();

private:
	UPROPERTY(EditDefaultsOnly, Category = "GC|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

};
