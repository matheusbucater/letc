#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void insert(struct node **head, int data, int last) {
    
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;

    if ( *head == NULL ) {
        *head = new_node;
        (*head)->next = *head;
        return;
    }

    struct node *curr_node = *head;
    
    while(curr_node->next != *head) {
        curr_node = curr_node->next;
    }


    curr_node->next = new_node;
    new_node->next = *head;

    if ( !last ) {
        *head = new_node;
    }
}

void display(struct node *head) {
    
    if ( head == NULL ) {
        return;
    }

    struct node *ptr = head;
    do {
        printf("%d", ptr->data);
        if ( ptr->next != head ) {
            printf(", ");
        }
        ptr = ptr->next;
    }
    while ( ptr != head );

    printf("\n");
}

int length(struct node *head) {

    if ( head == NULL) {
        return 0;    
    }
    
    int l = 0;
    struct node *ptr = head;
    do {
        l++;
        ptr = ptr->next;
    }
    while(ptr != head);

    return l;
}

// void delete(struct node **head, int index) {
//     
//     struct node *prev_ptr = NULL;
//     struct node *ptr = *head;
//
//     int 
//
//     if ( index == 0 ) {
//         *head = (*head)->next;
//     }
//
//     for ( int i = 0; i < index; i++ ) {
//         prev_ptr = ptr;
//         ptr = ptr->next;
//     }
//
//     prev_ptr->next = ptr->next;
//
//     free(ptr);
//
// }

int main(void) {

    struct node *head = NULL;

    for ( int i = 0; i < 10; i++ ) {
        insert(&head, i, 1);
    }

    display(head);

    printf("%d\n", length(head));

    free(head);
    return 0;
}
