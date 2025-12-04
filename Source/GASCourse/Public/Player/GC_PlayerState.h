// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"

#include "GC_PlayerState.generated.h"

class UAbilitySystemComponent;

UCLASS()
class GASCOURSE_API AGC_PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGC_PlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

private:
	UPROPERTY(VisibleAnywhere, Category = "GC|Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};
