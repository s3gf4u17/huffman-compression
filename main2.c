#include <stdio.h>
#include <cstdlib>

struct Node {
    int value,priority;
    struct Node* next;
};

void insert_with_priority(struct Node** head, int value, int priority) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->priority = priority;
    newNode->next = NULL;

    if (*head==NULL||priority<(*head)->priority) {
        newNode->next = *head;
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next!=NULL&&current->next->priority<=priority) current = current->next;
        newNode->next = current->next;
        current->next = newNode;
    }
}

void pop(struct Node** head) {
    if (*head==NULL) return;
    *head = (*head)->next;
}

int main() {
    struct Node *pq = NULL;
    insert_with_priority(&pq,42,3);
    insert_with_priority(&pq,10,1);
    insert_with_priority(&pq,30,2);

    while(pq!=NULL) {
        printf("Value: %d, Priority: %d\n", pq->value, pq->priority);
        pop(&pq);
    }

    return 0;
}