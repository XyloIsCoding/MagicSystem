// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XMSNodeTooltipInterface.generated.h"

class UXMSNodeTooltipWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FXMSTooltipRequestedSignature, UWidget*)

// This class does not need to be modified.
UINTERFACE()
class UXMSNodeTooltipInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOMODULARSPELLS_API IXMSNodeTooltipInterface
{
	GENERATED_BODY()

public:
	virtual FXMSTooltipRequestedSignature& GetTooltipRequestedDelegate() = 0;
	virtual void InitializeTooltip(UXMSNodeTooltipWidget* TooltipWidget) = 0;
};
