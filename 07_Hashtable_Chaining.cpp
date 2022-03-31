#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_BUCKETS = 5; // 5 linked lists

struct Node {
    char name[255]; // node's value
    Node *next; // node's pointer to the next node
}*head[MAX_BUCKETS], *tail[MAX_BUCKETS]; // 5 head and 5 tail

Node *createNode(const char *str) { // create new node
    Node *newNode = (Node *)malloc(sizeof(Node)); // allocate memory with the size of Node
    strcpy(newNode->name, str); // copy the string
    newNode->next = NULL; // set next pointer to NULL by default
    return newNode; // return the newly create Node
}

// Hash : http://www.cse.yorku.ca/~oz/hash.html
// djb2 hash : 
// https://stackoverflow.com/questions/1579721/why-are-5381-and-33-so-important-in-the-djb2-algorithm

// 0000001 << 5 = 0100000
int djb2(const char *str) {
    unsigned long hash = 5381;

    for(int i = 0; str[i] != '\0'; i++) {
        int c = int(str[i]);
        hash = ((hash << 5) + hash) + c;
    }

    return hash % MAX_BUCKETS;
}

void insert(const char *str) { // push tail
    Node *newNode = createNode(str); // create the new node
    int index = djb2(str); // get the hash value

    if(!head[index]) { // if the head is empty
        head[index] = tail[index] = newNode;
    } else { // there is at least one node
        tail[index]->next = newNode; // connect the old tail to the new tail
        tail[index] = newNode; // the node will be the last element of the LL
    }
}

void view() {
    // loop the whole buckets from i = 0 to MAX_BUCKETS
    for(int i = 0; i < MAX_BUCKETS; i++) {
        printf("Index %d: ", i);
        if(head[i]) { // if the LL is not empty
            Node *curr = head[i];
            while(curr) { // traverse the whole LL
                printf("%s -> ", curr->name);
                curr = curr->next; // move one step at a time
            }
        }
        puts("NULL");
    }
}

int main() {
    insert("budi");
    insert("abdul");
    insert("cecep");
    insert("dody");
    insert("aseng");
    insert("bobo");
    insert("dodo");
    insert("dede");
    insert("caca");
    insert("bibi");
    view();
    return 0;
}