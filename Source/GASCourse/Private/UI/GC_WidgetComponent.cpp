// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GC_WidgetComponent.h"

#include "AbilitySystem/GC_AbilitySystemComponent.h"
#include "AbilitySystem/GC_AttributeSet.h"
#include "Blueprint/WidgetTree.h"
#include "Characters/GC_BaseCharacter.h"
#include "UI/GC_AttributeWidget.h"


void UGC_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystemData();

	if (!IsASCInitialized())
	{
		BaseCharacter->OnASCInitialized.AddDynamic(this, &ThisClass::OnASCInitialized);
		return;
	}

	InitializeAttributeDelegate();
}

void UGC_WidgetComponent::InitAbilitySystemData()
{
	BaseCharacter = Cast<AGC_BaseCharacter>(GetOwner());
	AttributeSet = Cast<UGC_AttributeSet>(BaseCharacter->GetAttributeSet());
	AbilitySystemComponent = Cast<UGC_AbilitySystemComponent>(BaseCharacter->GetAbilitySystemComponent());
}

bool UGC_WidgetComponent::IsASCInitialized() const
{
	return AbilitySystemComponent.IsValid() && AttributeSet.IsValid();
}

void UGC_WidgetComponent::InitializeAttributeDelegate()
{
	if (!AttributeSet->bAttributesInitialized)
	{
		AttributeSet->OnAttributesInitialized.AddDynamic(this, &ThisClass::BindToAttributeChanges);
	}
	else
	{
		BindToAttributeChanges();
	}
}

void UGC_WidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AbilitySystemComponent = Cast<UGC_AbilitySystemComponent>(ASC);
	AttributeSet = Cast<UGC_AttributeSet>(AS);

	if (!IsASCInitialized()) return;
	InitializeAttributeDelegate();
}

void UGC_WidgetComponent::BindToAttributeChanges()
{
	for (const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair : AttributeMap)
	{
		BindWidgetToAttributeChanges(GetUserWidgetObject(), Pair); // for checking the owned widget object.
		
		// Otherwidse, loop over all children
		GetUserWidgetObject()->WidgetTree->ForEachWidget([this, Pair](UWidget* ChildWidget)
		{
			BindWidgetToAttributeChanges(ChildWidget, Pair);
		});
	}
}

void UGC_WidgetComponent::BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	// Check the user widget object owned by this component, see if it is a GC_AttributeWidget, handle it if so.
	UGC_AttributeWidget* AttributeWidget = Cast<UGC_AttributeWidget>(WidgetObject);
	if (!IsValid(AttributeWidget)) return;
	if (!AttributeWidget->MatchesAttributes(Pair)) return;
	AttributeWidget->AvatarActor = BaseCharacter;

	AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get(), 0.f); // for initial values

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda([this, AttributeWidget, Pair](const FOnAttributeChangeData& AttributeChangeData)
	{
		AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get(), AttributeChangeData.OldValue);
	});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value).AddLambda([this, AttributeWidget, Pair](const FOnAttributeChangeData& AttributeChangeData)
	{
		AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get(), AttributeChangeData.OldValue);
	});
}
