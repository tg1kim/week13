#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable: 4326 4996 6001 6031)

//#define DebugON			// define for testing
#ifdef DebugON
#define NoNODE	4
#else
#define NoNODE	31
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

int  MakeTree(TreePtr &pTree, int nData);
void Numbering(TreePtr pTree, int nNo);
void PreorderTrvs(TreePtr pTree, CharPtr &sOrder);
void InorderTrvs(TreePtr pTree, CharPtr &sOrder);
void PostorderTrvs(TreePtr pTree, CharPtr &sOrder);
void LevelOrderTrvs(TreePtr pTree, char *sOrder);
void FreeTree(TreePtr pTree);
void ShowTree(TreePtr pTree);
int CountNode(TreePtr pTree);

void main()
{
#ifdef DebugON
	srand((unsigned)1);
#else
	srand((unsigned)time(NULL));
#endif
	char sTrvslOrder[5 * NoNODE], *pOrder;
	while (1) {
		TreePtr pTree = NULL;
		for (int i = 1; i <= NoNODE; i++) {
			if (MakeTree(pTree, i) == false)
				return;
		}
		// Node numbering
		printf("[After Making]\n");
		ShowTree(pTree);
		putchar('\n');
		Numbering(pTree, 1);
		printf("[After Numbering]\n");
		ShowTree(pTree);
		putchar('\n');
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

int MakeTree(TreePtr& pTree, int nData)
{
	if (pTree == NULL) {
		pTree = (Node1Ptr)malloc(sizeof(Node1));
		if (pTree == NULL)
			return false;
		pTree->nData = nData;
		pTree->lChild = pTree->rChild = NULL;
		return true;
	}
	int nlCtr = CountNode(pTree->lChild), nrCtr = CountNode(pTree->rChild);
	int nChild = nlCtr == nrCtr ? rand() % 2 : nlCtr > nrCtr;
	return nChild ?
		MakeTree(pTree->rChild, nData) : MakeTree(pTree->lChild, nData);
}

void Numbering(TreePtr pTree, int nNo)
{	// 이진트리를 nNo부터 Numbering 한다.
	if (pTree) {
		//pTree의 nData에 nNo를 저장한다
		//pTree의 lChild를 2 * nNo부터 Numbering 한다
		// rChild를 2 * nNo + 1부터 Numbering 한다
	}
}

void PreorderTrvs(TreePtr pTree, CharPtr& sOrder)
{	// preorder로 순회하여 그 결과를 sOrder에 출력한다.
	if (pTree) {
		//sOrder에 "%-3d" 형식으로 pTree->nData를 출력한다
		//pTree의 lChild를 순회하여 sOrder에 추가한다
		//pTree의 rChild를 순회하여 sOrder에 추가한다
	}
}

void InorderTrvs(TreePtr pTree, CharPtr& sOrder)
{	// inorder로 순회하여 그 결과를 sOrder에 출력한다.
	if (pTree) {
		//pTree의 lChild를 순회하여 sOrder에 추가한다
		//sOrder에 "%-3d" 형식으로 pTree->nData를 출력한다
		//pTree의 rChild를 순회하여 sOrder에 추가한다
	}
}

void PostorderTrvs(TreePtr pTree, CharPtr& sOrder)
{	// postorder로 순회하여 그 결과를 sOrder에 출력한다.
	if (pTree) {
		//pTree의 lChild를 순회하여 sOrder에 추가 한다
		//pTree의 rChild를 순회하여 sOrder에 추가 한다
		//sOrder에 "%-3d" 형식으로 pTree->nData를 출력한다
	}
}

// 큐는 마지막 노드를 가리키는 순환 연결 리스트로 표현된다.
void AddQ(QueuePtr& pQueue, TreePtr pTree)
{	// 마지막 노드로 삽입
}

TreePtr DeleteQ(QueuePtr& pQueue)
{	// 첫 노드를 삭제
	return NULL;
}

void LevelOrderTrvs(TreePtr pTree, char *sOrder)
{	// level order로 순회하여 그 결과를 sOrder에 출력한다.
	//pQueue를 초기화 한다
	if (pTree) {
		//pQueue에 pTree를 삽입한다
		while (1) {
			//pTree에 pQueue를 삭제하여 NULL이 아니면
			//	break;
			//sOrder에 "%-3d" 형식으로 pTree->nData를 저장하고 sOrder를 3 증가한다
			//pTree의 lChild가 존재하면
			//	pQueue에 pTree->lChild를 삽입한다
			//pTree의 rChild가 존재하면
			//	pQueue에 pTree->rChild를 삽입한다
		}
	}
}

void FreeTree(TreePtr pTree)
{	// 이진트리의 모든 노드를 되돌려준다.
	if (pTree) {
		FreeTree(pTree->lChild);
		FreeTree(pTree->rChild);
		free(pTree);
	}
}

#define	NodeWIDTH	2
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
				printf("%02d", arNode1[i]->nData);
			else
				PrintGap(NodeWIDTH);
			nGapSum = nGapNow + NodeWIDTH;
			arNode2[2 * i] = arNode1[i] ? arNode1[i]->lChild : NULL;
			arNode2[2 * i + 1] = arNode1[i] ? arNode1[i]->rChild : NULL;
		}
		putchar('\n');
	}
}

int CountNode(TreePtr pTree)
{
	int nCtr = 0;
	if (pTree)
		nCtr = CountNode(pTree->lChild) + CountNode(pTree->rChild) + 1;
	return nCtr;
}
