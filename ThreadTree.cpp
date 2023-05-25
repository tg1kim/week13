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
{	// inorder로 순회하여 그 결과를 sOrder에 출력하고 노드 수를 반환한다.
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
{	// 스레드 이진 트리를 inorder로 순회하여 그 결과를 sOrder에 출력한다.
	/***
	pNode에 pHead를 저장한다
	while (1) {
		pNode에 pNode Successor를 저장하고 pHead와 같으면
			break;
		sOrder에 "%-3d" 형식으로 pNode->nData를 저장하고 sOrder를 3 증가한다
	}
	***/
}

NodePtr Successor(NodePtr pTree)
{	// 스레드 이진 트리에서 다음 노드를 반환한다
	/***
	pNode에 pTree의 rChild를 저장한다
	pTree의 오른 자식이 존재하면
		pNode의 왼쪽 자식이 존재할 동안
			pNode는 왼쪽 자식을 따라 내려간다
	pNode를 반환한다
	***/
	return NULL;
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