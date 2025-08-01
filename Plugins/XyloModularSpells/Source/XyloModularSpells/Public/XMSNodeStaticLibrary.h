// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "XMSNodeStaticLibrary.generated.h"

struct FXMSNodePathElement;
struct FXMSValueTypeData;
class UXMSSpellExecutorComponent;
struct FGameplayTag;
class UXMSNodeDataRegistry;
class UXMSNodeData;
class UXMSSpellEditorComponent;
class UXMSNode;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeStaticLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FString ReadStringFromFile(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage);
	static void WriteStringToFile(FString FilePath, FString String, bool& bOutSuccess, FString& OutInfoMessage);

	static TSharedPtr<FJsonObject> ReadJson(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage);
	static void WriteJson(FString JsonFilePath, TSharedPtr<FJsonObject> JsonObject, bool& bOutSuccess, FString& OutInfoMessage);

	static void GetAllValueTypes(TArray<FGameplayTag>& OutTypes);
	static FGameplayTag GetValueTypeFromName(FName TypeName);
	static FXMSValueTypeData* GetValueTypeData(const FGameplayTag& Type);
	UFUNCTION(BlueprintCallable)
	static UTexture2D* GetValueTypeIcon(const FGameplayTag& Type);

	static bool GetAllNodeClasses(TArray<TSubclassOf<UXMSNode>>& OutClasses);
	static UClass* GetNodeClassByName(const FString& ClassName);
	static UXMSNodeDataRegistry* GetNodeClassDataRegistry();
	static UXMSNodeData* GetNodeClassData(UClass* NodeClass);
	static void GetNodeClassRequiredFlags(UClass* NodeClass, FGameplayTagContainer& OutFlags);
	static bool AreNodeClassFlagsSatisfied(UClass* NodeClass, const FGameplayTagContainer& AvailableFlags);
	static bool IsSubNodeHiddenInEditor(UClass* ParentNodeClass, const FXMSNodePathElement& PathToSubNode);
	/** If Node is not valid, falls back to using a default texture */
	static UTexture2D* GetNodeClassIconFromNode(UXMSNode* Node);
	static FString GetNodeClassNameFromNode(UXMSNode* Node);
	static UTexture2D* GetNodeClassIcon(UClass* NodeClass);
	static FString GetNodeClassName(UClass* NodeClass);

	/** Get a deep copy of this node reparented to the chosen outer
	 * @param Outer: Outer for the returned node
	 * @param InNode: Node to copy
	 * @return: Reparented copy of InNode */
	static UXMSNode* CopyNode(UObject* Outer, UXMSNode* InNode);

	template <typename T> requires std::is_base_of_v<UXMSNode, T>
	static T* CopyNode(UObject* Outer, T* InNode)
	{
		return static_cast<T*>(CopyNode(Outer, static_cast<UXMSNode*>(InNode)));
	}

	static UXMSSpellEditorComponent* GetSpellEditorComponent(UObject* Actor);
	static UXMSSpellExecutorComponent* GetSpellExecutorComponent(UObject* Actor);
};

