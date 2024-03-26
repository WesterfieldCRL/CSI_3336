/**
* file: fileInfo.c
* author: Wesley Anastasi
* course: CSI 3336
* assignment: project 6
* due date: 3/25/2024
*
* date modified: 3/25/2024
* - file created
*
* This file will read file information and sort by size, access time, modified time, or status change time
*/


#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>


struct FileInfo {
    char *path;
    struct stat info;
};


typedef struct Node {
    struct FileInfo file;
    struct Node *next;
} node;

void swap(struct Node *a, struct Node *b) {
    struct FileInfo temp = a->file;
    a->file = b->file;
    b->file = temp;
}

int compareSize(struct FileInfo a, struct FileInfo b) {
    return a.info.st_size - b.info.st_size;
}

int compareAccessTime(struct FileInfo a, struct FileInfo b) {
    return a.info.st_atime - b.info.st_atime;
}

int compareModificationTime(struct FileInfo a, struct FileInfo b) {
    return a.info.st_mtime - b.info.st_mtime;
}

int compareStatusChangeTime(struct FileInfo a, struct FileInfo b) {
    return a.info.st_ctime - b.info.st_ctime;
}

void bubbleSort(struct Node *start, int (*compare)(struct FileInfo, struct FileInfo)){
    int swapped;
    struct Node *ptr1;
    struct Node *lptr = NULL;

    if (start == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr) {
            if (compare(ptr1->file, ptr1->next->file) > 0) {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

int stringLength(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void insertNode(node **head, struct FileInfo file) {
    node *newNode = (node *)malloc(sizeof(node));
    newNode->file = file;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}


int menu() {
    char *menu = "Choose your order:\n"
                 "1. by size\n"
                 "2. by access time\n"
                 "3. by modified time\n"
                 "4. by status change time\n"
                 ": ";
    int menuLength = stringLength(menu);
    write(STDOUT_FILENO, menu, menuLength);

    char choice;
    read(STDIN_FILENO, &choice, 1);
    return choice - '0';
}

int main(int argc, char *argv[]) {
    node *head = NULL;

    int i = 1;
    while (i < argc) {
        struct FileInfo file;
        file.path = argv[i];
        if (stat(file.path, &file.info) == 0) {
            insertNode(&head, file);
        } else {
            char *error_msg = "Error: Unable to get information for file: ";
            int error_msg_length = stringLength(error_msg);
            write(STDERR_FILENO, error_msg, error_msg_length);
            write(STDERR_FILENO, file.path, stringLength(file.path));
            write(STDERR_FILENO, "\n", 1);
        }
        i++;
    }

    int choice = menu();

    switch (choice) {
        case 1:
            bubbleSort(head, compareSize);
            break;
        case 2:
            bubbleSort(head, compareAccessTime);
            break;
        case 3:
            bubbleSort(head, compareModificationTime);
            break;
        case 4:
            bubbleSort(head, compareStatusChangeTime);
            break;
        default: {
            char *invalid_choice = "Invalid choice.\n";
            int invalid_choice_length = stringLength(invalid_choice);
            write(STDERR_FILENO, invalid_choice, invalid_choice_length);
            return 1;
        }
    }

    node *current = head;
    while (current != NULL) {
        write(STDOUT_FILENO, current->file.path, stringLength(current->file.path));
        write(STDOUT_FILENO, " ", 1);
        current = current->next;
    }
    write(STDOUT_FILENO, "\n", 1);

    while (head != NULL) {
        node *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

