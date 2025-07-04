// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "XMSNodeData.generated.h"


class UXMSNode;
class UXMSNodeValueWidget;

USTRUCT(BlueprintType)
struct FXMSSubNodeData
{
	GENERATED_BODY()

	FXMSSubNodeData()
	{
	}
	
	FXMSSubNodeData(FName InIdentifier)
		: Identifier(InIdentifier)
	{
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName Identifier;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Glyph;
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeData : public UDataAsset
{
	GENERATED_BODY()

public:
	UXMSNodeData(const FObjectInitializer& ObjectInitializer);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UObject Interface
	 */
	
#if WITH_EDITOR
	
public:
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
	
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeData
	 */

/*--------------------------------------------------------------------------------------------------------------------*/
	// NodeClass
	
public:
	UClass* GetNodeClass() const;
protected:
	void OnNodeClassChanged();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UXMSNode> NodeClass;
private:
	UPROPERTY()
	bool bIsNodeWithValue = false;

	// ~NodeClass
/*--------------------------------------------------------------------------------------------------------------------*/

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Glyph;
	
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bIsNodeWithValue", EditConditionHides, HideEditConditionToggle))
	TSubclassOf<UXMSNodeValueWidget> ValueSelectorWidgetClass;

	/** Node with this property set to true will not be displayed in spell editor, which means that the ContainerWidget
	 * set to display this node, will disappear, and the node of the container will no longer be modifiable.
	 * This is only useful if this node class is only going to be used as default value for a node */
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bIsNodeWithValue", EditConditionHides, HideEditConditionToggle))
	bool bHideInSpellEditor = false;

/*--------------------------------------------------------------------------------------------------------------------*/
	// SubNodes
	
public:
	void UpdateSubNodes();
	UFUNCTION(BlueprintCallable)
	bool GetSubNodeData(FName SubNodeIdentifier, FXMSSubNodeData& OutSubNodeData);
	FXMSSubNodeData* GetSubNodeData(FName SubNodeIdentifier);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, EditFixedSize, meta = (TitleProperty = "Identifier"))
	TArray<FXMSSubNodeData> SubNodes;

	// ~SubNodes
/*--------------------------------------------------------------------------------------------------------------------*/

};
