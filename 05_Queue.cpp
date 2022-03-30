#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    Node *next;
}*first, *last;

Node *createNewNode(int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Queue : Push Tail - Pop Head
void pushTail(int value) {
    Node *newNode = createNewNode(value);
    if(!first) {
        first = last = newNode;
    } else {
        last->next = newNode;
        last = newNode;
    }
}

void popHead() {
    if(!first) {
        return;
    } else if(first == last) {
        free(first);
        first = last = NULL;
    } else {
        Node *temp = first->next;
        first->next = NULL;
        free(first);
        first = temp;
    }
}

void printQueue() {
    if(!first) {
        printf("Stack Empty\n");
    } else {
        Node *curr = first;
        while(curr) {
            printf("%d\n", curr->value);
            curr = curr->next;
        }
        puts("NULL");
    }
}

int main() {
    pushTail(10);
    printQueue();
    pushTail(20);
    pushTail(30);
    printQueue();
    popHead();
    printQueue();
    popHead();
    printQueue();
    popHead();
    printQueue();
    return 0;
}