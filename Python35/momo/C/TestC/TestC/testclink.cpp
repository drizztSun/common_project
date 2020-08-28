#include<stdio.h>
#include<stdlib.h>


typedef struct node {
    int val;
    struct node* next;
} node_t;


int test_clink() {

    node_t* head = (node_t*)malloc(sizeof(node_t));
    if (head == NULL) {
        return 1;
    }

    head->val = 1;
    head->next = NULL;

    //We've just created the first variable in the list. We must set the value, and the next item to be empty, if we want to finish populating the list. Notice that we should always check if malloc returned a NULL value or not.

    //To add a variable to the end of the list, we can just continue advancing to the next pointer :

    head = NULL;
    head = (node_t*)malloc(sizeof(node_t));
    head->val = 1;
    head->next = (node_t*)malloc(sizeof(node_t));
    head->next->val = 2;
    head->next->next = NULL;

    free(head);
    free(head->next);
}

