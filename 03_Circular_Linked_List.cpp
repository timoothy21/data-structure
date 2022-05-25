#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    Node *next;
}*head;

Node *createNewNode(int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void pushTail(int value) {
    Node *newNode = createNewNode(value);
    if(!head) {
        head = newNode;
        head->next = head;
    } else {
        Node *curr = head;
        while(curr->next != head) {
            curr = curr->next;
        }
        curr->next = newNode;
        newNode->next = head;
    }
}

void printCircularLL() {
    if(!head) {
        printf("LL Empty\n");
    } else {
        Node *curr = head->next;
        printf("%d -> ", head->value);
        while(curr != head) {
            printf("%d -> ", curr->value);
            curr = curr->next;
        }
        printf("%d ", head->value);
    }
}

int main() {
    pushTail(1);
    pushTail(2);
    pushTail(3);
    printCircularLL();

    return 0;
}