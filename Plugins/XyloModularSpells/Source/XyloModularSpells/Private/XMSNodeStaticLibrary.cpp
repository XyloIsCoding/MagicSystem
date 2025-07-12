// Fill out your copyright notice in the Description page of Project Settings.


#include "XMSNodeStaticLibrary.h"

#include "XMSModularSpellsSubsystem.h"
#include "Node/XMSNodeData.h"
#include "Node/XMSNodeDataRegistry.h"
#include "Node/Base/XMSNode.h"
#include "SpellExecutor/XMSSpellExecutorInterface.h"
#include "SpellEditor/XMSSpellEditorComponent.h"
#include "SpellEditor/XMSSpellEditorInterface.h"

FString UXMSNodeStaticLibrary::ReadStringFromFile(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Check if file exists
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("UXMSNodeStaticLibrary::ReadStringFromFile >> File does not exist - %s"), *FilePath);
		return "";
	}

	FString ReturnString = "";

	// Try read file. Output goes in ReturnString;
	if (!FFileHelper::LoadFileToString(ReturnString, *FilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("UXMSNodeStaticLibrary::ReadStringFromFile >> Was not able to read file. Is this a text file? - %s"), *FilePath);
		return "";
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("UXMSNodeStaticLibrary::ReadStringFromFile >> Reading string from file succeeded - %s"), *FilePath);
	return ReturnString;
}

void UXMSNodeStaticLibrary::WriteStringToFile(FString FilePath, FString String, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Try to write string into file
	if (!FFileHelper::SaveStringToFile(String, *FilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("UXMSNodeStaticLibrary::WriteStringToFile >> Not able to write to file. Is your file read only? is the path valid? - %s"), *FilePath);
		return;
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("UXMSNodeStaticLibrary::WriteStringToFile >> Write string to file succeeded - %s"), *FilePath);
}

TSharedPtr<FJsonObject> UXMSNodeStaticLibrary::ReadJson(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Try to read file
	FString JsonString = ReadStringFromFile(JsonFilePath, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{
		return nullptr;
	}

	TSharedPtr<FJsonObject> ReturnJsonObject;

	// Try to convert string to json object. Output goes in ReturnJsonObject
	if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), ReturnJsonObject))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("UXMSNodeStaticLibrary::ReadJson >> Not able to deserialize the json string. Is it the right format? - %s"), *JsonFilePath);
		return nullptr;
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("UXMSNodeStaticLibrary::ReadJson >> Read from json succeeded - %s"), *JsonFilePath);
	return ReturnJsonObject;
}

void UXMSNodeStaticLibrary::WriteJson(FString JsonFilePath, TSharedPtr<FJsonObject> JsonObject, bool& bOutSuccess, FString& OutInfoMessage)
{
	FString JsonString;

	// Try convert json object to string. Output goes in JsonString
	if (!FJsonSerializer::Serialize(JsonObject.ToSharedRef(), TJsonWriterFactory<>::Create(&JsonString, 0)))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("UXMSNodeStaticLibrary::WriteJson >> Not able to serialize the json to string. Is the JsonObject valid? - %s"), *JsonFilePath);
		return;
	}

	WriteStringToFile(JsonFilePath, JsonString, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{
		return;
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("UXMSNodeStaticLibrary::WriteJson >> Write to json succeeded - %s"), *JsonFilePath);
}

void UXMSNodeStaticLibrary::GetAllValueTypes(TArray<FGameplayTag>& OutTypes)
{
	if (UXMSNodeDataRegistry* NodeDataRegistry = GetNodeClassDataRegistry())
	{
		NodeDataRegistry->GetTypesData().GetKeys(OutTypes);
	}
	if (OutTypes.IsEmpty())
	{
		OutTypes.Add(XMSValueType::None);
	}
}

FGameplayTag UXMSNodeStaticLibrary::GetValueTypeFromName(FName TypeName)
{
	UXMSNodeDataRegistry* NodeDataRegistry = GetNodeClassDataRegistry();
	if (!NodeDataRegistry) return XMSValueType::None;

	for (TPair<FGameplayTag, FXMSValueTypeData> TypeDataPair : NodeDataRegistry->GetTypesData())
	{
		if (TypeDataPair.Key.GetTagName().IsEqual(TypeName))
		{
			return TypeDataPair.Key;
		}
	}
	return XMSValueType::None;
}

