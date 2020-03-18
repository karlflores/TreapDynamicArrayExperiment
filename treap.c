#include "treap.h"

struct node *create_node(struct data_element *data){
	struct node *new_node = (struct node*)malloc(sizeof(struct node)); 
	assert(new_node);
	new_node-> data = data;	
	new_node->left = NULL;
	new_node->right = NULL;
	// assign a priority to the node when created
	new_node->priority = (int)(rand()*MAX_PRIORITY);
	
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

struct node *insert(struct node *root, struct data_element *data){
	// normal bst insert 
	if(!data) return NULL;
	if(!root) return create_node(data);
	
	// keep track of what side of the current root we have inserted
	// the node into
	// insert to the leaf position
	if(data->key >= root->data->key){
		root->right = insert(root->right, data);
		printf("insert right\n");
		if(root->right->priority > root->priority || 
					(root->right->priority == root->priority && 
					root->right->data->id < root->data->id)){
			// rotate left
			root = rotate_left(root);
			printf("rotate left\n");
		}
	}else{
		root->left = insert(root->left, data);
		printf("insert left\n");
		if(root->left->priority > root->priority || 
					(root->left->priority == root->priority && 
					root->left->data->id < root->data->id)){
			// rotate left
			root = rotate_left(root);
			printf("rotate right\n");
		}
	}

	return root;
}

// TODO - WRITE DELETE FUNCTION
struct node *delete(struct node *root, int key){
	
	if(!root) return NULL;
	
	if(root->data->key > key) root->right = delete(root->right,key);
	else if (root->data->key < key) root->left = delete(root->left,key);
	else{ 	
		// at this stage, we know root is the node we want to delete
		
		// if the del_node is a leaf, we can immediately delete it 
		if(!root->left  && !root->right){
			free(root);
			return NULL;
		}
		// if the node has one child, we can just swap the node with the child and delete the node;
		else if(!root->left && root->right){
			struct node *temp = root;
			root = root->right;
			free(temp);	
		// if the node has one child, we can just swap the node with the child and delete the node;
		}else if(!root->right && root->left){
			struct node *temp = root;
			root = root->left;
			free(temp);
		// if the node has two children we have to rotate the child to a leaf position 
		}else{

			// rotate in the opposite direction to side which has the lowest priority
			if(root->left->priority < root->right->priority){
				// need to rotate left;
				root = rotate_right(root);
				// then call delete on the right child 
				root->right = delete(root->right,key);
			}else{
				// need to rotate right to push the left priority to the parent;
				root = rotate_left(root);
				// then call delete on the right child which now contains the node that needs to be deleted 
				root->right = delete(root->right,key);
			}	
		}
	}
	return root;
}

// standard treap 
struct node *search(struct node *root, int key){
	if(!root) return NULL;
	if(root->data->key == key) return root;
	if(root->data->key > key) return search(root->right,key);
	return search(root->left,key);
}

