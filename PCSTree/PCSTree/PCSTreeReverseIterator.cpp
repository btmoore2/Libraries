#include "PCSTreeReverseIterator.h"

namespace EngineSpace
{
	PCSTreeReverseIterator::PCSTreeReverseIterator(PCSNode* rootNode)
		:root(rootNode), current(nullptr)
	{

	}

	PCSNode* PCSTreeReverseIterator::First()
	{
		//End node can be deleted, so always start from the root.
		this->current = this->root;
		while (this->current->getForward() != nullptr)
		{
			this->current = this->current->getForward();
		}
		return this->current;
	}

	PCSNode* PCSTreeReverseIterator::Next()
	{
		if (this->current != nullptr)
		{
			this->current = this->current->getReverse();
		}
		else
		{
			//Set to the end node.
			this->current = this->First();
		}
		return current;
	}

	bool PCSTreeReverseIterator::isDone()
	{
		if (this->current->getReverse() == nullptr)
		{
			return true;
		}
		return false;
	}

	PCSNode* PCSTreeReverseIterator::currentItem()
	{
		return this->current;
	}

}