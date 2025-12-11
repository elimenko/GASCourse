// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/ANS_MeleeAttack.h"

#include "AbilitySystemComponent.h"
#include "Characters/GC_BaseCharacter.h"
#include "Characters/GC_PlayerCharacter.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "KismetTraceUtils.h"
#include "GameplayTags/GCTags.h"
#include "Kismet/KismetMathLibrary.h"

void UANS_MeleeAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
                                  const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (!IsValid(MeshComp)) return;
	if (!IsValid(MeshComp->GetOwner())) return;

	TArray<FHitResult> HitResults = PerformSphereTrace(MeshComp);
	SendEventsToActors(HitResults, MeshComp);
}

TArray<FHitResult> UANS_MeleeAttack::PerformSphereTrace(USkeletalMeshComponent* MeshComp) const
{
	FTransform SocketTransform = MeshComp->GetSocketTransform(SocketName);
	FVector TraceStart = SocketTransform.GetLocation();
	FVector ExtendedSocketDirection = UKismetMathLibrary::GetForwardVector(SocketTransform.GetRotation().Rotator()) * SocketExtensionOffset;
	// Lag behind trace start
	FVector TraceEnd = TraceStart - ExtendedSocketDirection;

	TArray<FHitResult> HitResults;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(MeshComp->GetOwner());

	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);

	UWorld* World = GEngine->GetWorldFromContextObject(MeshComp, EGetWorldErrorMode::LogAndReturnNull);
	if (!IsValid(World)) return HitResults;
	bool const bHit = World->SweepMultiByChannel(
		HitResults,
		TraceStart,
		TraceEnd,
		FQuat::Identity,
		ECC_Visibility,
		FCollisionShape::MakeSphere(SphereTraceRadius),
		QueryParams,
		ResponseParams);

	if (bDrawDebugs)
	{
		DrawDebugSphereTraceMulti(World, TraceStart, TraceEnd, SphereTraceRadius, EDrawDebugTrace::ForDuration, bHit, HitResults, FColor::Red, FColor::Green, 5.f);
	}

	return HitResults;
}

void UANS_MeleeAttack::SendEventsToActors(const TArray<FHitResult>& HitResults, USkeletalMeshComponent* MeshComp)
{
	UAbilitySystemComponent* AbilitySystemComponent = Cast<AGC_BaseCharacter>(MeshComp->GetOwner())->GetAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent)) return;
	
	for (const FHitResult& HitResult : HitResults)
	{
		if (!IsValid(HitResult.GetActor())) continue;
		AGC_PlayerCharacter* PlayerCharacter = Cast<AGC_PlayerCharacter>(HitResult.GetActor());
		if (!IsValid(PlayerCharacter)) continue;
		if (!PlayerCharacter->IsAlive()) continue;

		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddHitResult(HitResult);
		
		FGameplayEventData Payload;
		Payload.Target = PlayerCharacter;
		Payload.ContextHandle = EffectContext;
		Payload.Instigator = MeshComp->GetOwner();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), GCTags::Events::Enemy::MeleeTraceHit, Payload);
	}
}
