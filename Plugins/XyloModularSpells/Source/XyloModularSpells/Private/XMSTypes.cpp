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
	return StringPath;
}
