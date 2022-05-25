#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value, height, bf; // store value, height, and balance factor
    Node *left, *right; // pointer to left and right child
};

Node *createNewNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value; // node's value
    newNode->height = 1; // 1 because it will be leaf node (no children)
    newNode->bf = 0; // 0 becuase it has no children
    newNode->left = newNode->right = NULL;
    return newNode;
}

// find the maximum of two number
int max(int a, int b) {
    return (a > b) ? a : b;
}

// get the height of a node
int getHeight(Node *n) {
    return (n) ? n->height : 0;
}

// Recall that to calculate balance factor, it is the height of left child - height of right child
// Balance Factor = height of left child - height of right child
// If Balance Factor in range -1 <= BF <= 1 == balance, else unbalance (need rotation)
int setBF(Node *n) {
    // if(n != NULL) {
    //     return (n->left->height) - (n->right->height);
    // } else {
    //     return 0;
    // }

    // Optimize Code
    // return (n) ? (n->left->height) - (n->right->height) : 0;

    // More optimize Code
    return (n) ? getHeight(n->left) - getHeight(n->right) : 0; 
}

// Recall that to calculate height, it is max height of both children plus one
// Height = max(height from 2 child) + 1
int setHeight(Node *n) {
    // if(n == NULL) {
    //     return 0;
    // } else {
    //     return max(n->left->height, n->right->height) + 1;
    // }

    // Optimize Code
    // return (n) ? max(n->left->height, n->right->height) + 1 : 0;

    // More Optimize Code
    return (n) ? max(getHeight(n->left), getHeight(n->right)) + 1 : 0;
}

Node *updateNode(Node *root) {
    root->bf = setBF(root);
    root->height = setHeight(root);
    return root;
}

Node *leftRotate(Node *root) {
    Node *pivot = root->right;
    Node *pivotLeftChild = pivot->left;
    pivot->left = root; // reverse from root->right = pivot
    root->right = pivotLeftChild;
    // update height and bf
    updateNode(root);
    updateNode(pivot);
    return pivot;
}

Node *rightRotate(Node *root) {
    Node *pivot = root->left;
    Node *pivotRightChild = pivot->right;
    pivot->right = root; // reverse from root->left = pivot
    root->left = pivotRightChild;
    updateNode(root);
    updateNode(pivot);
    return pivot;
}

Node *rotation(Node *root) { // determine type of rotation based on root's BF and child's BF
    if(root->bf < -1 && root->right->bf <= 0) { // left rotation
        return leftRotate(root);
    } else if(root->bf < -1 && root->right->bf > 0) { // right-left rotation
        root->right = rightRotate(root->right);
        return leftRotate(root);
    } else if(root->bf > 1 && root->left->bf >= 0) { // right rotation
        return rightRotate(root);
    } else if(root->bf > 1 && root->left->bf < 0) { // left-right rotation
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    return root;
}

Node *insertNode(Node *root, int value) {
    if(!root) { // empty tree
        return createNewNode(value); // create the node
    } else if(value < root->value) { // if value is lower than parent's value
        root->left = insertNode(root->left, value); // go to the left and connect the pointer
    } else if(value > root->value) { // if value is higher than parent's value
        root->right = insertNode(root->right, value); // go to the right and connect the pointer
    }

    return rotation(updateNode(root)); // update node's height and balance factor, then we will check for unbalanced tree
}

Node *inOrderSuccessor(Node *root) { // kanan sekali, kiri sampai habis
    Node *curr = root->right;
    
    while(curr->left) {
        curr = curr->left;
    }

    return curr;
}

Node *deleteNode(Node *root, int value) {
    if(!root) { // empty tree
        return root;
    } else if(value < root->value) {
        root->left = deleteNode(root->left, value);
    } else if(value > root->value) {
        root->right = deleteNode(root->right, value);
    } else { // we have found the node to be deleted
        if(!root->left || !root->right) { // 0 / 1 child
            Node *newNode = (root->left) ? root->left : root->right;
            root->left = root->right = NULL;
            free(root);
            root = NULL;
            return newNode;
        }

        // 2 children
        Node *Successor = inOrderSuccessor(root);
        root->value = Successor->value;
        root->right = deleteNode(root->right, Successor->value); 
    }

    return rotation(updateNode(root)); // update node's height and balance factor, then we will check for unbalanced tree
}

void inOrder(Node *root) {
    if(root) {
        inOrder(root->left);
        printf("| %-3d | %4d   | %7d        |\n", root->value, root->height, root->bf);
        inOrder(root->right);
    }
}


int main() {
    Node *baseRoot = NULL; // top node of the tree
    int toInsert[] = {10, 11, 12, 5, 3, 2, 8, 7, 4};

    for(int i = 0; i < 9; i++) {
        baseRoot = insertNode(baseRoot, toInsert[i]);
        printf("\nAdded %d to the tree.\n", toInsert[i]);
        printf("| %-3s | %-5s | %-14s |\n", "Key", "Height", "Balance Factor");
        inOrder(baseRoot); getchar();
    }

    for(int i = 0; i < 9; i++) {
        baseRoot = deleteNode(baseRoot, toInsert[i]);
        printf("\nRemoved %d from the tree.\n", toInsert[i]);
        printf("| %-3s | %-5s | %-14s |\n", "Key", "Height", "Balance Factor");
        inOrder(baseRoot); getchar();
    }
    return 0;
}