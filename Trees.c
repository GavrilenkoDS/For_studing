#include <stdio.h>
#include <stdlib.h>

//BIN TREE
struct node {
	int key;
	int data;
	struct node *left;
	struct node *right;
	struct node *parent;
};

struct node * search(struct node *tree, int key) {
	if (key == tree->key)
		return tree;
	if (key > tree->key) {
		if (tree->left != NULL)
			search(tree->left, key);
		else
			return 0;
	}
	if (key < tree->key) {
		if (tree->right != NULL)
			search(tree->right, key);
		else
			return 0;
	}
}

void insert(struct node *tree, int key, int data) {
	if (key > tree->key) {
		if (tree->left != NULL)
			insert(tree->left, key, data);
		else {
			struct node * node = malloc(sizeof * node);
			node->data = data;
			node->key = key;
			node->left = NULL;
			node->right = NULL;
			node->parent = tree;
			tree->left = node;
		}
	}
	if (key < tree->key) {
		if (tree->right != NULL)
			insert(tree->right, key, data);
		else{
			struct node * node = malloc(sizeof * node);
			node->data = data;
			node->key = key;
			node->left = NULL;
			node->right = NULL;
			node->parent = tree;
			tree->right = node;
		}
	}
}

void add(struct node *tree, struct node *new_node) {
	if (new_node->key > tree->key) {
		if (tree->left != NULL)
			insert(tree->left, new_node->key, new_node->data);
		else {
			tree->left = new_node;
		}
	}
	if (new_node->key < tree->key) {
		if (tree->right != NULL)
			insert(tree->right, new_node->key, new_node->data);
		else {
			tree->right = new_node;
		}
	}


}

void del(struct node *tree, int key) {
	struct node *node = search(tree, key);
	struct node *nodeL = node->left;
	struct node *nodeR = node->right;
	free(node);
	add(tree, nodeL);
	add(tree, nodeR);
}

//
//AVL
struct avl_node {
	struct avl_node * link[2];
	int data;
	short bal;
};

struct avl_tree {
	struct avl_node *root; 
	int count; 
};

int avl_insert(struct avl_tree * tree, int data) {
	struct avl_node ** v, *w, *x, *y, *z;

	
	v = &tree->root;
	x = z = tree->root;
	if (x == NULL) {
		tree->root = new_node(tree, data);
		return tree->root != NULL;
	}

	for (;;) {
		int dir;

		if (data == z->data) return 2;

		dir = (data > z->data);
		y = z->link[dir];
		if (y == NULL) {
			y = z->link[dir] = new_node(tree, data);
			if (y == NULL) return 0;
			break;
		}
		if (y->bal != 0) {
			v = &z->link[dir];
			x = y;
		}
		z = y;
	}


	w = z = x->link[data > x->data];
	while (z != y)
		if (data < z->data) {
			z->bal = -1;
			z = z->link[0];
		}
		else {
			z->bal = +1;
			z = z->link[1];
		}


	if (data < x->data) {
		if (x->bal != -1)
			x->bal--;
		else if (w->bal == -1) {
			*v = w;
			x->link[0] = w->link[1];
			w->link[1] = x;
			x->bal = w->bal = 0;
		}
		else {
			*v = z = w->link[1];
			w->link[1] = z->link[0];
			z->link[0] = w;
			x->link[0] = z->link[1];
			z->link[1] = x;
			if (z->bal == -1) {
				x->bal = 1;
				w->bal = 0;
			}
			else if (z->bal == 0)
				x->bal = w->bal = 0;
			else {
				x->bal = 0;
				w->bal = -1;
			}
			z->bal = 0;
		}
	}

	else {
		if (x->bal != +1)
			x->bal++;
		else if (w->bal == +1) {
			*v = w;
			x->link[1] = w->link[0];
			w->link[0] = x;
			x->bal = w->bal = 0;
		}
		else {
			*v = z = w->link[0];
			w->link[0] = z->link[1];
			z->link[1] = w;
			x->link[1] = z->link[0];
			z->link[0] = x;
			if (z->bal == +1) {
				x->bal = -1;
				w->bal = 0;
			}
			else if (z->bal == 0)
				x->bal = w->bal = 0;
			else {
				x->bal = 0;
				w->bal = 1;
			}
			z->bal = 0;
		}
	}
	return 1;
}

