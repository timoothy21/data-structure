#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    Node *next;
}*top;

Node *createNewNode(int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}
// Stack : Push Head - Pop Head
void pushHead(int value) {
    Node *newNode = createNewNode(value);
    if(!top) {
        top = newNode;
    } else {
        newNode->next = top;
        top = newNode;
    }
}

void popHead() {
    if(!top) {
        return;
    } else if(top->next == NULL) {
        free(top);
        top = NULL;
    } else {
        Node *temp = top->next;
        top->next = NULL;
        free(top);
        top = temp;
    }
}

void printStack() {
    if(!top) {
        printf("Stack Empty\n");
    } else {
        Node *curr = top;
        while(curr != NULL) {
            printf("%d\n", curr->value);
            curr = curr->next;
        }
        puts("NULL");
    }
}

int main() {
    pushHead(10);
    printStack();
    pushHead(20);
    pushHead(30);
    printStack();
    popHead();
    printStack();
    popHead();
    printStack();
    popHead();
    printStack();
    return 0;
}