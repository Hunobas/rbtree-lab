#pragma once
#include "rbtree.h"

//// 노드용 재귀함수
node_t* new_node(void);
void clear_tree(rbtree*, node_t*);
node_t* node_insert(rbtree*, node_t**, node_t*, const key_t);
node_t* node_find(const rbtree*, node_t*, const key_t, const int);
node_t* node_min(const rbtree*, node_t*);
node_t* node_max(const rbtree*, node_t*);
int rotateR(rbtree*, node_t*);
int rotateL(rbtree*, node_t*);
void rbtree_transplant(rbtree*, node_t*, node_t*);
int make_inorder_array(const rbtree*, key_t*, node_t*, int);

//// 검사 함수
void rootBlack(rbtree*);
void rb_insert_fixup(rbtree*, node_t*);
void rb_delete_fixup(rbtree*, node_t*);

//// 프린트 함수
void print2D(rbtree*);
void print2DUtil(rbtree*, node_t*, int);

int pow_2(int);
void record_keys(rbtree*, node_t*, node_t**, int*, int, int);
void visualize_tree(rbtree*, int);