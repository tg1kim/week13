#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4326 4996 6001 6031)

#define SWAP(x, y)	x = (TreePtr)((unsigned int)x ^ (unsigned int)y);	\
					y = (TreePtr)((unsigned int)x ^ (unsigned int)y);	\
					x = (TreePtr)((unsigned int)x ^ (unsigned int)y);

typedef struct node1 {			// 트리에서 노드
	char sData[5];
	struct node1 *lChild;
	struct node1 *rChild;
}	Node1, *Node1Ptr, Tree, *TreePtr;

typedef struct node2 {			// 스택, 큐에서 노드
	TreePtr pData;
	struct node2 *link;
}	Node2, *Node2Ptr, Stack, *StackPtr, Queue, *QueuePtr;

int InsertNode(TreePtr& pTree, const char *sData);
void Inorder(TreePtr pTree);
void Preorder(TreePtr pTree);
void Postorder(TreePtr pTree);
void IterativeInorder(TreePtr pTree);
void IterativePreorder(TreePtr pTree);
void LevelOrder(TreePtr pTree);
TreePtr CopyTree(TreePtr pTree);
int EqualTree(TreePtr pTree, TreePtr pTree1);
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
		printf("\n[i nrotulcqsx e] ? ");
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
			pTree0 = (TreePtr)((unsigned)pTree0 ^ (unsigned)pTree1);
			pTree1 = (TreePtr)((unsigned)pTree0 ^ (unsigned)pTree1);
			pTree0 = (TreePtr)((unsigned)pTree0 ^ (unsigned)pTree1);
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
	if (nCond < 0)
		return InsertNode(pTree->lChild, sData);
	if (nCond > 0)
		return InsertNode(pTree->rChild, sData);
	return false;
}

void Inorder(TreePtr pTree)
{
} 

void Preorder(TreePtr pTree)
{
}

void Postorder(TreePtr pTree)
{
}

void Push(StackPtr& pStack, TreePtr pTree)
{	// 첫 노드로 삽입
}

TreePtr Pop(StackPtr& pStack)
{	// 첫 노드를 삭제
	return NULL;
}

// 큐를 마지막 노드를 가리키는 원형 연결 리스트로 표현
void AddQ(QueuePtr& pQueue, TreePtr pTree)
{	// 마지막 노드로 삽입
}

TreePtr DeleteQ(QueuePtr& pQueue)
{	// 첫 노드를 삭제
	return NULL;
}

void IterativeInorder(TreePtr pTree)
{
	/***
	pStack을 초기화 한다
	while (1) {
		while (pTree) {
			pStack에 pTree를 push한다
			pTree의 lChild를 따라간다
		}
		pTree에 pStack을 pop한다
		if (pTree == NULL)
			return;
		pTree->sData를 출력한다
		pTree의 rChild를 따라간다
	}
	***/
}

void IterativePreorder(TreePtr pTree)
{
	/***
	pStack을 초기화 한다
	while (1) {
		while (pTree) {
			pStack에 pTree를 push한다
			pTree->sData를 출력한다
			pTree의 lChild를 따라간다
		}
		pTree에 pStack을 pop한다
		if (pTree == NULL)
			return;
		pTree의 rChild를 따라간다
	}
	***/
}

void LevelOrder(TreePtr pTree)
{
}

TreePtr CopyTree(TreePtr pTree)
{
	return NULL;
}

int EqualTree(TreePtr pTree1, TreePtr pTree2)
{
	return true;
}

void SwapTree(TreePtr pTree)
{
}

void FreeTree(TreePtr pTree)
{
}

#define	NodeWIDTH	4
#define	NodeGAP		1

void PrintGap(int nCtr)
{
	for (int i = 0; i < nCtr; i++)
		putchar(0x20);
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
			if (arNode1[i])
				printf("%-4s", arNode1[i]->sData);
			else
				PrintGap(NodeWIDTH);
			nGapSum = nGapNow + NodeWIDTH;
			arNode2[2 * i] = arNode1[i] ? arNode1[i]->lChild : NULL;
			arNode2[2 * i + 1] = arNode1[i] ? arNode1[i]->rChild : NULL;
		}
		putchar('\n');
	}
}