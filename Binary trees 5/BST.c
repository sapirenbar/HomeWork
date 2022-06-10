#include "BST.h"
#include "TreePrintLibrary.h"
#include <stdio.h>
#include <stdlib.h>
#define ifNull(parameter)do{ if ((parameter) == NULL){ printf("allocation failed"); exit(1);}}while(0);
void initBST(BST* bst);
void insertBST(BST* bst, int value);
void insert(TreeNode* root, TreeNode* newNode);
void printTreeInorder(BST* bst);
void inorder(TreeNode* root);
void destroyBST(BST* bst);
int findIndexNFromLast(BST* bst, int N);
int reversInorder(TreeNode* node, int N);
int sameHeightLeaves(BST* bst);
int checkUtil(TreeNode* root, int level, int* leafLevel);

void initBST(BST* bst)
{
	bst->root = NULL;
}

void insertBST(BST* bst, int value)
{
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	ifNull(newNode);
	newNode->element = value;
	newNode->left = NULL;
	newNode->right = NULL;
	insert(bst, newNode);

}

void insert(TreeNode* root, TreeNode* newNode) {
	if (newNode->element <= root->element)
		if (root->left == NULL)
			root->left = newNode;
		else
			insert(root->left, newNode);
	if (newNode->element > root->element)
		if (root->right == NULL)
			root->right = newNode;
		else
			insert(root->right, newNode);
}

void printTreeInorder(BST* bst) {
	if (bst == NULL) { printf("The tree is empty\n"); return 0; }
	inorder(bst->root);
}

void inorder(TreeNode* root) {
	if (root != NULL) {
		inorder(root->left);
		printf("%d\t", root->element);
		inorder(root->right);
	}
}

void destroyBST(BST* bst) {
	if (bst->root == NULL)
		return;
	destroyBST(bst->root->left);
	destroyBST(bst->root->right);
	free(bst->root);
}

int findIndexNFromLast(BST* bst, int N) {
	if (bst == NULL) { exit(1); };
	return reversInorder(bst->root, N);
}

int reversInorder(TreeNode* node, int N) {
	if (N == 0) {
		if (node == NULL)
			exit(1);

		return node->element;
	}

	if (node != NULL) {
		reversInorder(node->right, --N);
		reversInorder(node->left, --N);
	}
}

int sameHeightLeaves(BST* bst) {
	int* leftLevel = (int*)malloc(sizeof(int));
	if (!leftLevel) { exit(1); }
	if (checkUtil(bst->root, 0, leftLevel) == 1)
		return 1;
	else
		return 0;

}

int checkUtil(TreeNode* root, int level, int* leafLevel)
{
	// Base case
	if (root == NULL)  return 1;

	// If a leaf node is encountered
	if (root->left == NULL && root->right == NULL)
	{
		// When a leaf node is found first time
		if (*leafLevel == 0)
		{
			*leafLevel = level; // Set first found leaf's level
			return 1;
		}

		// If this is not first leaf node, compare its level with
		// first leaf's level
		return (level == *leafLevel);
	}

	// If this node is not leaf, recursively check left and right subtrees
	return (checkUtil(root->left, level + 1, leafLevel) && checkUtil(root->right, level + 1, leafLevel));
}