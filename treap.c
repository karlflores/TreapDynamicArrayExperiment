#include "treap.h"

// create the treap 
struct treap *create_treap(){
	struct treap *treap = (struct treap *)malloc(sizeof(struct treap));
	assert(treap);
	
	// set the root to be null first;
	treap->root = NULL;

	treap->insert = &treap_insert;
	treap->delete = &treap_delete;
	treap->search = &treap_search;
	return treap;	
}

// delete a treap 
void delete_treap(struct treap *treap){
	if(!treap) return;
	delete_treap_nodes(treap->root);
	free(treap);
}

/* TREAP INTERFACE FUNCTION WRAPPERS */
// insert into the treap 
void treap_insert(struct treap *treap, struct data_element *data){
	// don't allow the treap to store NULL values 
	if(!data) return;

	// treap has to exist inorder to insert something into it;
	if(!treap) return;

	treap->root = insert_node(treap->root,data);
}

void treap_delete(struct treap *treap, int key){
	if(!treap) return;

	treap->root = delete_node(treap->root,key);
}

int treap_search(struct treap *treap, int key){
	if(!treap) FALSE;

	return search_node(treap->root,key);
}


/* Search functions that work on the node */
struct node *insert_node(struct node *root, struct data_element *data){
	// normal bst insert 
	if(!data) return NULL;
	if(!root) return create_node(data);
	
	// keep track of what side of the current root we have inserted
	// the node into
	// insert to the leaf position
	if(data->key >= root->data->key){

		root->right = insert_node(root->right, data);

		// once we have inserted the element, we can fix the heap 
		// as the node is on the right, check if the heap property is violated 
		// and rotate left if needed
		if(root->right->priority < root->priority || 
					(root->right->priority == root->priority && 
					root->right->data->id < root->data->id)){
			root = rotate_left(root);
		}
	}else{
		root->left = insert_node(root->left, data);
		if(root->left->priority < root->priority || 
					(root->left->priority == root->priority && 
					root->left->data->id < root->data->id)){

			// rotate right to fix heap property 
			root = rotate_right(root);
		}
	}

	return root;
}

// Delete a node from the heap 
struct node *delete_node(struct node *root, int key){
	
	// if the root does not exist we dont need to do anything 	
	if(!root) return NULL;
	
	// recurse down the tree until we find the node we want to delete	
	if(key > root->data->key) root->right = delete_node(root->right,key);
	else if (key < root->data->key) root->left = delete_node(root->left,key);
	else{ 	
		// at this stage, we know root is the node we want to delete
		
		// if the del_node is a leaf, we can immediately delete it 
		if(!root->left  && !root->right){
			free(root);
			return NULL;
		}
		// if the node has one child, we can just swap the node with the child and delete the node;
		else if(!root->left && root->right){
			struct node *temp = root->right;
			free(root);	
			root = temp;

		// if the node has one child, we can just swap the node with the child and delete the node;
		}else if(!root->right && root->left){
			struct node *temp = root->left;
			free(root);
			root = temp;
		// if the node has two children we have to rotate the child to a leaf position 
		}else{
			// rotate in the opposite direction to side which has the lowest priority
			if(root->left->priority < root->right->priority){
				// need to rotate left;
				root = rotate_right(root);
				// our required node now is on the right of the root, 
				// call delete on the right child 
				root->right = delete_node(root->right,key);
			}else{
				// need to rotate right to push the left priority to the parent;
				root = rotate_left(root);
				// then call delete on the right child which now 
				// contains the node that needs to be deleted 
				root->left = delete_node(root->left,key);
			}	
		}
	}
	return root;
}

// standard bst search
int search_node(struct node *root, int key){
	if(!root) return FALSE;
	if(root->data->key == key) return TRUE;
	if(key >= root->data->key) return search_node(root->right,key);
	return search_node(root->left,key);
}

// helper function to create a node in the treap 
struct node *create_node(struct data_element *data){
	struct node *new_node = (struct node*)malloc(sizeof(struct node)); 
	assert(new_node);
	new_node-> data = data;	
	new_node->left = NULL;
	new_node->right = NULL;
	// assign a priority to the node when created
	new_node->priority = (int)(rand()%MAX_PRIORITY+1);
	
	return new_node;
}

/* ROTATION FUNCTIONS */
struct node *rotate_left(struct node *root){
	if(!root) return NULL;
	
	// can't rotate a leaf node 
	if(!root->left && !root->right) return root;

	struct node *new_root = root->right;
	struct node *old_left = new_root->left;
	new_root->left = root;
	root->right = old_left;
	return new_root;
}

struct node *rotate_right(struct node *root){
	if(!root) return NULL;

	// can't rotate a leaf node 
	if(!root->left && !root->right) return root;

	struct node *new_root = root->left;
	struct node *old_right = new_root->right;
	new_root->right = root;
	root->left = old_right;
	return new_root;
}


/* UTIL FUNCTIONS */
void inorder(struct node *root){
	if(!root) return;
	inorder(root->left);
	printf("| (%d,%d) ",root->data->id,root->data->key);
	inorder(root->right);
}

void delete_treap_nodes(struct node *root){
	if(!root) return;
	delete_treap_nodes(root->left);
	delete_treap_nodes(root->right);
	free(root);

}
