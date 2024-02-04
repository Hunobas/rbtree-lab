// bstree.h 전용 유틸 헤더파일

#pragma once
#include "bstree.h"

//// 노드용 재귀함수
node_t* new_node(void);
void clear_tree(bstree* t, node_t* node);
void node_insert(bstree* t, node_t** node, node_t* parent, const key_t key);
node_t* node_find(const bstree* t, node_t* node, const key_t key, const int depth);
node_t* node_min(const bstree* t, node_t* node);
node_t* node_max(const bstree* t, node_t* node);
int make_inorder_array(const bstree* t, key_t* arr, node_t* node, int i);
