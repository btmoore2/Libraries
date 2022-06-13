#include "PCSTree.h"

namespace EngineSpace
{
	PCSTree::PCSTree()
		:pRoot(nullptr)
	{
		mInfo.currNumLevels = 0;
		mInfo.currNumNodes = 0;
		mInfo.maxNumLevels = 0;
		mInfo.maxNumNodes = 0;
	};

	PCSTree::~PCSTree()
	{

	};

	// Get root node of tree
	PCSNode* PCSTree::GetRoot() const
	{
		return pRoot;
	}

	void PCSTree::Insert(PCSNode* const pInNode, PCSNode* const pParent)
	{
		int Level = 1;
		//If no root, add as root. 
		if (pRoot == nullptr)
		{
			pRoot = pInNode;
		}
		//Otherwise add to the pParent list
		else
		{
			PCSNode* OldChild = pParent->getChild();
			pParent->setChild(pInNode);
			pInNode->setParent(pParent);
			if (OldChild != nullptr)
			{
				OldChild->setPrevSibling(pInNode);
				pInNode->setNextSibling(OldChild);
			}

			//Forward will always be the parent's forward, so we can use to update reverse as well. 
			PCSNode* OldForward = pParent->getForward();

			if (OldForward != nullptr)
			{
				pInNode->setForward(OldForward);
				OldForward->setReverse(pInNode);
			}

			pInNode->setReverse(pParent);
			pParent->setForward(pInNode);

			PCSNode* LevelCount = pParent;
			//Figure out current level
			while (LevelCount != nullptr)
			{
				LevelCount = LevelCount->getParent();
				Level++;
			}
		}

		//Update Node data
		mInfo.currNumNodes++;

		//Update Level if needed
		if (mInfo.currNumLevels < Level)
		{
			mInfo.currNumLevels = Level;
		}

		//Update Max info
		if (mInfo.maxNumNodes < mInfo.currNumNodes)
		{
			mInfo.maxNumNodes = mInfo.currNumNodes;
		}
		if (mInfo.maxNumLevels < mInfo.currNumLevels)
		{
			mInfo.maxNumLevels = mInfo.currNumLevels;
		}
	}

	// Remove
	void PCSTree::Remove(PCSNode* const pInNode)
	{
		PCSNode* Prev = pInNode->getPrevSibling();
		PCSNode* Next = pInNode->getNextSibling();
		PCSNode* Parent = pInNode->getParent();
		PCSNode* Child = pInNode->getChild();

		//Remove the whole child list
		while (Child != nullptr)
		{
			Remove(Child);
			Child = pInNode->getChild();
		}

		//Updating Forward/Reverse here lets the Children pass up their links. 

		PCSNode* Reverse = pInNode->getReverse();
		PCSNode* Forward = pInNode->getForward();

		//If Reverse is null, this is the root so we don't need to update.
		if (Reverse != nullptr)
		{
			//Check if this is the last node
			if (Forward == nullptr)
			{
				Reverse->setForward(nullptr);
			}
			//Otherwise Forward will still exist, so we can just update the links around this node.
			else
			{
				Reverse->setForward(Forward);
				Forward->setReverse(Reverse);
			}
		}

		//Check and move parents to next child (or null)
		if (Parent != nullptr)
		{
			if (Parent->getChild() == pInNode)
			{
				Parent->setChild(Next);
			}
		}

		if (Prev != nullptr)
		{
			Prev->setNextSibling(Next);
		}

		if (Next != nullptr)
		{
			Next->setPrevSibling(Prev);
		}

		//Clean the Node, Child cleaned from delete
		pInNode->setParent(nullptr);
		pInNode->setNextSibling(nullptr);
		pInNode->setPrevSibling(nullptr);
		pInNode->setForward(nullptr);
		pInNode->setReverse(nullptr);
		pInNode->setName("");

		mInfo.currNumNodes--;

		int MaxLevel = 0;

		if (pInNode != pRoot)
		{
			PCSNode* CheckLevels = pRoot;
			int NodeCheck = 0;
			int CurrLevel = 1;

			while (NodeCheck < mInfo.currNumNodes)
			{
				while (CheckLevels->getChild() != nullptr)
				{
					CheckLevels = CheckLevels->getChild();
					NodeCheck++;
					CurrLevel++;
				}

				if (CurrLevel == mInfo.currNumLevels)
				{
					break;
				}
				else if (CheckLevels->getNextSibling() != nullptr)
				{
					CheckLevels = CheckLevels->getNextSibling();
					NodeCheck++;
				}
				else
				{
					while (CheckLevels->getNextSibling() == nullptr && CheckLevels != pRoot)
					{
						CheckLevels = CheckLevels->getParent();
						CurrLevel--;
					}
					CheckLevels = CheckLevels->getNextSibling();
					NodeCheck++;
				}

			}
		}
		else
		{
			this->pRoot = nullptr;
		}

		mInfo.currNumLevels = MaxLevel;

	}

	void PCSTree::GetInfo(Info& info)
	{
		info.currNumLevels = mInfo.currNumLevels;
		info.currNumNodes = mInfo.currNumNodes;
		info.maxNumLevels = mInfo.maxNumLevels;
		info.maxNumNodes = mInfo.maxNumNodes;
	}

}