// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/XMSNodeContainer.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * FXMSNodeContainer
 */

/*--------------------------------------------------------------------------------------------------------------------*/
// ContainerManagement

void FXMSNodeContainer::NodeSet(UXMSNode* InNode, UXMSNode* OldNode)
{
	if (OldNode) OldNode->RemovedFromParent_Internal();
	if (InNode) InNode->ReparentNode(Owner.Get(), FXMSNodePathElement(Identifier, 0));
	if (UXMSNodeWithMap* OwnerPtr = Owner.Get())
	{
		if (OwnerPtr->IsInSpellEditorContext())
		{
			OwnerPtr->OnSubNodeChanged(Identifier);
			OwnerPtr->SubNodeChangedDelegate.Broadcast(FXMSNodePathElement(Identifier, 0));
		}
	}
}

// ~ContainerManagement
/*--------------------------------------------------------------------------------------------------------------------*/



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * FXMSMultiNodeContainer
 */

/*--------------------------------------------------------------------------------------------------------------------*/
// ContainerManagement

void FXMSMultiNodeContainer::NodeSet(UXMSNode* InNode, int32 Index, UXMSNode* OldNode)
{
	if (OldNode) OldNode->RemovedFromParent_Internal();
	if (InNode) InNode->ReparentNode(Owner.Get(), FXMSNodePathElement(Identifier, Index));
	if (UXMSNodeWithArray* OwnerPtr = Owner.Get())
	{
		if (OwnerPtr->IsInSpellEditorContext())
		{
			OwnerPtr->OnSubNodeChanged(Identifier, Index);
			OwnerPtr->SubNodeChangedDelegate.Broadcast(FXMSNodePathElement(Identifier, Index));
		}
	}
}

void FXMSMultiNodeContainer::NodeAdded(UXMSNode* InNode, int32 Index)
{
	// We need to call this before we set parent on new node, else there will be an overlapping
	// PathFromParentNode in the parent's node container (this function shift up path index to make
	// space for new node)
	ShiftUpPathIndexes(Index);
		
	if (InNode) InNode->ReparentNode(Owner.Get(), FXMSNodePathElement(Identifier, Index));
	if (UXMSNodeWithArray* OwnerPtr = Owner.Get())
	{
		if (OwnerPtr->IsInSpellEditorContext())
		{
			OwnerPtr->OnSubNodeAdded(Identifier, Index);
			OwnerPtr->SubNodeAddedDelegate.Broadcast(FXMSNodePathElement(Identifier, Index));
		}
	}
}

void FXMSMultiNodeContainer::NodeRemoved(int32 Index, UXMSNode* OldNode)
{
	if (OldNode) OldNode->RemovedFromParent_Internal();

	// We need to call this after we removed old node from parent, else there will be an overlapping
	// PathFromParentNode in the parent's node container (this function shift down path index so it would
	// cover the index of the removed one)
	ShiftDownPathIndexes(Index);
		
	if (UXMSNodeWithArray* OwnerPtr = Owner.Get())
	{
		if (OwnerPtr->IsInSpellEditorContext())
		{
			OwnerPtr->OnSubNodeRemoved(Identifier, Index);
			OwnerPtr->SubNodeRemovedDelegate.Broadcast(FXMSNodePathElement(Identifier, Index));
		}
	}
}

void FXMSMultiNodeContainer::ShiftPathIndex(UXMSNode* Node, int32 Amount)
{
	if (Node)
	{
		Node->PathFromParentNode.Index += Amount;
		
		if (Node->IsInSpellEditorContext())
		{
			Node->PathIndexChangedDelegate.Broadcast(Node->PathFromParentNode.Index);
		}
	}
}

// ~ContainerManagement
/*--------------------------------------------------------------------------------------------------------------------*/


