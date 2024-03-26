#include <stdio.h>
#include <stdlib.h>
#include "list.h"

LinkedList* createLinkedList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

void addNodeAtHead(LinkedList* list, char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
}

char removeNodeAtHead(LinkedList* list) {
    if (list->head == NULL) {
        printf("Error: List is empty.\n");
        return '\0';
    }
    Node* temp = list->head;
    char data = temp->data;
    list->head = temp->next;
    free(temp);
    return data;
}

void printList(Node* node) {
    Node* current = node;
    while (current != NULL) {
        printf("%c ", current->data);
        current = current->next;
    }
    printf("\n");
}

void printListReverse(Node* node) {
    Node* current = node;
    if (current == NULL)
        return;
    printListReverse(current->next);
    printf("%c ", current->data);
}

void destroyList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}
