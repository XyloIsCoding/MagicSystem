// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Base/XMSNode.h"

#include "XMSNodeStaticLibrary.h"
#include "SpellEditor/XMSSpellEditorInterface.h"


const FString UXMSNode::NodeClassJsonKey = FString(TEXT("NodeClass"));

UXMSNode::UXMSNode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UObject
 */

void UXMSNode::BeginDestroy()
{
	// We want to make sure this node is removed from parent before destruction.
	// (usually RemovedFromParentDelegate is used to clean up node data from other classes)
	RemoveFromParent();
	
	UObject::BeginDestroy();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode
 */

bool UXMSNode::IsInSpellEditorContext() const
{
	return GetOuter() && GetOuter()->Implements<IXMSSpellEditorInterface::UClassType>();
}

void UXMSNode::GetNodeFlagsRecursive(FGameplayTagContainer& OutFlags) const
{
	GetNodeFlags(OutFlags);
	
	if (UXMSNode* Parent = ParentNode.Get())
	{
		Parent->GetNodeFlagsRecursive(OutFlags);
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/
// Serialization

TSharedPtr<FJsonObject> UXMSNode::SerializeToJson(bool& bOutSuccess)
{
	TSharedPtr<FJsonObject> NodeJson = MakeShareable<>(new FJsonObject);
	NodeJson->SetStringField(NodeClassJsonKey, GetClass()->GetName());
	bOutSuccess = true;
	return NodeJson;
}

void UXMSNode::DeserializeFromJson(TSharedPtr<FJsonObject>)
{
	
}

// ~Serialization
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// Hierarchy

void UXMSNode::GetHierarchy(TArray<UXMSNode*>& OutHierarchy) const
{
	UXMSNode* Parent = ParentNode.Get();
	if (!Parent) return;
	
	OutHierarchy.Add(Parent);
	Parent->GetHierarchy(OutHierarchy);
}

bool UXMSNode::IsInScopeOf(UXMSNode* Other) const
{
	if (!Other) return false;

	TArray<UXMSNode*> Parents;
	GetHierarchy(Parents);

	return IsInScopeOf(Other, Parents);
}

bool UXMSNode::IsInScopeOf(UXMSNode* Other, const TArray<UXMSNode*>& ThisNodeHierarchy) const
{
	if (!Other) return false;
	UXMSNode* OtherParent = Other->ParentNode.Get();

	if (!OtherParent)
	{
		// If Other does not have a parent, it might be the root node, so we try to check if
		// this node descends from Other
		int32 IndexOfMatchingParent = ThisNodeHierarchy.Find(Other);
		return IndexOfMatchingParent != INDEX_NONE;
	}

	// Check if this node and Other have a common parent
	int32 IndexOfMatchingParent = ThisNodeHierarchy.Find(OtherParent);
	// No parent in common
	if (IndexOfMatchingParent == INDEX_NONE) return false;
	
	// There is a matching parent, so it could be one of two cases:
	// 1) the common parent is a NodeWithMap, in which case Other and the child of MatchingParent will have Path Index 0
	// 2) the common parent is a NodeWithArray, in which case we need to make sure that Other's Path Index is lower
	//	  than the Path index of the child of MatchingParent

	// To get the child of OtherParent we can use the knowledge that ThisNodeHierarchy has been generated
	// by GetHierarchy, which means that by using 'Index - 1' we can climb down the hierarchy and reach the
	// child of that parent
	const UXMSNode* ChildOfMatchingParent = ThisNodeHierarchy.IsValidIndex(IndexOfMatchingParent - 1)
		? ThisNodeHierarchy[IndexOfMatchingParent - 1] : this;
	
	return ChildOfMatchingParent && ChildOfMatchingParent->PathFromParentNode.Index >= Other->PathFromParentNode.Index;
}

// ~Hierarchy
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// ParentNode

void UXMSNode::RemoveFromParent()
{
	UXMSNode* Parent = ParentNode.Get();
	if (!Parent) return;

	// If ParentNode is not nullptr, it means that this node is still set as sub-node of ParentNode
	// (When a node is set in a node container RemovedFromParent_Internal is called on the old node).
	// This means that we can safely use SetSubNode without worrying about overriding nodes
	Parent->SetSubNode(PathFromParentNode, nullptr);
}

void UXMSNode::ReparentNode(UXMSNode* InParentNode, const FXMSNodePathElement& InPathFromParent)
{
	// UE_LOG(LogTemp, Warning, TEXT("UXMSNode::ReparentNode >> [%s] now has parent [%s]"), *GetName(), InParentNode ? *InParentNode->GetName() : *FString())
	ParentNode = InParentNode;
	PathFromParentNode = InPathFromParent;
	OnParentSet();
}

void UXMSNode::RemovedFromParent_Internal()
{
	// Clean up this node
	PreRemovedFromParent();
	
	ParentNode = nullptr;
	PathFromParentNode.Reset();

	PostRemovedFromParent();
	RemovedFromParentDelegate.Broadcast();

	TArray<UXMSNode*> SubNodes;
	GetAllSubNodes(SubNodes);
	for (UXMSNode* SubNode : SubNodes)
	{
		// Call RemoveFromParent from sub-nodes after removing this node from parent
		// This allows to disassemble the hierarchy from this node to the branches of the hierarchy tree
		if (SubNode) SubNode->RemoveFromParent();
	}
}

// ~ParentNode
/*--------------------------------------------------------------------------------------------------------------------*/

