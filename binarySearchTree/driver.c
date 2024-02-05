#include "bstree.h"
#include "bstreeNode.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_DEPTH 5

int main() {
	// Test the print_bstree function
	bstree* myTree = new_bstree();

	int ch, key;
	node_t* tar_node;
	key_t* init_arr;
	while (1)
	{
		visualize_tree(myTree, MAX_DEPTH);
		printf("\n\nlength: %d\n", myTree->len);
		printf("\n1.Insert Operation\n");
		printf("2.Erase Operation\n");
		printf("3.Find Operation\n");
		printf("4.Find Min Operation\n");
		printf("5.Find Max Operation\n");
		printf("6.RotateR Operation\n");
		printf("7.RotateL Operation\n");
		printf("8.TreeToArray Operation\n");
		printf("9.Exit\n");
		printf("Enter your choice of operations : ");
		scanf_s("%d", &ch);
		system("cls");
		switch (ch)
		{
		case 1:
			printf("Enter the number of key for INSERT : ");
			scanf_s("%d", &key);
			bstree_insert(myTree, key);
			continue;
		case 2:
			printf("Enter the number of key for ERASE : ");
			scanf_s("%d", &key);
			tar_node = bstree_find(myTree, key);
			bstree_erase(myTree, tar_node);
			continue;
		case 3:
			printf("Enter the number of key for FIND : ");
			scanf_s("%d", &key);
			bstree_find(myTree, key);
			continue;
		case 4:
			printf("MINIMUN key in the tree : ");
			printf("%d", bstree_min(myTree)->key);
			continue;
		case 5:
			printf("MAXIMUM key in the tree : ");
			printf("%d", bstree_max(myTree)->key);
			continue;
		case 6:
			printf("Enter the number of key for ROTATE-R : ");
			scanf_s("%d", &key);
			tar_node = bstree_find(myTree, key);
			bstree_rotateR(myTree, tar_node);
			continue;
		case 7:
			printf("Enter the number of key for ROTATE-L : ");
			scanf_s("%d", &key);
			tar_node = bstree_find(myTree, key);
			bstree_rotateL(myTree, tar_node);
			continue;
		case 8:
			init_arr = (key_t*)calloc(myTree->len, sizeof(key_t));
			if (bstree_to_array(myTree, init_arr, myTree->len) == 0) {
				printf("중위순회 배열: ");
				for (int i = 0; i < myTree->len; ++i)
					printf("%d ", init_arr[i]);
				printf("\n");
			}
			free(init_arr);
			continue;
		case 9:
			exit(0);
			break;
		default:
			printf("Incorrect choice \n");
		}
	}

	delete_bstree(myTree);

	return 0;
}