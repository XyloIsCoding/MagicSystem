// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "XMSNodeDataRegistry.generated.h"


class UXMSNodeValueWidget;
class UXMSArrayAddButtonWidget;
class UXMSNodeClassOptionsWidget;
class UXMSNodeCanvasWidget;
class UXMSNodeContainerFromArrayWidget;
class UXMSNodeContainerWidget;
class UXMSNodeContainerFromMapWidget;
class UXMSNode;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(MultiLine=true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Glyph;
};

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
		UpdateSubNodes();
	}

	void UpdateSubNodes();
	FXMSSubNodeData* GetSubNodeData(FName SubNodeIdentifier);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UClass> NodeClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(MultiLine=true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Glyph;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UXMSNodeContainerWidget> WidgetClassOverride;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UXMSNodeValueWidget> ValueSelectorWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, EditFixedSize, meta=(TitleProperty="Identifier"))
	TArray<FXMSSubNodeData> SubNodes;
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

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif


public:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UXMSNodeCanvasWidget> NodeCanvasWidgetClass;
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UXMSNodeClassOptionsWidget> NodeOptionsWidgetClass;
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UXMSNodeContainerFromMapWidget> NodeWithMapWidgetClass;
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UXMSNodeContainerFromArrayWidget> NodeWithArrayWidgetClass;
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UXMSArrayAddButtonWidget> ArrayAddWidgetClass;
	UPROPERTY(EditAnywhere, Category = "UI")
	UTexture2D* EmptyNodeTexture;
	UPROPERTY(EditAnywhere, Category = "UI")
    UTexture2D* ArrayAddTexture;
	UPROPERTY(EditAnywhere, Category = "UI")
	UTexture2D* ArrayRemoveTexture;

public:
	UFUNCTION(BlueprintCallable)
	bool GetNodeData(UClass* NodeClass, FXMSNodeData& OutNodeData);
	FXMSNodeData* GetNodeData(UClass* NodeClass);
private:
	void UpdateNodeDataArray();
	UPROPERTY(EditAnywhere, EditFixedSize, meta=(TitleProperty="NodeClass"))
	TArray<FXMSNodeData> NodesData;
	
};
