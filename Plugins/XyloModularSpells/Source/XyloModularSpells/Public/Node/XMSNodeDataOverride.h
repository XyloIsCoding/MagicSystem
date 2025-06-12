// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "XMSNodeDataOverride.generated.h"


USTRUCT(BlueprintType)
struct FXMSNodeData
{
	GENERATED_BODY()

	FXMSNodeData()
	{
	}
	
	FXMSNodeData(FGameplayTag InIdentifier)
		: NodeIdentifier(InIdentifier)
	{
	}
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayTag NodeIdentifier;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(MultiLine=true))
	FText Description;
};


/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeDataOverride : public UDataAsset
{
	GENERATED_BODY()

	UXMSNodeDataOverride(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, EditFixedSize, meta=(TitleProperty="Name"))
	TArray<FXMSNodeData> Registry;

	void TestFunction();
};
