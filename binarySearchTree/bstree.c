#include "bstree.h"
#include "bstreeNode.h"

#include <stdio.h>
#include <stdlib.h>

// bs트리 생성
// -> bstree 포인터 반환
bstree* new_bstree(void) {
	bstree* p = (bstree*)calloc(1, sizeof(bstree));

	// calloc 실패 시
	if (p == NULL) {
		printf("메모리 할당 거부됨.\n");
		return NULL;
	}

	// 트리의 구성요소 메모리 할당
	p->nil = new_node();
	p->root = p->nil;

	return p;
}

// bs트리 삭제(bstree 포인터)
// ->
void delete_bstree(bstree* t) {
	if (t == NULL)
		return;

	clear_tree(t, t->root);
	free(t->nil);
	free(t);
}

// bs트리에 노드 삽입(bstree 포인터, 삽입할 값)
// -> bstree의 루트 노드 포인터 반환
node_t* bstree_insert(bstree* t, const key_t key) {
	if (t == NULL)
		t = new_bstree();

	node_insert(t, &(t->root), NULL, key);
	t->len++;

	return t->root;
}

// bs트리 내의 값 검색(bstree 포인터, 찾을 값)
// -> 찾은 노드 반환
node_t* bstree_find(const bstree* t, const key_t key) {
	if (t == NULL)
		t = new_bstree();

	return node_find(t, t->root, key, 0);
}

// bs트리 내의 최솟값(bstree 포인터)
// -> 최솟값 노드 반환
node_t* bstree_min(const bstree* t) {
	if (t == NULL)
		t = new_bstree();

	return node_min(t, t->root);
}

// bs트리 내의 최댓값(bstree 포인터)
// -> 최댓값 노드 반환
node_t* bstree_max(const bstree* t) {
	if (t == NULL)
		t = new_bstree();

	return node_max(t, t->root);
}

// bs트리 내의 노드 삭제(bstree 포인터, 삭제할 노드의 포인터)
// -> 성공 여부(0, -1) 반환
int bstree_erase(bstree* t, node_t* p) {
	if (t == NULL)
		t = new_bstree();

	if (p == NULL) {
		printf("삭제할 노드 정의 잘못됨!\n");
		return -1;
	}

	// 타겟 노드의 포인터 지정
	node_t* tar_node = bstree_find(t, p->key);
	if (tar_node == NULL) {
		printf("삭제할 노드 정의 잘못됨!\n");
		return -1;
	}

	// 삭제할 노드의 오른쪽 자식이 하나라도 삽입되어 있다면
	if (tar_node->right != t->nil) {
		// swap_node: 큰 놈중에 작은 애
		node_t* swap_node = node_min(t, tar_node->right);
		
		// 스왑 노드가 오른쪽으로 뻗어나간 애라면
		if (swap_node == swap_node->parent->right) {
			swap_node->right->parent = swap_node->parent;
			swap_node->parent->right = swap_node->right;
		}
		else {
			// 스왑 노드의 오른쪽 자식이 하나라도 삽입되어 있다면
			if (swap_node->right != t->nil) {
				swap_node->right->parent = swap_node->parent;
				swap_node->parent->left = swap_node->right;
			}
			else
				swap_node->parent->left = t->nil;
		}

		tar_node->key = swap_node->key;
		free(swap_node);
	}
	// 삭제할 노드의 왼쪽 자식만 있다면
	else if (tar_node->left != t->nil) {
		tar_node->left->parent = tar_node->parent;
		// 삭제할 노드가 루트라면
		if (tar_node->parent == NULL) {
			tar_node->left->parent = NULL;
			t->root = tar_node->left;
		}
		else
			tar_node->parent->left = tar_node->left;
		free(tar_node);
	}
	// 삭제할 노드가 자식이 없는 노드라면
	else {
		// 삭제할 노드가 루트라면
		if (tar_node->parent == NULL)
			t->root = t->nil;
		else
			tar_node->parent->right = t->nil;
		free(tar_node);
	}

	t->len--;
	return 0;
}

