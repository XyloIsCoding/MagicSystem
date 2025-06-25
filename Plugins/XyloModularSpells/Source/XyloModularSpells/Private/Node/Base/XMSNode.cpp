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
 * UXMSNode
 */

bool UXMSNode::IsInSpellEditorContext() const
{
	return GetOuter() && GetOuter()->Implements<IXMSSpellEditorInterface::UClassType>();
}

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

void UXMSNode::GetNodeFlagsRecursive(FGameplayTagContainer& OutFlags) const
{
	GetNodeFlags(OutFlags);
	
	if (UXMSNode* Parent = ParentNode.Get())
	{
		Parent->GetNodeFlagsRecursive(OutFlags);
	}
}

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
	
	return ChildOfMatchingParent && ChildOfMatchingParent->PathFromParent.Index >= Other->PathFromParent.Index;
}

void UXMSNode::RemoveFromParent()
{
	// Clean up sub-nodes before this node
	TArray<UXMSNode*> SubNodes;
	GetAllSubNodes(SubNodes);
	for (UXMSNode* SubNode : SubNodes)
	{
		if (SubNode) SubNode->RemoveFromParent();
	}

	// Clean up this node
	PreRemovedFromParent();
	
	ParentNode = nullptr;
	PathFromParent.Reset();

	PostRemovedFromParent();
	RemovedFromParentDelegate.Broadcast();
}

void UXMSNode::ReparentNode(UXMSNode* InParentNode, const FXMSNodePathElement& InPathFromParent)
{
	ParentNode = InParentNode;
	PathFromParent = InPathFromParent;
	OnParentSet();
}


