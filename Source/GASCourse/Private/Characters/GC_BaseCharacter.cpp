// Fill out your copyright notice in the Description page of Project Settings.


#include "GASCourse/Public/Characters/GC_BaseCharacter.h"

AGC_BaseCharacter::AGC_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Tick and refresh bones transforms whether rendered or not - for bone updates on a dedicated server
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}
