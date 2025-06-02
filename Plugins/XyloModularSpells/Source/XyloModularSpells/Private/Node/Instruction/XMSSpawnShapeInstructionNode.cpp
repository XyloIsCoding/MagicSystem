// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Instruction/XMSSpawnShapeInstructionNode.h"

void UXMSSpawnShapeInstructionNode::ExecuteNode()
{
	if (ShapeClass && GetWorld() && GetWorld()->IsGameWorld())
	{
		//GetWorld()->SpawnActor(ShapeClass);
	}
}