struct avl_node * new_node_avl(struct avl_tree * tree, int item) {
	struct avl_node * node = malloc(sizeof * node);
	node->data = item;
	node->link[0] = node->link[1] = NULL;
	node->bal = 0;
	tree->count++;
	return node;
};

int avl_delete(struct avl_tree * tree, int item) {
	struct avl_node * ap[32];
	int ad[32];

	int k = 1;

	struct avl_node ** y, *z;

	ad[0] = 0;
	ap[0] = (struct avl_node *) &tree->root;

	z = tree->root;

	for (;;) {
		int dir;
		if (z == NULL)
			return 0;
		if (item == z->data)
			break;

		dir = item > z->data;
		ap[k] = z;
		ad[k++] = dir;
		z = z->link[dir];
	}

	
	tree->count--;
	y = &ap[k - 1]->link[ad[k - 1]];
	if (z->link[1] == NULL)
		*y = z->link[0];
	else {
		struct avl_node *x = z->link[1];
		if (x->link[0] == NULL) {
			x->link[0] = z->link[0];
			*y = x;
			x->bal = z->bal;
			ad[k] = 1;
			ap[k++] = x;
		}
		else {
			struct avl_node *w = x->link[0];
			int j = k++;
			ad[k] = 0;
			ap[k++] = x;
			while (w->link[0] != NULL) {
				x = w;
				w = x->link[0];
				ad[k] = 0;
				ap[k++] = x;
			}

			ad[j] = 1;
			ap[j] = w;
			w->link[0] = z->link[0];
			x->link[0] = w->link[1];
			w->link[1] = z->link[1];
			w->bal = z->bal;
			*y = w;
		}
	}
	free(z);

	
	while (--k) {
		struct avl_node *w, *x;
		w = ap[k];
		if (ad[k] == 0) {
			if (w->bal == -1) {
				w->bal = 0;
				continue;
			}
			else if (w->bal == 0) {
				w->bal = 1;
				break;
			}

			x = w->link[1];
			if (x->bal > -1) {
				w->link[1] = x->link[0];
				x->link[0] = w;
				ap[k - 1]->link[ad[k - 1]] = x;
				if (x->bal == 0) {
					x->bal = -1;
					break;
				}
				else
					w->bal = x->bal = 0;
			}
			else {
				z = x->link[0];
				x->link[0] = z->link[1];
				z->link[1] = x;
				w->link[1] = z->link[0];
				z->link[0] = w;
				if (z->bal == 1) {
					w->bal = -1;
					x->bal = 0;
				}
				else if (z->bal == 0)
					w->bal = x->bal = 0;
				else {
					w->bal = 0;
					x->bal = 1;
				}
				z->bal = 0;
				ap[k - 1]->link[ad[k - 1]] = z;
			}
		}
		else {
			if (w->bal == 1) {
				w->bal = 0;
				continue;
			}
			else if (w->bal == 0) {
				w->bal = -1;
				break;
			}

			x = w->link[0];
			if (x->bal < 1) {
				w->link[0] = x->link[1];
				x->link[1] = w;
				ap[k - 1]->link[ad[k - 1]] = x;
				if (x->bal == 0) {
					x->bal = 1;
					break;
				}
				else
					w->bal = x->bal = 0;
			}
			else if (x->bal == 1) {
				z = x->link[1];
				x->link[1] = z->link[0];
				z->link[0] = x;
				w->link[0] = z->link[1];
				z->link[1] = w;
				if (z->bal == -1) {
					w->bal = 1;
					x->bal = 0;
				}
				else if (z->bal == 0)
					w->bal = x->bal = 0;
				else {
					w->bal = 0;
					x->bal = -1;
				}
				z->bal = 0;
				ap[k - 1]->link[ad[k - 1]] = z;
			}
		}
	}
	return 1;
}

