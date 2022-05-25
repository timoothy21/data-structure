#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    Node *next;
}*head, *tail;

Node *createNewNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void pushHead(int value) {
    Node *temp = createNewNode(value);
    if(!head) {
        head = tail = temp;
    } else {
        temp->next = head;
        head = temp;
    }
}

void pushTail(int value) {
    Node *temp = createNewNode(value);
    if(!head) {
        head = tail = temp;
    } else {
        tail->next = temp;
        tail = temp;
    }
}

void popHead() {
    if(!head) {
        return;
    } else if(head == tail) {
        free(head);
        head = tail = NULL;
    } else {
        Node *temp = head->next;
        head->next = NULL;
        free(head);
        head = temp;
    }
}

void popTail() {
    if(!head) {
        return;
    } else if(head == tail) {
        free(head);
        head = tail = NULL;
    } else {
        Node *curr = head;
        while(curr->next != tail) {
            curr = curr->next;
        }
        curr->next = NULL;
        free(tail);
        tail = curr;
    }
}

void printLL() {
    Node *temp = head;
    printf("Linked List: \n");
    while(temp != NULL) {
        printf("%d -> ", temp->value);
        temp = temp->next;
    }
    printf("NULL\n");
}
int main() {
    pushHead(12);
    pushHead(11);
    printLL();
    pushTail(13);
    pushTail(14);
    printLL();
    popHead();
    printLL();
    popTail();
    printLL();
    return 0;
}