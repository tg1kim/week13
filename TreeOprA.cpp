#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4326 4996 6001 6031)

#define	NodeWIDTH	4
#define	NodeGAP		1
#define SWAP(x, y)	x = (TreePtr)((unsigned int)x ^ (unsigned int)y);	\
					y = (TreePtr)((unsigned int)x ^ (unsigned int)y);	\
					x = (TreePtr)((unsigned int)x ^ (unsigned int)y);

typedef struct Node1 {			// 트리에서 노드
	char   sData[5];
	Node1 *lChild;
	Node1 *rChild;
}	*Node1Ptr, Tree, *TreePtr;

typedef struct Node2 {			// 스택, 큐에서 노드
	TreePtr pData;
	Node2  *link;
}	*Node2Ptr, Stack, *StackPtr, Queue, *QueuePtr;

int  InsertNode(TreePtr& pTree, const char *sData);
void Inorder(TreePtr pTree);
void Preorder(TreePtr pTree);
void Postorder(TreePtr pTree);
void IterativeInorder(TreePtr pTree);
void IterativePreorder(TreePtr pTree);
void LevelOrder(TreePtr pTree);
TreePtr CopyTree(TreePtr pTree);
bool EqualTree(TreePtr pTree, TreePtr pTree1);
void SwapTree(TreePtr pTree);
void ShowTree(TreePtr pTree);
void FreeTree(TreePtr pTree);

void main()
{
	const char *sMonth[] =  {"July", "Feb", "Aug", "May", "Oct", "Nov", "Dec", "Mar", "Sept", "Jan", "June", "Apr"};
	TreePtr pTree0 = NULL;
	for (int i = 0; i < sizeof(sMonth) / sizeof(sMonth[0]); i++)
		InsertNode(pTree0, sMonth[i]);
	printf("[pTree0]\n");
	ShowTree(pTree0);
	putchar('\n');
	char sCmnd[10];
	TreePtr pTree1 = NULL;
	while (1) {
		printf("[01i nrotulcqsx e] ? ");
		gets_s(sCmnd);
		switch (*sCmnd) {
		case '0':
		case '1':
			printf("[pTree%c]\n", *sCmnd);
			ShowTree(*sCmnd == '0' ? pTree0 : pTree1);
			break;
		case 'i':
			printf("Data ? ");
			gets_s(sCmnd);
			if (InsertNode(pTree0, sCmnd))
				printf("Inserted ...\n");
			break;
		case 'n':
			printf("     Inorder Trav:");
			Inorder(pTree0);
			printf("\n");
			break;
		case 'r':
			printf("    Preorder Trav:");
			Preorder(pTree0);
			printf("\n");
			break;
		case 'o':
			printf("   Postorder Trav:");
			Postorder(pTree0);
			printf("\n");
			break;
		case 't':
			printf("Iter inorder Trav:");
			IterativeInorder(pTree0);
			printf("\n");
			break;
		case 'u':
			printf("Ite Preorder Trav:");
			IterativePreorder(pTree0);
			printf("\n");
			break;
		case 'l':
			printf(" Level order Trav:");
			LevelOrder(pTree0);
			printf("\n");
			break;
		case 'c':
			if (pTree1)
				FreeTree(pTree1);
			pTree1 = CopyTree(pTree0);
			printf("Copyed ...\n");
			break;
		case 'q':
			printf("%s\n", EqualTree(pTree0, pTree1) ? "Yes" : "No");
			break;
		case 's':
			SwapTree(pTree0);
			printf("Swapped ...\n");
			break;
		case 'x':
			printf("Exchanged ...\n");
			SWAP(pTree0, pTree1);
			break;
		case 'e':
			if (pTree0)
				FreeTree(pTree0);
			if (pTree1)
				FreeTree(pTree1);
			printf("Freed ...\n");
			return;
		default:
			printf("Invalid command ....\n");
		}
		putchar('\n');
	}
}

int InsertNode(TreePtr& pTree, const char *sData)
{	// return true for success
	if (pTree == NULL) {
		pTree = (TreePtr)malloc(sizeof(Node1));
		if (pTree) {
			pTree->lChild = pTree->rChild = NULL;
			strcpy(pTree->sData, sData);
		}
		return pTree != NULL;
	}
	int nCond = strcmp(sData, pTree->sData);
	int nResult = false;
	if (nCond < 0)
		nResult = InsertNode(pTree->lChild, sData);
	else if (nCond > 0)
		nResult = InsertNode(pTree->rChild, sData);
	return nResult;
}

void Inorder(TreePtr pTree)
{
	if (pTree) {
		Inorder(pTree->lChild);			// L
		printf(" %s", pTree->sData);	// D
		Inorder(pTree->rChild);			// R
	}
} 

void Preorder(TreePtr pTree)
{
	if (pTree) {
		printf(" %s", pTree->sData);	// D
		Preorder(pTree->lChild);		// L
		Preorder(pTree->rChild);		// R
	}
}

