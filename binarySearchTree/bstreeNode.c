#include "bstreeNode.h"

#include <stdlib.h>
#include <stdio.h>

#define SPACE 3

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


void print2DUtil(bstree* t, node_t* node, int space)
{
	if (node == NULL)
		return;

	space += SPACE;

	print2DUtil(t, node->right, space);

	printf("\n");
	for (int i = SPACE; i < space; i++)
		printf(" ");
	if (node == t->nil)
		printf(".");
	else
		printf("%d\n", node->key);

	print2DUtil(t, node->left, space);
}

void print2D(bstree* t)
{
	print2DUtil(t, t->root, 0);
}

int pow_2(int x) {
	// 2**x 계산 함수
	return 1 << x;
}

void record_keys(bstree* t, node_t* p, node_t** node_arr, int* node_idx_list, int cur_depth, int render_depth) {
	// visualize_tree에서 사용하기위한 배열을 재귀적으로 기록
	if (cur_depth > render_depth) {
		return;
	}

	node_arr[cur_depth * pow_2(render_depth) + node_idx_list[cur_depth]] = p;
	node_idx_list[cur_depth] += 1;
	if (p == t->nil) {
		record_keys(t, t->nil, node_arr, node_idx_list, cur_depth + 1, render_depth);
		record_keys(t, t->nil, node_arr, node_idx_list, cur_depth + 1, render_depth);
	}
	else {
		record_keys(t, p->left, node_arr, node_idx_list, cur_depth + 1, render_depth);
		record_keys(t, p->right, node_arr, node_idx_list, cur_depth + 1, render_depth);
	}
}

void visualize_tree(bstree* t, int render_depth) {
	// 트리 시각화 함수
	// depth는 루트를 0으로 계산
	// key_arr[i][j]: 깊이가 i인 (j+1)번째 원소의 키 **2차원 배열 접근이 불가능해 1차원 배열로 구현
	node_t** node_arr = calloc((render_depth + 1) * pow_2(render_depth), sizeof(node_t));

	// key_idx_list[i]: key_arr[i]의 현재 인덱스
	int* node_idx_list = (int*)calloc(render_depth + 1, sizeof(int));

	char* filler = "  ";

	// 키를 배열에 기록
	record_keys(t, t->root, node_arr, node_idx_list, 0, render_depth);

	// 기록된 키를 출력
	for (int i = 0; i < render_depth + 1; i++) {
		for (int j = 0; j < pow_2(i); j++) {
			for (int k = 0; k < pow_2(render_depth - i); k++) { // front buffer
				printf("%s", filler);
			}
			if (node_arr[i * pow_2(render_depth) + j] == t->nil) {
				printf("\x1b[0m" "%2s", ".");
			}
			else {
				// 검정 노드는 흰색으로 출력
				printf("%2d", node_arr[i * pow_2(render_depth) + j]->key);
			}

			for (int k = 0; k < pow_2(render_depth - i) - 1; k++) { // back buffer
				printf("%s", filler);
			}
		}
		printf("\n");
	}
	printf("\n");

	free(node_arr);
	free(node_idx_list);
}