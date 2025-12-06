// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GC_BaseCharacter.h"
#include "GC_EnemyCharacter.generated.h"

class UAbilitySystemComponent;

UCLASS()
class GASCOURSE_API AGC_EnemyCharacter : public AGC_BaseCharacter
{
	GENERATED_BODY()

public:
	AGC_EnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "GC|Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
};
