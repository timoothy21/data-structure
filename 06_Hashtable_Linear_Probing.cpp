#include <stdio.h>
#include <string.h>

const int MAX_ELEMENT = 5; // amount of strings that can be stored
const int MAX_LENGTH = 10; // max length of each string
char HASTABLES[MAX_ELEMENT][MAX_LENGTH]; // 5 strings, each max 10 character

// convert a string into an index of an array

// e.g. abdul -> 1
int hashFirstChar(const char *str) { // hash function first character
    // first character of the string while be the index ('a' -> 0, 'b' -> 1, ...)
    // if it's greater than MAX_ELEMENT, it will get modulo
    return (str[0] - 'a') % MAX_ELEMENT; 
}

int hashSumString(const char *str) { // hash function ascii sum
    int sum = 0;
    // looping for sum all the alphabet in string
    for(int i = 0; str[i] != '\0'; i++) {
        sum += str[i] - '0';
    }
    return sum % MAX_ELEMENT;
}

void linearProbing(int idx, const char *str) {
    // Loop from idx + 1 to idx - 1, to find an empty slot
    for(int i = idx+1 % MAX_ELEMENT; i != idx; i = (i+1) % MAX_ELEMENT) {
        if(!HASTABLES[i][0]) { // if empty
            strcpy(HASTABLES[i], str); // insert the element
            return; // quit looping
        }
    }
    puts("TABLE IS FULL"); // if it has finished the loop and HASTABLES is full
}

void insert(const char *str) {
    // int index = hashFirstChar(str); // first, convert the string into an index (First Char)
    int index = hashSumString(str); // first, convert the string into an index (Sum of the string)
    printf("%d\n", index);
    if(!HASTABLES[index][0]) { //if the current index is empty,
        strcpy(HASTABLES[index], str);
    } else { // else if the current index is not empty, do linear probing
        linearProbing(index, str);
    }
}

void view() {
    for(int i = 0; i < MAX_ELEMENT; i++) { // loop the whole hastables
        printf("%d -> %s\n", i, HASTABLES[i]); // print the index and the string stored
    }
}

int main() {
    insert("abdul");
    insert("cecep");
    insert("dody");
    insert("anto");
    insert("aseng");
    insert("bobo");
    view();
}