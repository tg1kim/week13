#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#pragma warning(disable: 4326 4996 6001 6031)

#define TESTING			// define for testing
#ifdef TESTING
#define NoNODE	11
#else
#define NoNODE	26
#endif

typedef char* CharPtr;
typedef struct node {
	char	nData;
	struct node *lChild;
	struct node *rChild;
}	Node, *NodePtr, *TreePtr;

int MakeTree(TreePtr& pTree, int nData);
void PreorderTrvs(TreePtr pTree, CharPtr& sOrder);
void InorderTrvs(TreePtr pTree, CharPtr& sOrder);
void PostorderTrvs(TreePtr pTree, CharPtr& sOrder);
TreePtr Tree4InPreorder(char* sInorder, char* sPreorder, int nCtr);
TreePtr Tree4InPostorder(char* sInorder, char* sPostorder, int nCtr);
bool EqualTree(TreePtr pTree1, TreePtr pTree2);
void FreeTree(TreePtr pTree);
void PrintRootLeftRght(TreePtr pTree);

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
		printf("[D, L, R]\n---------\n");
		PrintRootLeftRght(pTree);
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
	int nChild;
	if (pTree->lChild == NULL && pTree->rChild)
		nChild = 0;
	else if (pTree->lChild && pTree->rChild == NULL)
		nChild = 1;
	else
		nChild = rand() % 2;
	return MakeTree((nChild) ? pTree->rChild : pTree->lChild, nData);
}

void PreorderTrvs(TreePtr pTree, CharPtr& sOrder)
{	// 전위 순회를 하여 sOrder에 저장한다
}

void InorderTrvs(TreePtr pTree, CharPtr& sOrder)
{	// 중위 순회를 하여 sOrder에 저장한다
}

void PostorderTrvs(TreePtr pTree, CharPtr& sOrder)
{	// 후위 순회를 하여 sOrder에 저장한다
}

TreePtr Tree4InPreorder(char *sInorder, char *sPreorder, int nCtr)
{
	return NULL;
}

TreePtr Tree4InPostorder(char *sInorder, char *sPostorder, int nCtr)
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

void PrintRootLeftRght(TreePtr pTree)
{	// 트리의 모든 노드에 대하여 [D, L, R] 형식으로 출력한다(NULL은 ^)
	if (pTree) {
		printf("[%c, %c, %c]\n",
			pTree->nData,
			(pTree->lChild) ? pTree->lChild->nData : '^',
			(pTree->rChild) ? pTree->rChild->nData : '^');
		PrintRootLeftRght(pTree->lChild);
		PrintRootLeftRght(pTree->rChild);
	}
}