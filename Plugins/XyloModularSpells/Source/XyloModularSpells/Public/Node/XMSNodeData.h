// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "XMSNodeData.generated.h"


class UXMSNode;
class UXMSNodeValueSelectorWidget;

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

public:
	void SetClasses(UClass* BaseClass, UClass* InterfaceClass);
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (EditCondition = "bHideStuff", EditConditionHides, HideEditConditionToggle))
	FString SubNodeClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (EditCondition = "bHideStuff", EditConditionHides, HideEditConditionToggle))
	FString SubNodeInterface;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName Identifier;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Glyph;

	/** SubNodes with this property set to true will not be displayed in spell editor, which means that the
	 * ContainerWidget set to display this node, will disappear, and the node of the container will no longer be modifiable.
	 * This is only useful if this sub node is supposed to have a non-modifiable default value
	 * (es: UXMSValueTypeValueNode is usually hidden, so that only its selector is visible) */
	UPROPERTY(EditAnywhere)
	bool bHideInSpellEditor = false;

private:
	// Used to hide properties that we want to use as TitleProperty (since thy must be marked as VisibleAnywhere)
	UPROPERTY()
	bool bHideStuff = false;
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

protected:
	UPROPERTY(EditAnywhere)
	bool bRefreshData = false;

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

	/** Flags to filter the context where this node class can be selected (checked in spell editor only).
	 * @remark In UXMSNode::GetSubNodeClassOptions for each class we check if the result of GetNodeFlagsRecursive
	 * contains all the flags specified by this property, and only in this case we allow the class to be an option. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer RequiredContextFlags;
	
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bIsNodeWithValue", EditConditionHides, HideEditConditionToggle))
	TSubclassOf<UXMSNodeValueSelectorWidget> ValueSelectorWidgetClass;

/*--------------------------------------------------------------------------------------------------------------------*/
	// SubNodes
	
public:
	void UpdateSubNodes();
	UFUNCTION(BlueprintCallable)
	bool GetSubNodeData(FName SubNodeIdentifier, FXMSSubNodeData& OutSubNodeData);
	FXMSSubNodeData* GetSubNodeData(FName SubNodeIdentifier);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, EditFixedSize, meta = (TitleProperty = "{Identifier} : [{SubNodeClass} | {SubNodeInterface}]"))
	TArray<FXMSSubNodeData> SubNodes;

	// ~SubNodes
/*--------------------------------------------------------------------------------------------------------------------*/

};
