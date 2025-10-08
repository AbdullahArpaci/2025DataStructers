#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList {
    int data;
    struct LinkedList *next;
} LinkedList;

void printLinkedList(LinkedList *head);
LinkedList *addValueStart(LinkedList *head, int value);
LinkedList *addValueMiddle(LinkedList *head, int value);
LinkedList *addValueEnd(LinkedList *head, int value);
LinkedList *delValue(LinkedList *head, int value);

int main() {
    LinkedList *head = NULL;

    head = addValueEnd(head, 10);
    head = addValueStart(head, 20);
    head = addValueEnd(head, 30);
    head = addValueEnd(head, 50);
    head = addValueEnd(head, 40);
    head = addValueMiddle(head, 80);

    printLinkedList(head);
    printf("\n");

    head = delValue(head, 50);
    printf("\n");
    printLinkedList(head);

    return 0;
}

void printLinkedList(LinkedList *head) {
    while (head != NULL) {
        printf("[%p:%d]", head, head->data);
        if (head->next != NULL)
            printf("->");
        head = head->next;
    }
    printf("\n");
}

LinkedList *addValueEnd(LinkedList *head, int value) {
    if (head == NULL) {
        LinkedList *node = (LinkedList*)malloc(sizeof(LinkedList));
        node->data = value;
        node->next = NULL;
        return node;
    }

    LinkedList *temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = (LinkedList*)malloc(sizeof(LinkedList));
    temp->next->data = value;
    temp->next->next = NULL;
    return head;
}

LinkedList *addValueStart(LinkedList *head, int value) {
    LinkedList *temp = (LinkedList*)malloc(sizeof(LinkedList));
    temp->data = value;
    temp->next = head;
    return temp;
}

LinkedList *addValueMiddle(LinkedList *head, int value) {
    if (head == NULL) {
        printf("List is empty, adding at start.\n");
        return addValueStart(head, value);
    }

    printLinkedList(head);
    printf("\nEnter number after which to insert %d: ", value);

    int number;
    scanf("%d", &number);

    LinkedList *temp = head;
    while (temp != NULL && temp->data != number)
        temp = temp->next;

    if (temp == NULL) {
        printf("Value %d not found, inserting at end.\n", number);
        return addValueEnd(head, value);
    }

    LinkedList *a = (LinkedList*)malloc(sizeof(LinkedList));
    a->data = value;
    a->next = temp->next;
    temp->next = a;

    return head;
}

LinkedList *delValue(LinkedList *head, int value) {
    if (head == NULL) return NULL;

    if (head->data == value) {
        LinkedList *toDelete = head;
        head = head->next;
        free(toDelete);
        return head;
    }

    LinkedList *temp = head;
    while (temp->next != NULL && temp->next->data != value)
        temp = temp->next;

    if (temp->next == NULL) {
        printf("The number was not found\n");
        return head;
    }

    LinkedList *a = temp->next;
    temp->next = a->next;
    free(a);
    return head;
}
