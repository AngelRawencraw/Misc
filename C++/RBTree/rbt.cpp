// RBTree.cpp: implementation of the CRBTree class.
//
//////////////////////////////////////////////////////////////////////
#include <iostream>
#include "rbt.h"
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// ���캯��
CRBTree::CRBTree()
{
	m_root = m_NIL = NULL;
	m_Size = 0;
}

// ��������
CRBTree::~CRBTree()
{
	RB_EmptyTree(m_root);
	delete m_NIL;
	m_root = m_NIL = NULL;
	cout << "Empty the tree!\n";
}

// ��ʼ��Ҷ�ӽ��
void CRBTree::RB_InitLeafNode()
{
	m_root = new RBTree(-1);
	m_NIL = new RBTreeNode(-1);
	m_NIL->color = BLACK;  // Ҷ�ӽ����ɫ��Ϊ��ɫ
	m_NIL->parent = NULL;
	m_NIL->left = m_NIL->right = NULL;
	m_root = m_NIL;
	m_root->parent = m_NIL;
}

// ���������
BOOL CRBTree::RB_Insert( int keyVal )
{
	RBTreeNode *pNewNode = new RBTreeNode(keyVal);
	pNewNode->left = m_NIL;
	pNewNode->right = m_NIL;
	RBTreeNode *pNode = m_root;
	RBTreeNode *pPreNode = m_NIL;
	while(pNode != m_NIL)  // ����Ϊ��
	{
		pPreNode = pNode;
		if (keyVal < pNode->key)
		{
			pNode = pNode->left;
		}
		else if (keyVal > pNode->key)
		{
			pNode = pNode->right;
		}
		else{
			delete pNewNode;
			return 0;
		}
	}
	pNewNode->parent = pPreNode;
	if (pPreNode == m_NIL)  // ��Ϊ��
	{
		pNewNode->color = BLACK;
		m_root = pNewNode;
	}
	else
	{
		if (keyVal < pPreNode->key)
		{
			pPreNode->left = pNewNode;
		}
		else
			pPreNode->right = pNewNode;
	}
	m_Size++;
//	cout << "Insert "<< m_Size << " node: " << keyVal << " succeeded!\n";
	RB_Insert_FixedUp(pNewNode);
	return 1;
}

// ɾ�������
BOOL CRBTree::RB_Delete( int keyVal )
{
	RBTreeNode *pDelNode, *pPreNode = m_NIL;
	if (m_root == m_NIL)
	{
		return 0;
	}
// 	pDelNode = m_root;
// 	while(pDelNode != m_NIL)
// 	{
// 		if (keyVal < pDelNode->key)
// 		{
// 			pPreNode = pDelNode;
// 			pDelNode = pDelNode->left;
// 		}
// 		else if (keyVal > pDelNode->key)
// 		{
// 			pPreNode = pDelNode;
// 			pDelNode = pDelNode->right;
// 		}
// 		else
// 			break;
// 	}
	pDelNode = RB_Find(keyVal);
	if (pDelNode == NULL)
	{
		return 0; // û�д˽��
	}
	pPreNode = pDelNode->parent;
	//�Ӹý����������ҳ����Ľ�����������ҳ���С�Ľ�㣬 ���ߵ�ֵ�����滻
	RBTreeNode *pTemp;
	RBTreeNode *pDelChild;
	if (pDelNode->left != m_NIL && pDelNode->right != m_NIL)
	{ // �������ӽ�㣬����������
		pTemp = pDelNode->left;
		while(pTemp->right != m_NIL)
		{
			pTemp = pTemp->right;
		}

		RB_SwapTwoNodes(pTemp, pDelNode);
	
		pDelChild = pTemp->left;
		pDelChild->parent = pTemp->parent;
		if (pTemp->parent->left == pTemp)
		{
			pTemp->parent->left = pDelChild;
		}
		else
			pTemp->parent->right = pDelChild;
	}
	else if (pDelNode->left == m_NIL && pDelNode->right == m_NIL)
	{ // Ҫɾ���Ľ����Ҷ�ӽ��
		if (pPreNode == m_NIL)
		{
			delete m_root;
			m_root = m_NIL;
			m_Size--;
			return 1;
		}
		else
		{
			if (pDelNode == pDelNode->parent->left)
			{
				pPreNode->left = m_NIL;
			}
			else
				pPreNode->right = m_NIL;
			pDelChild = m_NIL;
			pDelChild->parent = pDelNode->parent;
			pTemp = pDelNode;
		}
	}
	else // ��һ���ӽ��
	{ 
		if (pDelNode->left != m_NIL)
		{
			pDelChild = pDelNode->left;
		}
		else 
		{
			pDelChild = pDelNode->right;
		}
		if (pDelChild == pPreNode->left)
		{
			pDelChild->parent = pPreNode;
			pPreNode->left = pDelChild;
		}
		else
		{
			pDelChild->parent = pPreNode;
			pPreNode->right = pDelChild;
		}
		pTemp = pDelNode;	
	}
	if (pTemp->color == BLACK)
	{
		RB_Del_FixedUp(pDelChild);
	}
//	cout << "Deleted node: " << pTemp->key << endl;
	delete pTemp;
	m_Size--;
	return 1;
}

