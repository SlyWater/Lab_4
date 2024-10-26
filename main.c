﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};
int deep = 0, min = -1, max = 0;

struct Node* root = NULL;

struct Node* CreateTree(struct Node* root, struct Node* r, int data) {
	if (r == NULL)
	{
		r = (struct Node*)malloc(sizeof(struct Node));
		if (r == NULL)
		{
			printf("Ошибка выделения памяти");
			exit(0);
		}

		r->left = NULL;
		r->right = NULL;
		r->data = data;
		if (root == NULL) return r;

		if (data > root->data)	root->left = r;
		else root->right = r;
		return r;
	}

	if (data > r->data)
		CreateTree(r, r->left, data);
	else
		CreateTree(r, r->right, data);
	return root;
}

void print_tree(struct Node* r, int l)
{

	if (r == NULL)
	{
		return;
	}

	print_tree(r->right, l + 1);
	for (int i = 0; i < l; i++)
	{
		printf(" ");
	}

	printf("%d\n", r->data);
	print_tree(r->left, l + 1);
}

struct Node* find(struct Node* root, int data) {
	if (root->data == data) return root;
	if (root->data > data && root->right != NULL) find(root->right, data);
	else if (root->left != NULL) find(root->left, data);
	else return NULL;
}

int count(struct Node* root, int data, int cnt) {
	if (root->data == data) {
		cnt++;
		if (min == -1 && deep >= min) min = deep;
		else if (deep > max) max = deep;
	}
	if (root->data >= data && root->right != NULL) {
		deep++;
		cnt = count(root->right, data, cnt);
	}
	else if (root->left != NULL)  {
		deep++;
		cnt = count(root->left, data, cnt);
	}
	else {
		deep--;
		return cnt; 

	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int D, start = 1;

	printf("-1 - окончание построения дерева\n");
	while (start)
	{
		printf("Введите число: ");
		scanf_s("%d", &D);
		if (D == -1)
		{
			printf("Построение дерева окончено\n\n");
			start = 0;
		}
		else {
			root = CreateTree(root, root, D);
		}

	}

	print_tree(root, 0);

	int s;
	printf("Введите число для поиска: ");
	scanf("%d", &s);


	struct Node* r = find(root, s);
	if (r) {
		printf("найден %d\n", r->data);
		int cnt;
		cnt = count(root, s, 0);
		printf("найдено %d вхождения\n", cnt);
		printf("\nпервое вхождение на уровне %d\nвторое вхождение на уровне %d", min, max);
	}
	else printf("элемент не найден\n");

	scanf_s("%d", &D);
	return 0;
}
