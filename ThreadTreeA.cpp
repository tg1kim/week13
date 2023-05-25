#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable: 4326 4996 6001 6031 28182)

#define DebugON			// define for testing
#ifdef DebugON
#define NoNODE	10
#else
#define NoNODE	15
#endif

typedef struct node {
	int	nData;
	unsigned char lThread : 1;
	unsigned char rThread : 1;
	struct node *lChild;
	struct node *rChild;
}	Node, *NodePtr, *TreePtr;

int  MakeTree(TreePtr& pTree, int nData);
void InorderTrvs(TreePtr pTree, NodePtr* &sOrder);
void MakeThreadTree(NodePtr *inorder);
void ThreadTrvs(TreePtr pHead, char *sOrder);
NodePtr Successor(NodePtr pNode);
void PrintRootLeftRght(TreePtr pTree);
void FreeTree(TreePtr pTree);

void main()
{
#ifdef DebugON
	srand((unsigned)13);
#else
	srand((unsigned)time(NULL));
#endif
	while (1) {
		TreePtr pHead = new Node;
		pHead->lThread = pHead->rThread = 0;
		pHead->rChild = pHead;
		pHead->lChild = NULL;
		for (int i = 1; i <= NoNODE; i++)
			if (MakeTree(pHead->lChild, i) == false)
				return;
		printf("[D, L, R]\n---------\n");
		PrintRootLeftRght(pHead);
		NodePtr arrNode[NoNODE + 2];
		arrNode[0] = arrNode[NoNODE + 1] = pHead;
		NodePtr *parNode = arrNode + 1;
		InorderTrvs(pHead->lChild, parNode);
		MakeThreadTree(arrNode);
		char sOrder[5 * NoNODE];
		ThreadTrvs(pHead, sOrder);
		printf("Thread Trvs: %s\n", sOrder);
		// deallocate tree
		pHead->rChild = NULL;
		FreeTree(pHead);

		printf("\nContinue[y/*] ? ");
		char sAns[10];
		gets_s(sAns);
		if (*sAns != 'y')
			break;
	}
}

int MakeTree(TreePtr& pTree, int nData)
{
	if (pTree == NULL) {
		pTree = (NodePtr)malloc(sizeof(Node));
		if (pTree == NULL)
			return false;
		pTree->nData = nData;
		pTree->lThread = pTree->rThread = 0;
		pTree->lChild = pTree->rChild = NULL;
		return true;
	}
	return MakeTree(rand() % 2 ? pTree->lChild : pTree->rChild, nData);
}

void InorderTrvs(TreePtr pTree, NodePtr* &parNode)
{	// inorder로 순회하여 그 결과를 sOrder에 출력한다.
	if (pTree) {
		InorderTrvs(pTree->lChild, parNode);
		*parNode++ = pTree;
		InorderTrvs(pTree->rChild, parNode);
	}
}

void MakeThreadTree(NodePtr *inorder)
{
	for (int i = 1; i <= NoNODE; i++) {
		NodePtr pNode = inorder[i];
		if (pNode->lChild == NULL) {
			pNode->lChild = inorder[i - 1];
			pNode->lThread = 1;
		}
		if (pNode->rChild == NULL) {
			pNode->rChild = inorder[i + 1];
			pNode->rThread = 1;
		}
	}
}

void ThreadTrvs(TreePtr pHead, char *sOrder)
{	// 스레드 이진 트리를 inorder로 순회하여 그 결과를 sOrder에 출력한다.
	NodePtr pNode = pHead;
	while (1) {
		if ((pNode = Successor(pNode)) == pHead)
			break;
		sOrder += sprintf(sOrder, "%-3d", pNode->nData);
	}
}

NodePtr Successor(NodePtr pTree)
{	// 스레드 이진 트리에서 다음 노드를 반환한다
	NodePtr pNode = pTree->rChild;
	if (pTree->rThread == 0)
		while (pNode->lThread == 0)
			pNode = pNode->lChild;
	return pNode;
}

void PrintRootLeftRght(TreePtr pTree)
{	// 트리의 모든 노드에 대하여 [D, L, R] 형식으로 출력한다(NULL은 -)
	if (pTree) {
		TreePtr plTree = pTree->lThread ? NULL : pTree->lChild;
		TreePtr prTree = pTree->rThread ? NULL : pTree->rChild;
		int nData = pTree->nData;
		if (pTree == prTree) {		// head node
			nData = 0;
			prTree = NULL;
		}
		nData ? printf("[%d,", nData) : printf("[?,");
		plTree ? printf(" %d,", plTree->nData) : printf(" -,");
		prTree ? printf(" %d", prTree->nData) : printf(" -");
		printf("]\n");
		PrintRootLeftRght(plTree);
		PrintRootLeftRght(prTree);
	}
}

void FreeTree(TreePtr pTree)
{	// 이진트리의 모든 노드를 되돌려준다.
	if (pTree) {
		if (pTree->lThread == 0)
			FreeTree(pTree->lChild);
		if (pTree->rThread == 0)
			FreeTree(pTree->rChild);
		free(pTree);
	}
}