void Postorder(TreePtr pTree)
{
	if (pTree) {
		Postorder(pTree->lChild);		// L
		Postorder(pTree->rChild);		// R
		printf(" %s", pTree->sData);	// D
	}
}

void Push(StackPtr& pStack, TreePtr pTree)
{	// 첫 노드로 삽입
	Node2Ptr pNew = (Node2Ptr)malloc(sizeof(Node2));
	if (pNew) {
		pNew->pData = pTree;
		pNew->link = pStack;
		pStack = pNew;
	}
}

TreePtr Pop(StackPtr& pStack)
{	// 첫 노드를 삭제
	TreePtr pItem = NULL;
	if (pStack) {
		Node2Ptr pDel = pStack;
		pItem = pDel->pData;
		pStack = pDel->link;
		free(pDel);
	}
	return pItem;
}

// 큐를 마지막 노드를 가리키는 원형 연결 리스트로 표현
void AddQ(QueuePtr& pQueue, TreePtr pItem)
{	// 마지막 노드로 삽입
	Node2Ptr pNew = (Node2Ptr)malloc(sizeof(Node2));
	if (pNew) {
		pNew->pData = pItem;
		if (pQueue) {
			pNew->link = pQueue->link;
			pQueue->link = pNew;
		}
		else
			pNew->link = pNew;
		pQueue = pNew;
	}
}

TreePtr DeleteQ(QueuePtr& pQueue)
{	// 첫 노드를 삭제
	TreePtr pItem = NULL;
	if (pQueue) {
		Node2Ptr pDel = pQueue->link;
		pItem = pDel->pData;
		if (pQueue == pDel)
			pQueue = NULL;
		else
			pQueue->link = pDel->link;
		free(pDel);
	}
	return pItem;
}

void IterativeInorder(TreePtr pTree)
{
	StackPtr pStack = NULL;
	while (1) {
		while (pTree) {
			Push(pStack, pTree);
			pTree = pTree->lChild;
		}
		pTree = Pop(pStack);
		if (pTree == NULL)
			return;
		printf(" %s", pTree->sData);
		pTree = pTree->rChild;
	}
}

void IterativePreorder(TreePtr pTree)
{
	StackPtr pStack = NULL;
	while (1) {
		while (pTree) {
			Push(pStack, pTree);
			printf(" %s", pTree->sData);
			pTree = pTree->lChild;
		}
		pTree = Pop(pStack);
		if (pTree == NULL)
			return;
		pTree = pTree->rChild;
	}
}

void LevelOrder(TreePtr pTree)
{
	QueuePtr pQueue = NULL;
	if (pTree) {
		AddQ(pQueue, pTree);
		while (1) {
			if ((pTree = DeleteQ(pQueue)) == NULL)
				break;
			printf(" %s", pTree->sData);
			if (pTree->lChild)
				AddQ(pQueue, pTree->lChild);
			if (pTree->rChild)
				AddQ(pQueue, pTree->rChild);
		}
	}
}

TreePtr CopyTree(TreePtr pTree)
{
	TreePtr pTree1 = NULL;
	if (pTree) {
		pTree1 = (TreePtr)malloc(sizeof(Tree));
		if (pTree1) {
			strcpy(pTree1->sData, pTree->sData);
			pTree1->lChild = CopyTree(pTree->lChild);
			pTree1->rChild = CopyTree(pTree->rChild);
		}
	}
	return pTree1;
}

bool EqualTree(TreePtr pTree1, TreePtr pTree2)
{
	if (pTree1 == NULL && pTree2 == NULL)
		return true;
	if (pTree1 == NULL || pTree2 == NULL)
		return false;
	return strcmp(pTree1->sData, pTree2->sData) == 0 &&
		   EqualTree(pTree1->lChild, pTree2->lChild) &&
		   EqualTree(pTree1->rChild, pTree2->rChild);
}

void SwapTree(TreePtr pTree)
{
	if (pTree) {
		SwapTree(pTree->lChild);
		SwapTree(pTree->rChild);
		SWAP(pTree->lChild, pTree->rChild);
	}
}

void FreeTree(TreePtr pTree)
{
	if (pTree) {
		FreeTree(pTree->lChild);
		FreeTree(pTree->rChild);
		free(pTree);
	}
}

void PrintGap(int nCtr)
{
	for (int i = 0; i < nCtr; i++)
		putchar(0x20);
}

void PrintData(char *sData)
{
	static char strFmt[] = { '%', '-', 0x30 + NodeWIDTH, 's', 0 };
	printf(strFmt, sData);
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
			arNode1[i] ? PrintData(arNode1[i]->sData) : PrintGap(NodeWIDTH);
			nGapSum = nGapNow + NodeWIDTH;
			arNode2[2 * i] = arNode1[i] ? arNode1[i]->lChild : NULL;
			arNode2[2 * i + 1] = arNode1[i] ? arNode1[i]->rChild : NULL;
		}
		putchar('\n');
	}
}