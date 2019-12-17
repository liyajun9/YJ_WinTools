#include "stdafx.h"
#include "NodeList.h"

CNodeList::CNode::CNode():m_pNext(NULL),
	m_pPre(NULL),
	m_pList(NULL)
{
}

CNodeList::CNode::~CNode()
{
	RemoveFromList();
}

void CNodeList::CNode::RemoveFromList()
{
	if(m_pPre){
		m_pPre->m_pNext = m_pNext;
	}
	if(m_pNext){
		m_pNext->m_pPre = m_pPre;
	}

	m_pList = NULL;
}

CNodeList::CNode* CNodeList::CNode::Next() const
{
	return m_pNext;
}

void CNodeList::CNode::InsertAfter(CNodeList::CNode *pNext)
{
	pNext = m_pNext;
	if(pNext)
		pNext->m_pPre = this;
}

CNodeList::CNodeList() : m_pHead(NULL), 
	m_nNumOfNodes(0)
{
}

CNode *CNodeList::Head() const
{
	return m_pHead;
}

void CNodeList::Append(CNode *pNode)
{

}

void CNodeList::Insert(CNode *pNewNode, CNode *pAfterThisNode)
{
	if(pAfterThisNode && pNewNode){
		pNewNode->m_pList = this;
		pNewNode->InsertAfter(pAfterThisNode->m_pNext);
		pAfterThisNode->InsertAfter(pNewNode);
		++m_nNumOfNodes;
	}
}

CNode *RemoveTail();
CNode *Get(size_t nIndex);
bool Empty() const;
size_t Size() const;

private:
	void Remove(CNode *pNode);