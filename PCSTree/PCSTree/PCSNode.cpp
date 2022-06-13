#include <string>
#include "PCSNode.h"

namespace EngineSpace
{
	PCSNode::PCSNode()
		:pParent(nullptr), pChild(nullptr), pNextSibling(nullptr), pPrevSibling(nullptr), pForward(nullptr), pReverse(nullptr)
	{
		memset(this->pName, 0, PCSNode::NAME_SIZE);
	}

	PCSNode::PCSNode(const PCSNode& in)
		: pParent(in.pParent), pChild(in.pChild), pNextSibling(in.pNextSibling), pPrevSibling(in.pPrevSibling), pForward(in.pForward), pReverse(in.pReverse)
	{
		memcpy(this->pName, in.pName, PCSNode::NAME_SIZE);
	}

	PCSNode& PCSNode::operator = (const PCSNode& in)
	{
		this->pParent = in.pParent;
		this->pChild = in.pChild;
		this->pNextSibling = in.pNextSibling;
		this->pPrevSibling = in.pPrevSibling;
		this->pForward = in.pForward;
		this->pReverse = in.pReverse;

		memcpy(this->pName, in.pName, PCSNode::NAME_SIZE);

		return *this;
	}

	PCSNode::~PCSNode()
	{

	}


	PCSNode::PCSNode(PCSNode* const pInParent, PCSNode* const pInChild, PCSNode* const pInNextSibling, PCSNode* const pInPrevSibling, const char* const pInName)
		: pParent(pInParent), pChild(pInChild), pNextSibling(pInNextSibling), pPrevSibling(pInPrevSibling), pForward(nullptr), pReverse(nullptr)
	{
		memcpy(this->pName, pInName, PCSNode::NAME_SIZE);
	}

	PCSNode::PCSNode(const char* const pInName)
		: pParent(nullptr), pChild(nullptr), pNextSibling(nullptr), pPrevSibling(nullptr), pForward(nullptr), pReverse(nullptr)
	{
		memcpy(this->pName, pInName, PCSNode::NAME_SIZE);
	}


	void PCSNode::setParent(PCSNode* const pIn)
	{
		this->pParent = pIn;
	}

	void PCSNode::setChild(PCSNode* const pIn)
	{
		this->pChild = pIn;
	}

	void PCSNode::setNextSibling(PCSNode* const pIn)
	{
		this->pNextSibling = pIn;
	}

	void PCSNode::setPrevSibling(PCSNode* const pIn)
	{
		this->pPrevSibling = pIn;
	}

	void PCSNode::setForward(PCSNode* const pIn)
	{
		this->pForward = pIn;
	}

	void PCSNode::setReverse(PCSNode* const pIn)
	{
		this->pReverse = pIn;
	}

	PCSNode* PCSNode::getParent(void) const
	{
		return this->pParent;
	}

	PCSNode* PCSNode::getChild(void) const
	{
		return this->pChild;
	}

	PCSNode* PCSNode::getNextSibling(void) const
	{
		return this->pNextSibling;
	}

	PCSNode* PCSNode::getPrevSibling(void) const
	{
		return this->pPrevSibling;
	}

	PCSNode* PCSNode::getForward(void) const
	{
		return this->pForward;
	}

	PCSNode* PCSNode::getReverse(void) const
	{
		return this->pReverse;
	}

	PCSNode::Code PCSNode::setName(const char* const pInName)
	{
		if (pInName == nullptr)
		{
			return Code(1);
		}

		memcpy(this->pName, pInName, PCSNode::NAME_SIZE - 1);

		return Code(0);
	}

	PCSNode::Code PCSNode::getName(char* const pOutBuffer, unsigned int sizeOutBuffer) const
	{
		if (pOutBuffer == nullptr)
		{
			return Code(1);
		}

		if (sizeOutBuffer < PCSNode::NAME_SIZE)
		{
			memcpy(pOutBuffer, this->pName, sizeOutBuffer - 1);
			pOutBuffer[sizeOutBuffer - 1] = 0;
			return Code(0);
		}

		memcpy(pOutBuffer, this->pName, PCSNode::NAME_SIZE);
		return Code(0);
	}

	int PCSNode::getNumSiblings() const
	{

		if (this->pParent == nullptr)
		{
			return 1;
		}
		else
		{
			int count = 0;
			PCSNode* Counter = this->pParent->getChild();
			while (Counter != nullptr)
			{
				count++;
				Counter = Counter->pNextSibling;
			}
			return count;
		}
	}

	int PCSNode::getNumChildren() const
	{
		if (this->pChild == nullptr)
		{
			return 0;
		}
		else
		{
			return this->pChild->getNumSiblings();
		}
	}

}