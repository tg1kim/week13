#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable: 4326 4996 6001 6031)

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
int  InorderTrvs(TreePtr pTree, NodePtr *sOrder);
void MakeThreadTree(NodePtr *inorder);
void ThreadTrvs(TreePtr pHead, char *sOrder);
NodePtr Successor(NodePtr pNode);
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
		for (int i = 1; i <= NoNODE; i++) {
			printf("%02d: ", i);
			if (MakeTree(pHead->lChild, i) == false)
				return;
			putchar('\n');
		}
		NodePtr arrNode[NoNODE + 2];
		arrNode[0] = arrNode[NoNODE + 1] = pHead;
		InorderTrvs(pHead->lChild, arrNode + 1);
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
	int nLeft = rand() % 2;
	putchar(nLeft ? 'L' : 'R');
	return MakeTree(nLeft ? pTree->lChild : pTree->rChild, nData);
}

int InorderTrvs(TreePtr pTree, NodePtr *arrNode)
{	// inorder�� ��ȸ�Ͽ� �� ����� sOrder�� ����ϰ� ��� ���� ��ȯ�Ѵ�.
	int nCtr = 0;
	if (pTree) {
		nCtr += InorderTrvs(pTree->lChild, arrNode);
		arrNode[nCtr++] = pTree;
		nCtr += InorderTrvs(pTree->rChild, arrNode + nCtr);
	}
	return nCtr;
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
{	// ������ ���� Ʈ���� inorder�� ��ȸ�Ͽ� �� ����� sOrder�� ����Ѵ�.
	/***
	pNode�� pHead�� �����Ѵ�
	while (1) {
		pNode�� pNode Successor�� �����ϰ� pHead�� ������
			break;
		sOrder�� "%-3d" �������� pNode->nData�� �����ϰ� sOrder�� 3 �����Ѵ�
	}
	***/
}

NodePtr Successor(NodePtr pTree)
{	// ������ ���� Ʈ������ ���� ��带 ��ȯ�Ѵ�
	/***
	pNode�� pTree�� rChild�� �����Ѵ�
	pTree�� ���� �ڽ��� �����ϸ�
		pNode�� ���� �ڽ��� ������ ����
			pNode�� ���� �ڽ��� ���� ��������
	pNode�� ��ȯ�Ѵ�
	***/
	return NULL;
}

void FreeTree(TreePtr pTree)
{	// ����Ʈ���� ��� ��带 �ǵ����ش�.
	if (pTree) {
		if (pTree->lThread == 0)
			FreeTree(pTree->lChild);
		if (pTree->rThread == 0)
			FreeTree(pTree->rChild);
		free(pTree);
	}
}