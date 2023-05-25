#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENTS	100
#pragma warning (disable: 4996)

typedef struct {
	int nData;
	int nOtherData;
}	Element;

void main()
{
	void InsertHeap(Element heap[], Element& anItem, int& n);
	Element DeleteHeap(Element heap[], int& nCtr);

	Element heap[MAX_ELEMENTS + 1];
	int nCtr = 0;
	Element item;
	srand((unsigned)time(NULL));
	while (1) {
		int nMax;
		printf("��� ���� ? ");
		scanf("%d", &nMax);
		if (nMax <= 0 || nMax > MAX_ELEMENTS)
			break;
		printf("  [Heap ���� ����]\n");
		for (int i = 1; i <= nMax; i++) {
			item.nData = rand() % 1000;
			printf("    [%02d] %d\n", i, item.nData);
			InsertHeap(heap, item, nCtr);
		}
		printf("\n  [Heap ����]\n");
		for (int i = 1; i <= nMax; i++) {
			item = DeleteHeap(heap, nCtr);
			printf("    [%02d] %d\n", i, item.nData);
		}
		putchar('\n');
	}
}

void InsertHeap(Element heap[], Element& anItem, int& nCtr)
{
	nNdx�� nCtr�� 1 ������ �� �����Ѵ�;
	while (nNdx�� 1���� ũ��  anItem�� ����Ŀ�� [nNdx / 2]�� �����ͺ��� ũ��) {
		�θ��� �����͸� �ڽ����� ������
		nNdx�� �� ���� ���� �ø���
	}
	[nNdx]�� anItem�� �����Ѵ�
}

Element DeleteHeap(Element heap[], int& nCtr)
{
	anItem�� ��Ʈ �����͸� �����Ѵ�
	lastItem�� ������ �����͸� �����ϰ� nCtr�� 1 �����Ѵ�
	parent�� 1��, child�� 2�� �����Ѵ�
	while (child�� nCtr���� �۰ų� ����) {
		if (child�� nCtr���� �۰� [child]�� �����Ͱ� [child + 1]�� �����ͺ��� �۴�)
			child�� 1 �����Ѵ�
		if (lastItem�� �����Ͱ� [child]�� �����ͺ��� Ŀ�ų� ����)
			break;
		[parent]�� �����Ϳ� [child]�� �����͸� �����Ѵ�
		parent�� child�� �����Ѵ�
		child�� 2�� ���Ѵ�
	}
	[parent]�� lastItem�� �����Ѵ�
	anItem�� ��ȯ�Ѵ�
}
