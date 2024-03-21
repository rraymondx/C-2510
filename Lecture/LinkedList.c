#include <stdio.h>
#include<stdlib.h>

struct LinkedList {
    int data;
    struct LinkedList *next;
};

typedef struct LinkedList *node;

void createNode(node head, int value) {
    node temp;
    temp = malloc(sizeof(struct LinkedList));
    temp->data = value;
    temp->next = NULL;

    node p = head;
    while(p->next != NULL) {
        p = p->next;
    }
    // raeching this: you are at the tail
    p->next = temp;

}

void deleteNode(node head, int value) {

    node prev = head;
    node curr = head->next;
    
    while (curr != NULL && curr->data != value) {
        curr = curr->next;
        prev = prev->next;
    }
    // found a match or does not exist
    if (curr == NULL) {
        return;
    } else {
        // i have a match
        prev->next = curr->next;
        free(curr);
    }

}

void printLL(node head) {
    node itr = head->next;
    while (itr != NULL) {
        printf("%d ", itr->data);
        itr = itr->next;
    }
    printf("\n");
}

void deleteLL(node head) {
    node prev = head;
    node curr = head->next;

    while(curr != NULL) {
        free(prev);
        prev = curr;
        curr = curr->next;
    }
    free(prev);
}


// node createNode() {
//     node temp;
//     temp = malloc(sizeof(struct LinkedList));
//     temp->next = NULL;
//     return temp;
// }

int main() {

    int n = 10;

    node head;
    head = malloc(sizeof(struct LinkedList));
    head->next = NULL;

    for(int i = 0; i < n; i++) {
        createNode(head, i);
    }

    printLL(head);
    deleteNode(head, 15);
    printLL(head);
    deleteLL(head);

    return 0;

}

// int main() {

    // node first = createNode();
    // first->data = 1;

    // node second = createNode();
    // second->data = 2;
    // first->next = second;

    // node third = createNode();
    // third->data = 3;
    // second->next = third;

    // printf("%d\n", first->data);
    // printf("%d\n", first->next->data);
    // printf("%d\n", first->next->next->data);

//     return 0;

// }