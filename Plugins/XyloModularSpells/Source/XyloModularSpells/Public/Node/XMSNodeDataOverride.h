// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "XMSNodeDataOverride.generated.h"


class XMSNode;

USTRUCT(BlueprintType)
struct FXMSNodeData
{
	GENERATED_BODY()

	FXMSNodeData()
	{
	}
	
	FXMSNodeData(UClass* InClass)
		: NodeClass(InClass)
	{
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UClass> NodeClass;
	
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

public:
	UXMSNodeDataOverride(const FObjectInitializer& ObjectInitializer);

public:
	UFUNCTION(BlueprintCallable)
	bool GetNodeData(UClass* NodeClass, FXMSNodeData& OutNodeData);
private:
	void UpdateNodeDataArray();
	UPROPERTY(EditAnywhere, EditFixedSize, meta=(TitleProperty="NodeClass"))
	TArray<FXMSNodeData> NodesData;
	
};
