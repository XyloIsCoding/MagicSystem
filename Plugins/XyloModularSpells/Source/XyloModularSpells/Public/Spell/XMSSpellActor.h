// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Runnable/XMSRunnableNodeInterface.h"
#include "SpellExecutor/XMSSpellExecutorInterface.h"
#include "XMSSpellActor.generated.h"





class UBlackboardComponent;
class UBlackboardData;

UCLASS()
class XYLOMODULARSPELLS_API AXMSSpellActor : public AActor, public IXMSSpellExecutorInterface
{
	GENERATED_BODY()

public:
	AXMSSpellActor();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * AActor Interface
	 */

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSSpellExecutorInterface Interface
	 */

public:
	virtual UXMSSpellExecutorComponent* GetSpellExecutorComponent() override { return SpellExecutorComponent; }
protected:
	UPROPERTY()
	TObjectPtr<UXMSSpellExecutorComponent> SpellExecutorComponent;
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * AXMSSpellActor
	 */
	
public:
	TXMSNodeContainer<UXMSNode, IXMSRunnableNodeInterface> Instruction = {
		nullptr,
		GET_MEMBER_NAME_CHECKED(ThisClass, Instruction),
		[](UClass* NodeClass){ return true; } };
};
