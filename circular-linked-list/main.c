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

void insert_at(struct node **head, int index, int data) {
    
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;

    if ( *head == NULL ) {
        *head = new_node;
        (*head)->next = *head;
        return;
    }

    if ( (*head)->next == *head ) {
        new_node->next = *head;
        (*head)->next = new_node;
        *head = new_node;
        return;
    }


    struct node *prev_ptr = NULL;
    struct node *ptr = *head;
    
    if ( index == 0 ) {

        do {
            ptr = ptr->next;
        }
        while ( ptr->next != *head );

        ptr->next = new_node;
        new_node->next = *head;
        *head = new_node;
        return;
    }

    for ( int i = 0; i < index; i++ ) {
        prev_ptr = ptr;
        ptr = ptr->next;
    }

    prev_ptr->next = new_node;
    new_node->next = ptr;

}

void update_at(struct node **head, int index, int data) {

    if ( *head == NULL ) {
        printf("err. head is null!");
        return;
    }

    if ( (*head)->next == *head ) {
        (*head)->data = data;
        return;
    }

    struct node *ptr = *head;
    for ( int i = 0; i < index; i++ ) {
        ptr = ptr->next; 
    }

    ptr->data = data;
}

void delete_at(struct node **head, int index) {
    
    if ( *head == NULL ) {
        return;
    }

    if ( (*head)->next == *head ) {
        *head = NULL;
        return;
    }

    if ( index == 0 ) {
        *head = (*head)->next;
        return;
    }

    struct node *prev_ptr = NULL;
    struct node *ptr = *head;

    for ( int i = 0; i < index; i++ ) {
        prev_ptr = ptr;
        ptr = ptr->next;
    }

    prev_ptr->next = ptr->next;

    free(ptr);

}


void sort(struct node **head) {
    struct node *sorted = (struct node*)malloc(sizeof(struct node));

    if ( *head == NULL ) {
        printf("err. head is null!");
        return;
    }

    if ( (*head)->next == *head ) {
        return;
    }

    while (1) {
        struct node *prev_ptr = NULL;
        struct node *ptr = *head;
        int done = 0;

        do {

            prev_ptr = ptr;
            ptr = ptr->next;

            int prev_data = prev_ptr->data;
            int data = ptr->data;

            if ( prev_data > data ) {
                prev_ptr->data = data;
                ptr->data = prev_data;
                done++;
            }
        }
        while ( ptr->next != *head );

        if ( done == 0 ) {
            break;
        }
    }


}

int main(void) {

    struct node *head = NULL;

    // for ( int i = 0; i < 10; i++ ) {
    //     insert(&head, i, 1);
    // }
    //

    insert(&head, 1, 1);
    insert(&head, 3, 1);
    insert(&head, 2, 1);
    insert(&head, 2, 1);
    insert(&head, 5, 1);
    insert(&head, 0, 1);

    display(head);

    sort(&head);

    display(head);

    
    free(head);
    return 0;
}
