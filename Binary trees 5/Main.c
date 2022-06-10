#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "BST.h"
#include "TreePrintLibrary.h"

void main() {
	BST bst;
	initBST(&bst);
	insertBST(&bst, 8);
	insertBST(&bst, 10);
	insertBST(&bst, 45);
	insertBST(&bst, 3);
	insertBST(&bst, 2);
	insertBST(&bst, 6);
	insertBST(&bst, 15);
	insertBST(&bst, 50);
	insertBST(&bst, 8);
	insertBST(&bst, 3);
	insertBST(&bst, 0);
	insertBST(&bst, 4);
	print_ascii_tree(bst.root);
	printTreeInorder(&bst);
	printf("\n%d\n", findIndexNFromLast(&bst, 2));
	printf("\n%d\n", sameHeightLeaves(&bst));
	destroyBST(&bst);
}