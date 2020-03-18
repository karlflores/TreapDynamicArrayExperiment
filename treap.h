#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 

#include "data.h"

#define LEFT 1
#define RIGHT 0
#define MAX_PRIORITY 100000000


struct node {
	struct node *left;
	struct node *right;
	struct data_element *data;	
	int priority;

};

struct node *rotate_left(struct node *root);
struct node *rotate_right(struct node *root);
struct node *insert(struct node *root, struct data_element *data);
struct node *delete(struct node *root, int key);
struct node *create_node(struct data_element *data);
struct node *search(struct node *root, int key);
