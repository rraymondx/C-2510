#include <stdio.h>
#include<stdlib.h>

struct LinkedList {
    int data;
    struct LinkedList *next;
    struct LinkedList *prev;
};

typedef struct LinkedList *node;

void createNode(node tail, int value) {
    node temp;
    temp = malloc(sizeof(struct LinkedList));
    temp->data = value;
    temp->next = NULL;

    node p = tail;

    temp->next = p;
    p->prev->next = temp;
    temp->prev = p->prev;
    p->prev = temp;
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
    while (itr->next != NULL) {
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

void swapNodes(node head, node tail) {
    node first = head->next;
    node second = tail->prev;
    node fNext = first->next;
    node sPrev = second->prev;

    sPrev->next = first;
    first->next = tail;
    first->prev = sPrev;
    tail->prev = first;
    head->next = second;
    second->next = fNext;
    fNext->prev = second;
    second->prev = head;

}

int main() {

    int n = 15;

    node head, tail;
    head = malloc(sizeof(struct LinkedList));
    head->next = tail;
    head->prev = NULL;
    tail = malloc(sizeof(struct LinkedList));
    tail->next = NULL;
    tail->prev = head;

    for(int i = 0; i < n; i++) {
        createNode(tail, i);
    }

    printLL(head);
    swapNodes(head, tail);
    // deleteNode(head, 11);
    printLL(head);
    // deleteLL(head);

    return 0;

}