UTexture2D* UXMSNodeStaticLibrary::GetValueTypeIcon(const FGameplayTag& Type)
{
	UXMSNodeDataRegistry* NodeDataRegistry = GetNodeClassDataRegistry();
	if (!NodeDataRegistry) return nullptr;

	FXMSValueTypeData* ValueTypeData = NodeDataRegistry->GetTypeData(Type);
	return ValueTypeData ? ValueTypeData->Glyph : nullptr;
}

bool UXMSNodeStaticLibrary::GetAllNodeClasses(TArray<TSubclassOf<UXMSNode>>& OutClasses)
{
	UXMSNodeDataRegistry* NodeDataRegistry = GetNodeClassDataRegistry();
	if (!NodeDataRegistry) return false;

	NodeDataRegistry->GetNodesData().GetKeys(OutClasses);
	return true;
}

UClass* UXMSNodeStaticLibrary::GetNodeClassByName(const FString& ClassName)
{
	TArray<TSubclassOf<UXMSNode>> NodeClasses;
	GetAllNodeClasses(NodeClasses);
	for (UClass* NodeClass : NodeClasses)
	{
		if (NodeClass->GetName().Equals(ClassName))
		{
			return NodeClass;
		}
	}
	return nullptr;
}

UXMSNodeDataRegistry* UXMSNodeStaticLibrary::GetNodeClassDataRegistry()
{
	UXMSModularSpellsSubsystem* MSS = UXMSModularSpellsSubsystem::Get();
	if (!MSS) return nullptr;
	return MSS->GetNodeDataRegistry();
}

UXMSNodeData* UXMSNodeStaticLibrary::GetNodeClassData(UClass* NodeClass)
{
	if (!NodeClass) return nullptr;
	UXMSNodeDataRegistry* NodeDataRegistry = GetNodeClassDataRegistry();
	if (!NodeDataRegistry) return nullptr;
	return NodeDataRegistry->GetNodeData(NodeClass);
}

UTexture2D* UXMSNodeStaticLibrary::GetNodeClassIconFromNode(UXMSNode* Node)
{
	if (Node)
	{
		UXMSNodeData* NodeData = GetNodeClassData(Node->GetClass());
		return NodeData? NodeData->Glyph : nullptr;
	}

	UXMSNodeDataRegistry* NodesDataRegistry = GetNodeClassDataRegistry();
	if (!NodesDataRegistry) return nullptr;
	return NodesDataRegistry->EmptyNodeTexture;
}

FString UXMSNodeStaticLibrary::GetNodeClassNameFromNode(UXMSNode* Node)
{
	if (Node) return Node->GetClass()->GetName();
	return FString(TEXT("NONE"));
}

UTexture2D* UXMSNodeStaticLibrary::GetNodeClassIcon(UClass* NodeClass)
{
	if (!NodeClass) return nullptr;
	
	UXMSNodeData* NodeData = GetNodeClassData(NodeClass);
	return NodeData? NodeData->Glyph : nullptr;
}

FString UXMSNodeStaticLibrary::GetNodeClassName(UClass* NodeClass)
{
	if (NodeClass) return NodeClass->GetName();
	return FString(TEXT("NONE"));
}

UXMSNode* UXMSNodeStaticLibrary::CopyNode(UObject* Outer, UXMSNode* InNode)
{
	if (!InNode || !Outer) return nullptr;

	bool bSerializeSuccess;
	TSharedPtr<FJsonObject> NodeJson = InNode->SerializeToJson(bSerializeSuccess);
	if (!bSerializeSuccess) return nullptr;
	
	UXMSNode* NewNode = NewObject<UXMSNode>(Outer, InNode->GetClass());
	if (!NewNode) return nullptr;
	
	NewNode->DeserializeFromJson(NodeJson);
	return NewNode;
}

UXMSSpellEditorComponent* UXMSNodeStaticLibrary::GetSpellEditorComponent(UObject* Actor)
{
	if (!Actor) return nullptr;
	IXMSSpellEditorInterface* SpellEditorInterface = Cast<IXMSSpellEditorInterface>(Actor);
	if (!SpellEditorInterface) return nullptr;

	return SpellEditorInterface->GetSpellEditorComponent();
}

UXMSSpellExecutorComponent* UXMSNodeStaticLibrary::GetSpellExecutorComponent(UObject* Actor)
{
	if (!Actor) return nullptr;
	IXMSSpellExecutorInterface* SpellExecutorInterface = Cast<IXMSSpellExecutorInterface>(Actor);
	if (!SpellExecutorInterface) return nullptr;

	return SpellExecutorInterface->GetSpellExecutorComponent();
}
