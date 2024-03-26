#include <stdio.h>
#include "list.h"

int main() {
    LinkedList* list = createLinkedList();

    addNodeAtHead(list, 'A');
    addNodeAtHead(list, 'B');
    addNodeAtHead(list, 'C');
    
    printf("List in order: ");
    printList(list->head);
    printf("List in reverse order: ");
    printListReverse(list->head);
    printf("\n");

    printf("Removing nodes from the head: ");
    while (list->head != NULL) {
        printf("%c ", removeNodeAtHead(list));
    }
    printf("\n");

    destroyList(list);

    return 0;
}
