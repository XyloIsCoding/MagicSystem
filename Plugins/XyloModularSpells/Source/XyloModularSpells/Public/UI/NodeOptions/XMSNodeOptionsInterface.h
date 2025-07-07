// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "UObject/Interface.h"
#include "XMSNodeOptionsInterface.generated.h"

class UXMSNodeOptionsSelectionWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FXMSOptionsRequestedSignature, UWidget*)

// This class does not need to be modified.
UINTERFACE()
class UXMSNodeOptionsInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Must be implemented by UXMSNodeCanvasEntryWidget classes that require having a UXMSNodeOptionsSelectionWidget
 */
class XYLOMODULARSPELLS_API IXMSNodeOptionsInterface
{
	GENERATED_BODY()

public:
	virtual FXMSOptionsRequestedSignature& GetOptionsRequestedDelegate() = 0;
	virtual void InitializeOptions(UXMSNodeOptionsSelectionWidget* OptionsSelectionWidget) = 0;
};
