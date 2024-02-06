#pragma once
#include "bstree.h"

//typedef struct queue {
//	node_t** n_arr;
//	size_t len;
//} queue;

//// 노드용 재귀함수
node_t* new_node(void);
void clear_tree(bstree* t, node_t* node);
void node_insert(bstree* t, node_t** node, node_t* parent, const key_t key);
node_t* node_find(const bstree* t, node_t* node, const key_t key, const int depth);
node_t* node_min(const bstree* t, node_t* node);
node_t* node_max(const bstree* t, node_t* node);
int make_inorder_array(const bstree* t, key_t* arr, node_t* node, int i);

//// 프린트 함수
// 내꺼
void print2D(bstree* t);
void print2DUtil(bstree* t, node_t* node, int space);
// 갓민수님꺼
int pow_2(int x);
void record_keys(bstree* t, node_t* p, node_t** node_arr, int* node_idx_list, int cur_depth, int render_depth);
void visualize_tree(bstree* t, int render_depth);
//void print_space(const int n);
//void print_bstree(const bstree* t);

//// 큐
//queue* new_queue(void);
//void delete_queue(queue* que);
//queue* append(queue* que, const node_t** node);
//const node_t* pop(queue* que);