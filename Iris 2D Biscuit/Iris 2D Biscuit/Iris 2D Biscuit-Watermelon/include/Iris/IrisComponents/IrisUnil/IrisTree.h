#ifndef _H_IRISTREE_
#define _H_IRISTREE_

#include <string>
#include <list>
#include <map>
using namespace std;

template<class T>
class IrisTree
{
public:
	template<class T>
	struct Node {
		T m_tData;
		map<string, Node<T>*> m_mpChildNodes;

		Node<T>* GetNodeByName(const string& strName) {
			if (m_mpChildNodes.find(strName) != m_mpChildNodes.end()) {
				return m_mpChildNodes[strName];
			}
			return nullptr;
		}

		bool AddChildNode(const string& strName, const T& tData){
			Node<T>* pNode = new Node<T>();
			pNode->m_tData = tData;
			m_mpChildNodes.insert(pair<string, Node<T>*>(strName, pNode));
			return true;
		}
	};

private:

	void _Delete(Node<T>* pCurNode);

public:

	Node<T>* m_pRoot;

	bool AddNode(list<string> lsRoute, const string& strName, const T& tData);
	bool GetNodeData(list<string> lsRoute, T& tData);

	IrisTree();
	~IrisTree();
};


template <class T>
IrisTree<T>::IrisTree() {
	m_pRoot = new Node<T>();
}

template <class T>
void IrisTree<T>::_Delete(Node<T>* pCurNode) {
	if (!(pCurNode->m_mpChildNodes.empty())) {
		return;
	}
	
	for (auto it = pCurNode->m_mpChildNodes.begin(); it != pCurNode->m_mpChildNodes.end(); ++it) {
		_Delete((it)->second);
	}
	delete pCurNode;
}

template <class T>
bool IrisTree<T>::AddNode(list<string> lsRoute, const string& strName, const T& tData) {
	Node<T>* pCurNode = m_pRoot;
	Node<T>* pTmpNode = nullptr;
	for (auto cur_name : lsRoute) {
		if (pTmpNode = pCurNode->GetNodeByName(cur_name)) {
			pCurNode = pTmpNode;
		}
		else {
			return false;
		}
	}
	pCurNode->AddChildNode(strName, tData);
	return true;
}

template <class T>
bool IrisTree<T>::GetNodeData(list<string> lsRoute, T& tData) {
	Node<T>* pCurNode = m_pRoot;
	Node<T>* pTmpNode = nullptr;
	for (auto cur_name : lsRoute) {
		if (pTmpNode = pCurNode->GetNodeByName(cur_name)) {
			pCurNode = pTmpNode;
		}
		else {
			return false;
		}
	}
	tData = pCurNode->m_tData;
	return true;
}

template <class T>
IrisTree<T>::~IrisTree(){
	_Delete(m_pRoot);
}

#endif