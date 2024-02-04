#ifndef binarySEarchTree
#define binarySEarchTree

#include <stddef.h>

typedef int key_t;

typedef struct node_t {
	key_t key;
	struct node_t* parent, * left, * right;
} node_t;

typedef struct {
	node_t* root;
	node_t* nil;  // for sentinel
	size_t len;
} bstree;

bstree* new_bstree(void);
void delete_bstree(bstree*);

node_t* bstree_insert(bstree*, const key_t);
node_t* bstree_find(const bstree*, const key_t);
node_t* bstree_min(const bstree*);
node_t* bstree_max(const bstree*);
int bstree_erase(bstree*, node_t*);
int bstree_rotateR(bstree*, node_t*);
int bstree_rotateL(bstree*, node_t*);

int bstree_to_array(const bstree*, key_t* arr, const size_t);

//// 프린트 함수
void print2D(bstree* t);
void print2DUtil(bstree* t, node_t* node, int space);

#endif  // _BSTREE_H_