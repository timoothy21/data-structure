#include <stdio.h>
#include <stdlib.h>

struct Node{
    int value;
    Node *next, *prev;
}*head, *tail;

Node *createNewNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = newNode->prev = NULL;
    return newNode;
}

void pushHead(int value) {
    Node *temp = createNewNode(value);

    if(!head) {
        head = tail = temp;
    } else {
        head->prev = temp;
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
        temp->prev = tail;
        tail = temp;
    }
}

void pushMid(int value) {
    if(!head) {
        Node *temp = createNewNode(value);
        head = tail = temp;
    } else if(value < head->value) {
        pushHead(value);
    } else if(value > tail->value) {
        pushTail(value);
    } else {
        Node *temp = createNewNode(value);
        Node *curr = head;

        while(curr->value < value) {
            curr = curr->next;
        }

        temp->prev = curr->prev;
        temp->next = curr;

        curr->prev->next = temp;
        curr->prev = temp;
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
        head->next = head->prev = NULL;
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
        Node *temp = tail->prev;
        tail->prev = temp->next = NULL;
        free(tail);
        tail = temp;
    }
}

void popMid(int value) {
    if(!head) {
        return;
    } else if(head->value == value) {
        popHead();
    } else if(tail->value == value) {
        popTail();
    } else {
        Node *curr = head;
        while(curr && curr->value != value) {
            curr = curr->next;
        }

        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        curr->prev = curr->next = NULL;
        free(curr);
        curr = NULL;
    }
}

void printLL() {
    Node *curr = head;
    printf("Double Linked List:\n");
    while(curr != NULL) {
        printf("%d <-> ", curr->value);
        curr = curr->next;
    }
    puts("NULL");
}

int main() {
    pushHead(3);
    pushHead(1);
    printLL();
    pushTail(6);
    pushTail(9);
    printLL();
    pushMid(7);
    printLL();
    pushMid(4);
    printLL();
    popHead();
    printLL();
    popTail();
    printLL();
    popMid(6);
    printLL();
    return 0;
}