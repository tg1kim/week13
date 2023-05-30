#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#pragma warning(disable: 4326 4996 6001 6031)

#define	NodeWIDTH	1
#define	NodeGAP		1

//#define TESTING			// define for testing
#ifdef TESTING
#define NoNODE		11
#else
#define NoNODE		26
#endif

typedef char* CPtr;
typedef struct Node {
	char  nData;
	Node *lChild;
	Node *rChild;
}	*NodePtr, *TreePtr;

int  MakeTree(TreePtr &pTree, int nData);
void PreorderTrvs(TreePtr pTree, CPtr &sOrder);
void InorderTrvs(TreePtr pTree, CPtr &sOrder);
void PostorderTrvs(TreePtr pTree, CPtr &sOrder);
TreePtr Tree4InPreorder(char* pLDR, char* pDLR, int nCtr);
TreePtr Tree4InPostorder(char* pLDT, char* pLRD, int nCtr);
bool EqualTree(TreePtr pTree1, TreePtr pTree2);
void FreeTree(TreePtr pTree);
void ShowTree(TreePtr pTree);
int  CountNode(TreePtr pTree);

void main()
{
#ifdef TESTING
	srand((unsigned)1);
#else
	srand((unsigned)time(NULL));
#endif
	while (1) {
		char sPreorder[NoNODE + 1];
		char sInorder[NoNODE + 1];
		char sPostorder[NoNODE + 1];
		char* pOrder;
		TreePtr pTree = NULL;
		for (int i = 0; i < NoNODE; i++)
			if (MakeTree(pTree, 'A' + i) == false)
				return;
		ShowTree(pTree);
		putchar('\n');
		pOrder = sPreorder;
		PreorderTrvs(pTree, pOrder);
		printf(" Preorder: %s\n", sPreorder);
		pOrder = sInorder;
		InorderTrvs(pTree, pOrder = sInorder);
		printf("  Inorder: %s\n", sInorder);
		pOrder = sPostorder;
		PostorderTrvs(pTree, pOrder);
		printf("Postorder: %s\n", sPostorder);

		TreePtr pTree1 = Tree4InPreorder(sInorder, sPreorder, NoNODE);
		TreePtr pTree2 = Tree4InPostorder(sInorder, sPostorder, NoNODE);

		printf("Equal Test1: %d\n", EqualTree(pTree, pTree1));
		printf("Equal Test2: %d\n", EqualTree(pTree, pTree2));

		FreeTree(pTree);
		FreeTree(pTree1);
		FreeTree(pTree2);

		printf("\nContinue(y/*) ? ");
		char cAns;
		scanf(" %c", &cAns);
		if (cAns != 'y')
			break;
	}
}

int MakeTree(TreePtr& pTree, int nData)
{
	if (pTree == NULL) {
		pTree = new Node;
		if (pTree) {
			pTree->nData = nData;
			pTree->lChild = pTree->rChild = NULL;
		}
		return (int)pTree;
	}
	int nlCtr = CountNode(pTree->lChild), nrCtr = CountNode(pTree->rChild);
	int nChild = nlCtr == nrCtr ? rand() % 2 : (nrCtr + 1) / (nlCtr + 1);
	return MakeTree(nChild ? pTree->lChild : pTree->rChild, nData);
}

void PreorderTrvs(TreePtr pTree, CPtr &sOrder)
{	// 전위 순회를 하여 sOrder에 저장한다
}

void InorderTrvs(TreePtr pTree, CPtr &sOrder)
{	// 중위 순회를 하여 sOrder에 저장한다
}

void PostorderTrvs(TreePtr pTree, CPtr &sOrder)
{	// 후위 순회를 하여 sOrder에 저장한다
}

TreePtr Tree4InPreorder(char *pLDR, char *pDLR, int nCtr)
{
	return NULL;
}

TreePtr Tree4InPostorder(char *pLDR, char *pLRD, int nCtr)
{
	return NULL;
}

bool EqualTree(TreePtr pTree1, TreePtr pTree2)
{
	return true;
}

void FreeTree(TreePtr pTree)
{
	if (pTree) {
		FreeTree(pTree->lChild);
		FreeTree(pTree->rChild);
		free(pTree);
	}
}

int CountNode(TreePtr pTree)
{
	int nCtr = 0;
	if (pTree)
		nCtr = CountNode(pTree->lChild) + CountNode(pTree->rChild) + 1;
	return nCtr;
}

void PrintGap(int nCtr)
{
	for (int i = 0; i < nCtr; i++)
		putchar(0x20);
}

void PrintData(int nData)
{
	static char strFmt[] = { '%', 0x30 + NodeWIDTH, 'c', 0 };
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
	TreePtr arNode1[256], arNode2[256] = { pTree, NULL };
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
			arNode2[2 * i] = arNode1[i] ? arNode1[i]->lChild : NULL;
			arNode2[2 * i + 1] = arNode1[i] ? arNode1[i]->rChild : NULL;
		}
		putchar('\n');
	}
}