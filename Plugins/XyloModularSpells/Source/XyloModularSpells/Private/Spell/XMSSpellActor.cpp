// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell/XMSSpellActor.h"

#include "SpellExecutor/XMSSpellExecutorComponent.h"


AXMSSpellActor::AXMSSpellActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SpellExecutorComponent = CreateDefaultSubobject<UXMSSpellExecutorComponent>(TEXT("SpellExecutorComponent"));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * AActor Interface
 */

void AXMSSpellActor::BeginPlay()
{
	Super::BeginPlay();

	if (IXMSRunnableNodeInterface* RunnableNodeInterface = Instruction.GetInterface())
	{
		RunnableNodeInterface->ExecuteNode();
	}
}

void AXMSSpellActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * AXMSSpellActor
 */



