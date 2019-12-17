#pragma once

#define ASSERT_NODETYPE(T) static_assert(std::is_base_of<CNode, T>::value, "class of pNode must inherit CNode")

class CNodeList{
public:
	class CNode{
	public:
		CNode *Next() const;
		void InsertAfter(CNode *pNext);
		void RemoveFromList();

	protected:
		CNode();
		~CNode();

	private:
		friend class CNodeList;
		CNode *m_pNext;
		CNode *m_pPre;
		CNodeList *m_pList;
	};

	CNodeList();
	CNode *Head() const;
	void Append(CNode *pNode);
	void Insert(CNode *pNode, CNode *pAfterThisNode);
	CNode *RemoveTail();
	CNode *Get(size_t nIndex);
	bool Empty() const;
	size_t Size() const;

private:
	void Remove(CNode *pNode);
	CNode *m_pHead;
	size_t m_nNumOfNodes;
};

template<typename T>
class TNodeList : public CNodeList{
public:
	TNodeList();
	T *Head() const;
	static T *Next(const T *pNode); //return specific node's next node
	T *RemoveTail();
};

template<typename T> TNodeList<T>::TNodeList()
{
	ASSERT_NODETYPE(T);
};

template<typename T> T *TNodeList<T>::Head() const
{
	return static_cast<CNode*>(CNodeList::Head());
}

template<typename T> T *TNodeList<T>::Next(const T *pNode)
{
	return static_cast<T*>(pNode->Next());
}

template<typename T> T *TNodeList<T>::RemoveTail()
{
	return static_cast<T*>(CNodeList::RemoveTail());
}

