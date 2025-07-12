// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/XMSNodeWithValue.h"
#include "Engine/DataAsset.h"
#include "XMSNodeDataRegistry.generated.h"


class UXMSNodeClassOptionEntryWidget;
class UXMSNodeData;
class UXMSArrayTerminatorWidget;
class UXMSNodeContainerFromArrayWidget;
class UXMSNodeContainerFromMapWidget;
class UXMSNodeOptionsSelectionWidget;
class UXMSNodeCanvasWidget;

USTRUCT(BlueprintType)
struct FXMSValueTypeData
{
	GENERATED_BODY()
	
	FXMSValueTypeData()
	{
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Glyph;
};

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeDataRegistry : public UDataAsset
{
	GENERATED_BODY()

public:
	UXMSNodeDataRegistry(const FObjectInitializer& ObjectInitializer);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UObject Interface
	 */
	
#if WITH_EDITOR

public:
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeDataRegistry
	 */

public:
	UPROPERTY(EditAnywhere, Category = "UI|NodeCanvas")
	TSubclassOf<UXMSNodeCanvasWidget> NodeCanvasWidgetClass;
	UPROPERTY(EditAnywhere, Category = "UI|NodeCanvas")
	TSubclassOf<UXMSNodeOptionsSelectionWidget> NodeOptionsWidgetClass;
	
	UPROPERTY(EditAnywhere, Category = "UI|NodeCanvas|Node")
	UTexture2D* EmptyNodeTexture;
	UPROPERTY(EditAnywhere, Category = "UI|NodeCanvas|Node")
	TSubclassOf<UXMSNodeClassOptionEntryWidget> NodeClassOptionWidgetClass;
	
	UPROPERTY(EditAnywhere, Category = "UI|NodeCanvas|NodeWithMap")
	TSubclassOf<UXMSNodeContainerFromMapWidget> NodeWithMapWidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI|NodeCanvas|NodeWithArray")
	TSubclassOf<UXMSNodeContainerFromArrayWidget> NodeWithArrayWidgetClass;
	UPROPERTY(EditAnywhere, Category = "UI|NodeCanvas|NodeWithArray")
	TSubclassOf<UXMSArrayTerminatorWidget> ArrayTerminatorWidgetClass;

/*--------------------------------------------------------------------------------------------------------------------*/
	// ValueTypes
	
public:
	UFUNCTION(BlueprintCallable)
	const TMap<FGameplayTag, FXMSValueTypeData>& GetTypesData();
	UFUNCTION(BlueprintCallable)
	bool GetTypeData(const FGameplayTag& InType, FXMSValueTypeData& OutTypeData);
	FXMSValueTypeData* GetTypeData(const FGameplayTag& InType);
private:
	void UpdateTypesMap();
	UPROPERTY(EditAnywhere, Category = "ValueTypes", meta=(TitleProperty = "Name", ForceInlineRow))
	TMap<FGameplayTag, FXMSValueTypeData> ValueTypesData;

	// ~ValueTypes
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
	// NodesData
	
public:
	UFUNCTION(BlueprintCallable)
	UXMSNodeData* GetNodeData(UClass* NodeClass);
	const TMap<TSubclassOf<UXMSNode>, UXMSNodeData*>& GetNodesData() const { return NodesData; }
private:
	void UpdateNodeDataMap();
	UPROPERTY(EditAnywhere, meta = (TitleProperty = "NodeClass"))
	TMap<TSubclassOf<UXMSNode>, UXMSNodeData*> NodesData;

	// ~NodesData
/*--------------------------------------------------------------------------------------------------------------------*/
	
};