// ����ָ����㣬�ɹ� �Żظý�㣬���򷵻�NULL
RBTreeNode * CRBTree::RB_Find( int keyVal )
{
	RBTreeNode *pNode;
	if (m_root == m_NIL)
	{
		return NULL;
	}
	pNode = m_root;
	while(pNode != m_NIL)
	{
		if (keyVal < pNode->key)
		{
			pNode = pNode->left;
		}
		else if (keyVal > pNode->key)
		{
			pNode = pNode->right;
		}
		else{
//			cout << "Find node: " << keyVal << "succeeded!\n";
			return pNode;
		}
	}
	return NULL;
}

// ��������γɵ��½ṹ�������������ʺͶ�����д���
void CRBTree::RB_Insert_FixedUp( RBTreeNode *&pNode )
{
	while (pNode->parent->color == RED)
	{
		RBTreeNode *pNodeParent = pNode->parent;
		RBTreeNode *pNodePaBro;
		if (pNodeParent->parent->left == pNodeParent) 
			pNodePaBro = pNodeParent->parent->right;
		else
			pNodePaBro = pNodeParent->parent->left;
		if (pNodePaBro->color == RED)
		{  // ���������㶼�Ǻ�ɫ ==>> ��--��  ��--��  �游--��
			pNodeParent->color = BLACK;
			pNodePaBro->color = BLACK;
			pNodeParent->parent->color = RED;
			pNode = pNode->parent->parent;
			if (pNode == m_NIL)
			{
				m_root->color = BLACK;
				return ;
			}
		}
		/// �츸 ������ ����û������
		else if(pNodeParent->parent->left == pNodeParent && pNodeParent->left == pNode)
		{
			pNodeParent->color = BLACK;
			pNodeParent->parent->color = RED;
			RB_Right_Rotate(pNode->parent->parent);
			break;
		}
		else if (pNodeParent->parent->left == pNodeParent && pNodeParent->right == pNode)
		{
			pNode = pNode->parent;
			RB_Left_Rotate(pNode);
		}
		else if (pNodeParent->parent->right == pNodeParent && pNodeParent->left == pNode)
		{
			pNode = pNode->parent;
			RB_Right_Rotate(pNode);
		}
		else 
		{
			pNodeParent->color = BLACK;
			pNodeParent->parent->color = RED;
			RB_Left_Rotate(pNode->parent->parent);
			break;
		}
	}// while
	m_root->color = BLACK;
}

