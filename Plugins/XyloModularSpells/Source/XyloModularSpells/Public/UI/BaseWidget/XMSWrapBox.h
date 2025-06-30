// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WrapBox.h"
#include "XMSWrapBox.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSWrapBox : public UWrapBox
{
	GENERATED_BODY()

public:
	int32 AddChildAt(int32 Index, UWidget* Content);
	void Rebuild();
};
