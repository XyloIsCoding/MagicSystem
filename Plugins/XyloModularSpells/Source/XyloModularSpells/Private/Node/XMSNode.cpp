// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/XMSNode.h"

AActor* UXMSNode::GetOwningActor() const
{
	return GetTypedOuter<AActor>();
}

UWorld* UXMSNode::GetWorld() const
{
	if (GetOuter() == nullptr)
	{
		return nullptr;
	}
		
	if (Cast<UPackage>(GetOuter()) != nullptr)
	{
		return Cast<UWorld>(GetOuter()->GetOuter());
	}
	
	return GetOwningActor()->GetWorld();
}
