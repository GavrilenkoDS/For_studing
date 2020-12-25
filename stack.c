//data types
#include <stdio.h>
#include <stdlib.h>
//stack
struct stack {
	int data;
	struct stack *next;
};

void push(struct stack ** head,int data){
	struct stack *tmp = malloc(sizeof(struct stack));
    tmp->next = *head;
    tmp->data = data;
    *head = tmp;
}

int pop(struct stack ** head){
	if ((*head) != NULL){
		int ans;
		ans=(*head)->data;
		*head=(*head)->next;
		return ans;
	} else {
		 perror("Error printed by perror");
	}
}

int main(){
	struct stack *st = malloc(sizeof(struct stack));
	int q;
	scanf("%d", &q);
	st->data = q;
	push(&st, 1);
	push(&st, 2);
	push(&st, 3);
	push(&st, 4);
	printf(" %d", pop(&st));
	printf(" %d", pop(&st));
	printf(" %d", pop(&st));
	printf(" %d", pop(&st));
	printf(" %d", pop(&st));
	printf(" %d", pop(&st));
	printf(" %d", pop(&st));

	return EXIT_SUCCESS;
}
