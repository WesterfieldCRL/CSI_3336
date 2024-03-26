#ifndef LIST_H
#define LIST_H

typedef struct Node {
    char data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} LinkedList;

LinkedList* createLinkedList();
void addNodeAtHead(LinkedList* list, char data);
char removeNodeAtHead(LinkedList* list);
void printList(Node* node);
void printListReverse(Node* node);
void destroyList(LinkedList* list);

#endif
