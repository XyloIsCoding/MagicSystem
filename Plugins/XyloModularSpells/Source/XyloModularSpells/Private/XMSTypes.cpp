// Fill out your copyright notice in the Description page of Project Settings.


#include "XMSTypes.h"

void FXMSNodePath::ExtendPath(const FXMSNodePathElement& PathElement)
{
	Path.Add(PathElement);
}

FString FXMSNodePath::ToString() const
{
	FString StringPath;
	for (const FXMSNodePathElement& PathElement : Path)
	{
		FString IdentifierString = PathElement.Identifier.ToString();
		if (PathElement.Index != INDEX_NONE)
		{
			IdentifierString.Append(FString::Printf(TEXT("[%i]"), PathElement.Index));
		}
		StringPath.Append(FString::Printf(TEXT(".%s"), *IdentifierString));
	}
	return StringPath.RightChop(0);;
}

bool FXMSNodePath::GetPathElement(int32 Index, FXMSNodePathElement& OutPathElement)
{
	if (!Path.IsValidIndex(Index)) return false;
	
	OutPathElement = Path[Index];
	return true;
}

namespace XMSValueType
{
	UE_DEFINE_GAMEPLAY_TAG(None, "XMS.Node.Type.None")
	UE_DEFINE_GAMEPLAY_TAG(Bool, "XMS.Node.Type.Bool")
	UE_DEFINE_GAMEPLAY_TAG(Integer, "XMS.Node.Type.Integer")
	UE_DEFINE_GAMEPLAY_TAG(Float, "XMS.Node.Type.Float")
	UE_DEFINE_GAMEPLAY_TAG(Vector, "XMS.Node.Type.Vector")
	UE_DEFINE_GAMEPLAY_TAG(Rotator, "XMS.Node.Type.Rotator")
	UE_DEFINE_GAMEPLAY_TAG(String, "XMS.Node.Type.String")
	UE_DEFINE_GAMEPLAY_TAG(Object, "XMS.Node.Type.Object")
}

namespace XMSNodeFlag
{
	UE_DEFINE_GAMEPLAY_TAG(Impossible, "XMS.Node.Flag.Impossible")
	UE_DEFINE_GAMEPLAY_TAG(Loop, "XMS.Node.Flag.Loop")
}
