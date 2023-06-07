#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable: 4326 4996 6001 6031)

#define	NodeWIDTH	2
#define	NodeGAP		1

typedef struct TNode {
	int nData;
	TNode *lChild;
	TNode *rChild;
}	*TNodePtr, *TreePtr;

void main()
{
	srand((unsigned)time(NULL));
	while (1) {
		printf("Node �� ? ");
		int nCtr;
		scanf("%d", &nCtr);
		if (nCtr <= 0)
			break;
		TreePtr pTree = NULL;
		for (int i = 1; i <= nCtr; i++) {
			int nData = rand() % 100;
			TreePtr MakeTree(TreePtr pTree, int nData);
			pTree = MakeTree(pTree, nData);
		}
		void ShowTree(TreePtr pTree);
		ShowTree(pTree);
		putchar('\n');
		int nNodeCtr[3] = {0, };
		int CountNode(TreePtr pTree, int nCtrs[]);
		CountNode(pTree, nNodeCtr);
		printf("�ܸ� ��� ��: %d\n", nNodeCtr[0]);
		printf("���� ��� ��: %d\n", nNodeCtr[1]);
		printf("  �� ��� ��: %d\n", nNodeCtr[2]);
		putchar('\n');
		void FreeTree(TreePtr);
		FreeTree(pTree);
	}
	printf("Bye, ...\n");
}

int CountNode(TreePtr pTree, int nCtrs[])
{	// [0]: �ܸ� ���, [1]: ���� ���, [2]: �� ���(��ȯ)
	if (pTree) {
		nCtrs[2]++;
		if (pTree->lChild || pTree->rChild) {
			nCtrs[1]++;
			CountNode(pTree->lChild, nCtrs);
			CountNode(pTree->rChild, nCtrs);
		}
		else
			nCtrs[0]++;
	}
	return nCtrs[2];
}

TreePtr MakeTree(TreePtr pTree, int nData)
{
	if (pTree == NULL) {
		pTree = new TNode;
		if (pTree) {
			pTree->nData = nData;
			pTree->lChild = pTree->rChild = NULL;
		}
	}
	else {
		int nl[3] = { 0 }, nr[3] = { 0 };
		int nlCtr = CountNode(pTree->lChild, nl);
		int nrCtr = CountNode(pTree->rChild, nr);
		int nChild = nlCtr == nrCtr ? rand() % 2 : nlCtr > nrCtr;
		if (nChild == 0)
			pTree->lChild = MakeTree(pTree->lChild, nData);
		else
			pTree->rChild = MakeTree(pTree->rChild, nData);
	}
	return pTree;
}

void FreeTree(TreePtr pTree)
{
	if (pTree) {
		FreeTree(pTree->lChild);
		FreeTree(pTree->rChild);
		delete pTree;
	}
}

void PrintGap(int nCtr)
{
	for (int i = 0; i < nCtr; i++)
		putchar(0x20);
}

void PrintData(int nData)
{
	static char strFmt[] = { '%', '0', 0x30 + NodeWIDTH, 'd', 0 };
	printf(strFmt, nData);
}

int TreeHeight(TreePtr pTree)
{
	int nHeight = 0;
	if (pTree) {
		int nlHeight = TreeHeight(pTree->lChild);
		int nrHeight = TreeHeight(pTree->rChild);
		nHeight = (nlHeight > nrHeight ? nlHeight : nrHeight) + 1;
	}
	return nHeight;
}

void ShowTree(TreePtr pTree)
{
	if (pTree == NULL)
		return;
	TreePtr arNode1[513], arNode2[513] = { pTree, NULL };
	int nHeight = TreeHeight(pTree);
	int nMaxLvlNode = 1;
	for (int i = 1; i < nHeight; i++)
		nMaxLvlNode *= 2;
	int nWidth = (NodeWIDTH + NodeGAP) * nMaxLvlNode;
	for (int nLevel = 1, nCtr = 1; nLevel <= nHeight; nLevel++, nCtr *= 2) {
		for (int i = 0; i < nCtr; i++)
			arNode1[i] = arNode2[i];
		float fAvgGap = (float)(nWidth - nCtr * NodeWIDTH) / nCtr;
		for (int i = 0, nGapSum = 0; i < nCtr; i++) {
			int nGapNow = (int)(fAvgGap / 2 + (NodeWIDTH + fAvgGap) * i);
			PrintGap(nGapNow - nGapSum);
			arNode1[i] ? PrintData(arNode1[i]->nData) : PrintGap(NodeWIDTH);
			nGapSum = nGapNow + NodeWIDTH;
			if (nLevel < nHeight) {
				arNode2[2 * i] = arNode1[i] ? arNode1[i]->lChild : NULL;
				arNode2[2 * i + 1] = arNode1[i] ? arNode1[i]->rChild : NULL;
			}
		}
		putchar('\n');
	}
}
