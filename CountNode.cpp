#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable: 4326 4996 6001 6031)

typedef struct TNode {
	int nData;
	struct TNode *lChild;
	struct TNode *rChild;
}	TNode, *TNodePtr, Tree, *TreePtr;

void main()
{
	srand((unsigned)time(NULL));
	while (1) {
		printf("Node 수 ? ");
		int nCtr;
		scanf("%d", &nCtr);
		if (nCtr <= 0)
			break;
		TreePtr pTree = NULL;
		for (int i = 1; i <= nCtr; i++) {
			TreePtr InsertBST(TreePtr, int);
			int nData = rand() % 100;
			printf("%2d: ", nData);
			pTree = InsertBST(pTree, nData);
			putchar('\n');
		}
		putchar('\n');
		int nNodeCtr[3] = {0, };
		void CountNode(TreePtr pTree, int nCtrs[]);
		CountNode(pTree, nNodeCtr);
		printf("단말 노드 수: %d\n", nNodeCtr[0]);
		printf("내부 노드 수: %d\n", nNodeCtr[1]);
		printf("  총 노드 수: %d\n", nNodeCtr[2]);
		putchar('\n');
		void FreeBST(TreePtr);
		FreeBST(pTree);
	}
	printf("Bye, ...\n");
}

TreePtr InsertBST(TreePtr pTree, int nData)
{
	if (pTree == NULL) {
		pTree = new TNode;
		if (pTree) {
			pTree->nData = nData;
			pTree->lChild = pTree->rChild = NULL;
		}
	}
	else if (nData < pTree->nData) {
		putchar('L');
		pTree->lChild = InsertBST(pTree->lChild, nData);
	}
	else if (nData > pTree->nData) {
		putchar('R');
		pTree->rChild = InsertBST(pTree->rChild, nData);
	}
	else
		putchar('-');
	return pTree;
}

void CountNode(TreePtr pTree, int nCtrs[])
{	// [0]: 단말 노드, [1]: 내부 노드, [2]: 총 노드
	if (pTree) {
		//총 노드 수를 1 증가한다
		//pTree의 lChild와 rChild 중 하나라도 있으면
		//	내부 노드 수를 1 증가한다
		//	pTree의 lChild에서 노드 수를 nCtrs에 증가시킨다
		//	pTree의 rChild에서 노드 수를 nCtrs에 증가시킨다
		//아니면
		//	단말 노드 수를 1 증가한다
	}
}

void FreeBST(TreePtr pTree)
{
	if (pTree) {
		FreeBST(pTree->lChild);
		FreeBST(pTree->rChild);
		delete pTree;
	}
}
