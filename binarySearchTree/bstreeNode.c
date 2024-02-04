#include "bstreeNode.h"

#include <stdlib.h>
#include <stdio.h>

// 새 노드 생성()
// -> 노드 포인터 반환
node_t* new_node(void) {
	node_t* node = (node_t*)calloc(1, sizeof(node_t));

	if (node == NULL) {
		printf("메모리 할당 거부됨.\n");
		return NULL;
	}

	return node;
}

// bs트리 내의 모든 노드 삭제(bstree 포인터, node_t 포인터)
// ->
void clear_tree(bstree* t, node_t* node) {
	if (t == NULL || node == t->nil)
		return;
	if (node == NULL)
		node = t->root;

	clear_tree(t, node->left);
	clear_tree(t, node->right);
	free(node);
}

void node_insert(bstree* t, node_t** node, node_t* parent, const key_t key) {
	if ((*node) == NULL) {
		printf("트리에 아무 노드도 없음!\n");
		return;
	}

	if ((*node) == t->nil) {
		(*node) = new_node();
		(*node)->key = key;
		(*node)->left = t->nil;
		(*node)->right = t->nil;
		(*node)->parent = parent;
		return;
	}

	if ((*node)->key == key) {
		printf("이진 트리 규칙 깨짐!\n");
		return;
	}
	else if (key < (*node)->key)
		node_insert(t, &((*node)->left), *node, key);
	else
		node_insert(t, &((*node)->right), *node, key);
	return;
}

node_t* node_find(const bstree* t, node_t* node, const key_t key, const int depth) {
	if (node == NULL) {
		printf("트리에 아무 노드도 없음!\n");
		return NULL;
	}

	if (node == t->nil) {
		printf("값을 찾지 못함!\n");
		return NULL;
	}

	if (node->key == key) {
		/*printf("%d: %d번째 순회 찾음.\n", key, depth);*/
		return node;
	}
	else if (key < node->key)
		return node_find(t, node->left, key, depth + 1);
	else
		return node_find(t, node->right, key, depth + 1);
}

node_t* node_min(const bstree* t, node_t* node) {
	if (node == NULL) {
		printf("트리에 아무 노드도 없음!\n");
		return NULL;
	}

	if (node->left == t->nil)
		return node;
	else
		return node_min(t, node->left);
}

node_t* node_max(const bstree* t, node_t* node) {
	if (node == NULL) {
		printf("트리에 아무 노드도 없음!\n");
		return NULL;
	}

	if (node->right == t->nil)
		return node;
	else
		return node_max(t, node->right);
}

int make_inorder_array(const bstree* t, key_t* arr, node_t* node, int i) {
	if (node == NULL) {
		printf("잘못된 노드 연결 감지!\n");
		return 0;
	}

	if (node == t->nil)
		return i;

	i = make_inorder_array(t, arr, node->left, i);
	arr[i++] = node->key;
	i = make_inorder_array(t, arr, node->right, i);
	return i;
}