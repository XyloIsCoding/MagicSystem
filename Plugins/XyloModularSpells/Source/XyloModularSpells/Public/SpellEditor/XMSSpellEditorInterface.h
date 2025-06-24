// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XMSSpellEditorInterface.generated.h"

class UXMSSpellEditorComponent;
// This class does not need to be modified.
UINTERFACE()
class UXMSSpellEditorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOMODULARSPELLS_API IXMSSpellEditorInterface
{
	GENERATED_BODY()

public:
	virtual UXMSSpellEditorComponent* GetSpellEditorComponent() = 0;
};
