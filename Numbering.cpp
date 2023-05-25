#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable: 4326 4996 6001 6031)

//#define DebugON			// define for testing
#ifdef DebugON
#define NoNODE	4
#else
#define NoNODE	15
#endif

typedef char* CharPtr;
typedef struct node1 {
	int	nData;
	struct node1 *lChild;
	struct node1 *rChild;
}	Node1, *Node1Ptr, *TreePtr;

typedef struct node2 {
	TreePtr pData;
	struct node2 *link;
}	Node2, *Node2Ptr, Queue, *QueuePtr;

int  MakeTree(TreePtr& pTree);
void Numbering(TreePtr pTree, int nNo);
void PreorderTrvs(TreePtr pTree, CharPtr& sOrder);
void InorderTrvs(TreePtr pTree, CharPtr& sOrder);
void PostorderTrvs(TreePtr pTree, CharPtr& sOrder);
void LevelOrderTrvs(TreePtr pTree, char* sOrder);
void FreeTree(TreePtr pTree);

void main()
{
#ifdef DebugON
	srand((unsigned)1);
#else
	srand((unsigned)time(NULL));
#endif
	char sTrvslOrder[5 * NoNODE], * pOrder;
	while (1) {
		TreePtr pTree = NULL;
		for (int i = 0; i < NoNODE; i++) {
			if (MakeTree(pTree) == false)
				return;
		}
		// Node numbering
		Numbering(pTree, 1);
		// level order
		LevelOrderTrvs(pTree, sTrvslOrder);
		printf("Level order: %s\n", sTrvslOrder);
		// Preorder
		pOrder = sTrvslOrder;
		PreorderTrvs(pTree, pOrder);
		printf("   Preorder: %s\n", sTrvslOrder);
		// inorder
		pOrder = sTrvslOrder;
		InorderTrvs(pTree, pOrder);
		printf("    Inorder: %s\n", sTrvslOrder);
		// postorder
		pOrder = sTrvslOrder;
		PostorderTrvs(pTree, pOrder);
		printf("  Postorder: %s\n", sTrvslOrder);
		// deallocate tree
		FreeTree(pTree);

		printf("\nContinue[y/*] ? ");
		char sAns[10];
		gets_s(sAns);
		if (*sAns != 'y')
			break;
	}
}

int MakeTree(TreePtr& pTree)
{
	if (pTree == NULL) {
		pTree = (Node1Ptr)malloc(sizeof(Node1));
		if (pTree == NULL)
			return false;
		pTree->lChild = pTree->rChild = NULL;
		return true;
	}
	return MakeTree((rand() % 2) ? pTree->lChild : pTree->rChild);
}

void Numbering(TreePtr pTree, int nNo)
{	// ����Ʈ���� nNo���� Numbering �Ѵ�.
	if (pTree) {
		//pTree�� nData�� nNo�� �����Ѵ�
		//pTree�� lChild�� 2 * nNo���� Numbering �Ѵ�
		// rChild�� 2 * nNo + 1���� Numbering �Ѵ�
	}
}

void PreorderTrvs(TreePtr pTree, CharPtr& sOrder)
{	// preorder�� ��ȸ�Ͽ� �� ����� sOrder�� ����Ѵ�.
	if (pTree) {
		//sOrder�� "%-3d" �������� pTree->nData�� ����Ѵ�
		//pTree�� lChild�� ��ȸ�Ͽ� sOrder�� �߰��Ѵ�
		//pTree�� rChild�� ��ȸ�Ͽ� sOrder�� �߰��Ѵ�
	}
}

void InorderTrvs(TreePtr pTree, CharPtr& sOrder)
{	// inorder�� ��ȸ�Ͽ� �� ����� sOrder�� ����Ѵ�.
	if (pTree) {
		//pTree�� lChild�� ��ȸ�Ͽ� sOrder�� �߰��Ѵ�
		//sOrder�� "%-3d" �������� pTree->nData�� ����Ѵ�
		//pTree�� rChild�� ��ȸ�Ͽ� sOrder�� �߰��Ѵ�
	}
}

void PostorderTrvs(TreePtr pTree, CharPtr& sOrder)
{	// postorder�� ��ȸ�Ͽ� �� ����� sOrder�� ����Ѵ�.
	if (pTree) {
		//pTree�� lChild�� ��ȸ�Ͽ� sOrder�� �߰� �Ѵ�
		//pTree�� rChild�� ��ȸ�Ͽ� sOrder�� �߰� �Ѵ�
		//sOrder�� "%-3d" �������� pTree->nData�� ����Ѵ�
	}
}

// ť�� ������ ��带 ����Ű�� ��ȯ ���� ����Ʈ�� ǥ���ȴ�.
void AddQ(QueuePtr& pQueue, TreePtr pTree)
{	// ������ ���� ����
}

TreePtr DeleteQ(QueuePtr& pQueue)
{	// ù ��带 ����
	return NULL;
}

void LevelOrderTrvs(TreePtr pTree, char *sOrder)
{	// level order�� ��ȸ�Ͽ� �� ����� sOrder�� ����Ѵ�.
	//pQueue�� �ʱ�ȭ �Ѵ�
	if (pTree) {
		//pQueue�� pTree�� �����Ѵ�
		while (1) {
			//pTree�� pQueue�� �����Ͽ� NULL�� �ƴϸ�
			//	break;
			//sOrder�� "%-3d" �������� pTree->nData�� �����ϰ� sOrder�� 3 �����Ѵ�
			//pTree�� lChild�� �����ϸ�
			//	pQueue�� pTree->lChild�� �����Ѵ�
			//pTree�� rChild�� �����ϸ�
			//	pQueue�� pTree->rChild�� �����Ѵ�
		}
	}
}

void FreeTree(TreePtr pTree)
{	// ����Ʈ���� ��� ��带 �ǵ����ش�.
	if (pTree) {
		FreeTree(pTree->lChild);
		FreeTree(pTree->rChild);
		free(pTree);
	}
}