// ɾ�������γɵ��½ṹ�������������ʺͶ�����д���
void CRBTree::RB_Del_FixedUp( RBTreeNode *&pNode )
{
	int nLRFlag;
	RBTreeNode *pBroNode;
	while(pNode != m_root && pNode->color == BLACK)
	{
		if (pNode->parent->left == pNode)
		{
			nLRFlag = 0;
			pBroNode = pNode->parent->right;
		}
		else 
		{
			nLRFlag = 1;
			pBroNode = pNode->parent->left;
		}
		
		//1 ��-red  ���� ��-red  ==>> ��-black
		//2 ��-black  ��-red  ==>> ��-red ��-black ��ת����� 
		if (pBroNode->color == RED)
		{
			pNode->parent->color = BLACK;
			pBroNode->color = BLACK;
			if (nLRFlag == 0)
			{
				RB_Left_Rotate(pNode->parent);
			}
			else
				RB_Right_Rotate(pNode->parent);
		}
		//3 ��-black  ����ֶ  ==>>	��=�� ��=�� �츸=�� ���ϱ���(�ڸ�)
		else if (pBroNode->left->color == BLACK && pBroNode->right->color == BLACK)
		{
			pNode->color = BLACK;
			pBroNode->color = RED;
			pNode->parent->color = BLACK;
			pNode = pNode->parent;  // ���ϱ���
		}
		//4 ��-black  ���ֶ�Һ�ֶ  ==>> ��=��ɫ ��=�� ֶ=�� (��=��) ����ת���ڵ�
		else if (pBroNode->left->color == BLACK && pBroNode->right->color == RED)
		{
			if (nLRFlag == 0)
			{
				pBroNode->color = pNode->parent->color;
				pNode->parent->color = BLACK;
				pNode->color = BLACK;
				pBroNode->right->color = BLACK;				
				RB_Left_Rotate(pNode->parent);
				break;
			}
			else 
			{
				RBTreeNode *pPa = pNode->parent;
				pBroNode->left->color = pNode->parent->color;
				pNode->parent->color = BLACK;
				RB_Left_Rotate(pBroNode);
				RB_Right_Rotate(pPa);
				break;
			}	
		}
		//5	��-black  ���ֶ�Һ�ֶ  ==>> ֶ=��ɫ ��=�� ����ת�� ����ת��
		else if (pBroNode->left->color == RED && pBroNode->right->color == BLACK)
		{
			
			if (nLRFlag == 0)
			{
				RBTreeNode *pPa = pNode->parent;
				pBroNode->left->color = pNode->parent->color;
				pNode->parent->color = BLACK;
				RB_Right_Rotate(pBroNode);
				RB_Left_Rotate(pPa);
				break;
			}
			else 
			{
				pBroNode->color = pNode->parent->color;
				pNode->parent->color = BLACK;
				pNode->color = BLACK;
				pBroNode->right->color = BLACK;				
				RB_Right_Rotate(pNode->parent);
				break;
			}	
		}
		else  //����ֶ����� ת����һ��һ������
		{
			if (nLRFlag == 0)
			{
				pBroNode->left->color = BLACK;
			}
			else
			{
				pBroNode->right->color = BLACK;
			}	
		}
	}
	pNode->color = BLACK;  //�� ==> black
	return;
}

// ��������
void CRBTree::RB_Left_Rotate( RBTreeNode *&pNode )
{
	RBTreeNode *pNodeA = pNode->parent;
	RBTreeNode *pNodeB = pNode->right;
	pNode->right = pNodeB->left;
	pNodeB->left->parent = pNode;
	pNodeB->left = pNode;
	pNode->parent = pNodeB;

	if (pNode == pNodeA->left)
	{  // ���Ӳ�ͬ��
		pNodeA->left = pNodeB;
		pNodeB->parent = pNodeA;
	}
	else if (pNode = pNodeA->right)
	{
		pNodeA->right = pNodeB;
		pNodeB->parent = pNodeA;
	}
	else // m_root == m_NIL
	{
		if (pNodeA == m_NIL)
		{  // pNode ԭ��Ϊ�����
			pNodeB->parent = m_NIL;
			m_root = pNodeB;
		}
	}
//	cout << "RB_Left_Rotate()\n";
}

// ����������
void CRBTree::RB_Right_Rotate( RBTreeNode *&pNode )
{
	RBTreeNode *pNodeA = pNode->parent;
	RBTreeNode *pNodeB = pNode->left;
	pNode->left = pNodeB->right;
	pNodeB->right->parent = pNode;
	pNodeB->right = pNode;
	pNode->parent = pNodeB;
	
	if (pNode == pNodeA->right)
	{  // ���Ӳ�ͬ��
		pNodeA->right = pNodeB;
		pNodeB->parent = pNodeA;
	}
	else if (pNode = pNodeA->left)
	{
		pNodeA->left = pNodeB;
		pNodeB->parent = pNodeA;
	}
	else // m_root == m_NIL
	{
		if (pNodeA == m_NIL)
		{  // pNodeA ԭ��Ϊ�����
			pNodeB->parent = m_NIL;
			m_root = pNodeB;
		}
	}
//	cout << "RB_Right_Rotate()\n";
}

void CRBTree::RB_Print()
{
	if (m_root == m_NIL)
	{
//		cout << "��Ϊ�գ�\n";
		return ;
	}
	RB_Print(m_root);
	cout << endl;
}

void CRBTree::RB_Print( RBTreeNode *&pNode )
{
	if (pNode != m_NIL)
	{
		cout << pNode->key << "(" << pNode->color << ")  ";
		RB_Print(pNode->left);
		RB_Print(pNode->right);
	}
}

void CRBTree::RB_SwapTwoNodes( RBTreeNode *&pNode1, RBTreeNode *&pNode2 )
{
	int t = pNode1->key;
	pNode1->key = pNode2->key;
	pNode2->key = t;
}

void CRBTree::RB_EmptyTree( RBTreeNode *&pNode )
{
	if (pNode != m_NIL)
	{
		RB_EmptyTree(pNode->left);
		RB_EmptyTree(pNode->right);
		delete pNode;
	}
}

