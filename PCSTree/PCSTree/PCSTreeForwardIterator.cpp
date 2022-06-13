#include "PCSTreeForwardIterator.h"

namespace EngineSpace
{
	PCSTreeForwardIterator::PCSTreeForwardIterator(PCSNode* rootNode)
		:root(rootNode), current(rootNode), end(nullptr)
	{
		//Finds the next PCSNode that would be in line without any children and updates the reverse to null. This allows the iterator to only run through its root children. Linkages are fixed in the destructor. 
		PCSNode* rootFindNext = rootNode;
		while (rootFindNext != nullptr)
		{
			if (rootFindNext->getNextSibling() != nullptr)
			{
				this->end = rootFindNext->getNextSibling()->getReverse();
				break;
				//rootFindNext->getNextSibling()->getReverse()->setForward(nullptr);
				//break;
			}

			rootFindNext = rootFindNext->getParent();
		}		
	}

	PCSTreeForwardIterator::~PCSTreeForwardIterator()
	{
		/*
		PCSNode* rootFindNext = root;
		while (rootFindNext != nullptr)
		{
			if (rootFindNext->getNextSibling() != nullptr)
			{
				rootFindNext->getNextSibling()->getReverse()->setForward(rootFindNext->getNextSibling());
				break;
			}

			rootFindNext = rootFindNext->getParent();
		}*/
	}

	PCSNode* PCSTreeForwardIterator::First()
	{
		this->current = this->root;
		return this->root;
	}

	PCSNode* PCSTreeForwardIterator::Next()
	{
		//This will either be nulltptr or the end node previously set.
		if (this->current == this->end)
		{
			return nullptr;
		}

		this->current = this->current->getForward();
		return this->current;

		/*
		if (this->current != nullptr)
		{
			this->current = this->current->getForward();
		}
		else
		{
			this->current = this->root;
		}

		return this->current;*/
	}

	bool PCSTreeForwardIterator::isDone()
	{
		if (this->current == this->end)
		{
			return true;
		}
		/*
		if (this->current->getForward() == nullptr)
		{
			return true;
		}*/
		return false;
	}

	PCSNode* PCSTreeForwardIterator::currentItem()
	{
		return this->current;
	}
}