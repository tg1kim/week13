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