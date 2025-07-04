// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/XMSNodeWithValue.h"
#include "Engine/DataAsset.h"
#include "XMSNodeDataRegistry.generated.h"


class UXMSNodeClassOptionEntryWidget;
class UXMSNodeData;
class UXMSArrayAddButtonWidget;
class UXMSNodeContainerFromArrayWidget;
class UXMSNodeContainerFromMapWidget;
class UXMSNodeOptionsSelectionWidget;
class UXMSNodeCanvasWidget;

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
	TSubclassOf<UXMSArrayAddButtonWidget> ArrayTerminatorWidgetClass;

public:
	UFUNCTION(BlueprintCallable)
	UXMSNodeData* GetNodeData(UClass* NodeClass);
private:
	void UpdateNodeDataMap();
	UPROPERTY(EditAnywhere, meta = (TitleProperty = "NodeClass", ReadOnlyKeys))
	TMap<TSubclassOf<UXMSNode>, UXMSNodeData*> NodesData;
	
};
