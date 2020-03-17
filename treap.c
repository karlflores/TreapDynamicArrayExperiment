#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 

#define LEFT 1
#define RIGHT 0
#define MAX_PRIORITY 10000000

struct node {
	struct node *left;
	struct node *right;
	int priority;
	int key;	
};

struct node *rotate_left(struct node *root);
struct node *rotate_right(struct node *root);
struct node *insert(int key, int priority, struct node *root);
struct node *delete(int key, struct node *root);
struct node *split(struct node *tree_less, struct node *tree_greater);
struct node *create_node(int key, int priority);

int main(int argc, char **argv){
	struct node *tree = NULL;
	tree = insert(1,10,tree);
	tree = insert(2,3,tree);
	tree = insert(3,1,tree);

	printf("%d, %d\n", tree->key, tree->priority);
	printf("%d, %d\n", tree->left->key, tree->left->priority);
	return 0;
}

struct node *create_node(int key, int priority){
	struct node *new_node = (struct node*)malloc(sizeof(struct node)); 
	assert(new_node);
	
	new_node->key = key;
	new_node->priority = priority;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

struct node *rotate_left(struct node *root){
	if(!root) return NULL;
	if(!root->left && !root->right) return root;

	struct node *new_root = root->right;
	struct node *old_left = new_root->left;
	new_root->left = root;
	root->right = old_left;
	return new_root;
}

struct node *rotate_right(struct node *root){
	if(!root) return NULL;
	if(!root->left && !root->right) return root;

	struct node *new_root = root->left;
	struct node *old_right = new_root->right;
	new_root->right = root;
	root->left = old_right;
	return new_root;
}

struct node *insert(int key, struct node *root){
	// generate random number from 1 to 10^7
	int priority = rand()*10000000
	return insert_p(key,priority,root);
};

struct node *insert_p(int key, int priority, struct node *root){
	// normal bst insert 
	if(!root) return create_node(key, priority);
	
	// keep track of what side of the current root we have inserted
	// the node into
	int direction;
	// insert to the leaf position
	if(key >= root->key){
		root->right = insert(key, priority, root->right);
		direction = RIGHT;
		printf("insert right\n");
	}else{
		root->left = insert(key, priority, root->left);
		direction = LEFT;
		printf("insert left\n");
	}

	// rotate left if the heap condition is not satisfied 
	if(priority < root->priority){
		if(direction == RIGHT){
			root = rotate_left(root);
			printf("rotate left\n");
		}else{	
			root = rotate_right(root); 
			printf("rotate right\n");
		}
	}

	return root;
}

// TODO - WRITE DELETE FUNCTION
struct node *delete(struct node *root, int key){
	
	if(!root) return NULL;
	
	// first lets find the position of the key;
	struct node **del_node = search_node(root, key);

	// if the element that needs to be deleted does not exist, the tree stays the same
	if(!del_node) return root;

	// else we need to delete the node
		
	// if the del_node is a leaf, we can immediately delete it 
	if(!*del_node->left  && !*del_node->right){
		free(*del_node);
		*del_node = NULL;
	}
	// if the node has one child, we can just swap the node with the child and delete the node;
	else if(!*del_node->left && *del_node->right){
		struct node *temp = *del_node;
		*del_node = *del_node->right;
		free(temp);
	
	// if the node has one child, we can just swap the node with the child and delete the node;
	}else if(!*del_node->right && *del_node->left){
		struct node *temp = *del_node;
		*del_node = *del_node->left;
		free(temp);
	
	// if the node has two children we have to rotate the child to a leaf position 
	}else{
		if(*del_node->left->key > *del_node->right){
			// need to rotate left;
			*del_node = rotate_left(*del_node);
			// then call delete on the left child 
			*del_node->left = delete(*del_node->left,key);
		}else{
			// need to rotate right to push the left priority to the parent;
			*del_node = rotate_right(*del_node);
			// then call delete on the right child which now contains the node that needs to be deleted 
			*del_node->right = delete(*del_node->right,key);
		}	
	}
	return root;
}

// standard treap 
struct node **search_node(struct node *root, int key){
	if(!root) return NULL;
	if(root->key == key) return &root;
	if(root->key > key) return search(key, root->right);
	return search(key, root->left);
}

