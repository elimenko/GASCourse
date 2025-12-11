// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class GASCOURSE_API UANS_MeleeAttack : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GC|TraceParams")
	FName SocketName{"FX_Trail_01_R"};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GC|TraceParams")
	float SocketExtensionOffset{40.f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GC|TraceParams")
	float SphereTraceRadius{60.f};

private:
	UPROPERTY(EditAnywhere, Category = "GC|Debugs")
	bool bDrawDebugs = true;
	
	TArray<FHitResult> PerformSphereTrace(USkeletalMeshComponent* MeshComp) const;

	void SendEventsToActors(const TArray<FHitResult>& HitResults, USkeletalMeshComponent* MeshComp);
};