//
//RB TREE

	struct rb_node {
		int red;
		int data;
		struct rb_node *link[2];
	};

	struct rb_tree {
		struct rb_node *root; 
		int count; 
	};

	int is_red(struct rb_node *node) {
		return node != NULL && node->red == 1;
	}

	
	struct rb_node *rb_single(struct rb_node *root, int dir) {
		struct rb_node *save = root->link[!dir];

		root->link[!dir] = save->link[dir];
		save->link[dir] = root;

		root->red = 1;
		save->red = 0;

		return save;
	}

	
	struct rb_node *rb_double(struct rb_node *root, int dir) {
		root->link[!dir] = rb_single(root->link[!dir], !dir);
		return rb_single(root, dir);
	}

	struct rb_node *make_node(int data) {
		struct rb_node *rn = malloc(sizeof *rn);

		if (rn != NULL) {
			rn->data = data;
			rn->red = 1;
			rn->link[0] = NULL;
			rn->link[1] = NULL;
		}
		return rn;
	}

	int rb_insert(struct rb_tree *tree, int data) {
		
		if (tree->root == NULL) {
			tree->root = make_node(data);
			if (tree->root == NULL)
				return 0;
		}
		else {
			struct rb_node head = { 0 }; 
			struct rb_node *g, *t;     
			struct rb_node *p, *q;   
			int dir = 0, last;

		
			t = &head;
			g = p = NULL;
			q = t->link[1] = tree->root;

		
			for (; ; ) {
				if (q == NULL) {
					
					p->link[dir] = q = make_node(data);
					tree->count++;
					if (q == NULL)
						return 0;
				}
				else if (is_red(q->link[0]) && is_red(q->link[1])) {
				
					q->red = 1;
					q->link[0]->red = 0;
					q->link[1]->red = 0;
				}
				
				if (is_red(q) && is_red(p)) {
					int dir2 = t->link[1] == g;

					if (q == p->link[last])
						t->link[dir2] = rb_single(g, !last);
					else
						t->link[dir2] = rb_double(g, !last);
				}

				
				if (q->data == data) {
					break;
				}

				last = dir;
				dir = q->data < data;

				if (g != NULL)
					t = g;
				g = p, p = q;
				q = q->link[dir];
			}

			
			tree->root = head.link[1];
		}
		
		tree->root->red = 0;

		return 1;
	}

	int br_remove(struct rb_tree *tree, int data) {
		if (tree->root != NULL) {
			struct rb_node head = { 0 }; 
			struct rb_node *q, *p, *g; 
			struct rb_node *f = NULL;  
			int dir = 1;

			
			q = &head;
			g = p = NULL;
			q->link[1] = tree->root;

			
			while (q->link[dir] != NULL) {
				int last = dir;

				
				g = p, p = q;
				q = q->link[dir];
				dir = q->data < data;

				
				if (q->data == data)
					f = q;

				if (!is_red(q) && !is_red(q->link[dir])) {
					if (is_red(q->link[!dir]))
						p = p->link[last] = rb_single(q, dir);
					else if (!is_red(q->link[!dir])) {
						struct rb_node *s = p->link[!last];


						if (s != NULL) {
							if (!is_red(s->link[!last]) && !is_red(s->link[last])) {
								
								p->red = 0;
								s->red = 1;
								q->red = 1;
							}
							else {
								int dir2 = g->link[1] == p;

								if (is_red(s->link[last]))
									g->link[dir2] = rb_double(p, last);
								else if (is_red(s->link[!last]))
									g->link[dir2] = rb_single(p, last);

								
								q->red = g->link[dir2]->red = 1;
								g->link[dir2]->link[0]->red = 0;
								g->link[dir2]->link[1]->red = 0;
							}
						}
					}
				}
			}

		
			if (f != NULL) {
				f->data = q->data;
				p->link[p->link[1] == q] =
					q->link[q->link[0] == NULL];
				free(q);
			}

			
			tree->root = head.link[1];
			if (tree->root != NULL)
				tree->root->red = 0;
		}

		return 1;
	}

//
int main() {




}