// bs트리 내의 노드 반시계방향 회전(bstree 포인터, 회전할 노드의 포인터)
// -> 성공 여부(0, -1) 반환
int bstree_rotateR(bstree* t, node_t* p) {
	if (t == NULL)
		t = new_bstree();

	if (p == NULL) {
		printf("회전시킬 노드 정의 잘못됨!\n");
		return -1;
	}

	// 타겟 노드의 포인터 지정
	node_t* tar_node = bstree_find(t, p->key);
	if (tar_node == NULL || tar_node->left == t->nil) {
		printf("회전시킬 노드 정의 잘못됨!\n");
		return -1;
	}

	// 부모자식 역전될 노드 설정
	node_t* upsideDown_node = tar_node->left;

	// 꺾인 손자를 자신의 왼쪽 아들로 1번 이산->
	tar_node->left = upsideDown_node->right;
	// 꺾인 손자의 부모를 자신으로 1번 경합<-
	if (upsideDown_node->right != t->nil)
		upsideDown_node->right->parent = tar_node;

	// 자신의 부모를 역전될 노드로 2번 이산->
	upsideDown_node->parent = tar_node->parent;
	// 자신이 루트라면
	if (tar_node->parent == NULL) {
		upsideDown_node->parent = NULL;
		t->root = upsideDown_node;
	}
	// 타겟 노드가 오른쪽으로 뻗어나간 애라면 2번 경합<-
	else if (tar_node->parent->right == tar_node)
		tar_node->parent->right = upsideDown_node;
	// 타겟 노드가 왼쪽으로 뻗어나간 애라면 2번 경합<-
	else
		tar_node->parent->left = upsideDown_node;

	// 자신을 역전될 노드의 오른쪽 자식으로 3번 이산->
	upsideDown_node->right = tar_node;
	// 역전될 노드를 자신의 부모로 3번 경합<-
	tar_node->parent = upsideDown_node;

	return 0;
}

// bs트리 내의 노드 반시계방향 회전(bstree 포인터, 회전할 노드의 포인터)
// -> 성공 여부(0, -1) 반환
int bstree_rotateL(bstree* t, node_t* p) {
	if (t == NULL)
		t = new_bstree();

	if (p == NULL) {
		printf("회전시킬 노드 정의 잘못됨!\n");
		return -1;
	}

	// 타겟 노드의 포인터 지정
	node_t* tar_node = bstree_find(t, p->key);
	if (tar_node == NULL || tar_node->right == t->nil) {
		printf("회전시킬 노드 정의 잘못됨!\n");
		return -1;
	}
	
	// 부모자식 역전될 노드 설정
	node_t* upsideDown_node = tar_node->right;

	// 꺾인 손자를 오른쪽 아들로 1번 이산->
	tar_node->right = upsideDown_node->left;
	// 꺾인 손자의 부모를 자신으로 1번 경합<-
	if (upsideDown_node->left != t->nil)
		upsideDown_node->left->parent = tar_node;

	// 자신의 부모를 역전될 노드로 2번 이산->
	upsideDown_node->parent = tar_node->parent;
	// 자신이 루트라면
	if (tar_node->parent == NULL) {
		upsideDown_node->parent = NULL;
		t->root = upsideDown_node;
	}
	// 타겟 노드가 오른쪽으로 뻗어나간 애라면 2번 경합<-
	else if (tar_node->parent->right == tar_node)
		tar_node->parent->right = upsideDown_node;
	// 타겟 노드가 왼쪽으로 뻗어나간 애라면 2번 경합<-
	else
		tar_node->parent->left = upsideDown_node;

	// 역전될 노드의 왼쪽 자식을 자신으로 3번 이산->
	upsideDown_node->left = tar_node;
	// 자신의 부모를 역전될 노드로 3번 경합<-
	tar_node->parent = upsideDown_node;

	return 0;
}

// bs트리를 중위순회 배열로(bstree 포인터, 배열 포인터, 배열 사이즈)
// -> 성공 여부(0, -1) 반환
int bstree_to_array(const bstree* t, key_t* arr, const size_t n) {
	if (t == NULL)
		t = new_bstree();
	if (arr == NULL) {
		printf("배열 정의 잘못됨!\n");
		return -1;
	}

	make_inorder_array(t, arr, t->root, 0);
	return 0;
}