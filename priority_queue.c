#include <stdio.h>
#include <cstdlib>

struct PQ_NODE {
    PQ_NODE *parent,*child;
    int weight;
    char value;
};



    // int symbols[256] = {0};
    // FILE *file = fopen("input.txt","r");

    // char charvar;
    // while(fscanf(file,"%c",&charvar)==1) {
    //     symbols[charvar] += 1;
    //     // printf("%d ",charvar);
    // }

    // printf("%d",symbols[32]);


// inserts new node into queue
void insert_with_priority(PQ_NODE *rn, int w, char v) {
    PQ_NODE *ln = (PQ_NODE*)malloc(sizeof(PQ_NODE)); // create leaf node
    ln->weight = w; ln->value = v; // fill leaf node data
    while (true) { // find place in queue
        if (rn->weight<=w&&rn->child==NULL) { // leaf goes after, no more nodes after
            rn->child = ln;
            ln->parent = rn;
            break;
        } else if (rn->weight<=w) { // leaf goes after, there is more nodes to check
            rn = rn->child;
        } else if (rn->weight>w&&rn->parent!=NULL) { // leaf goes before, in the middle of the queue
            ln->child = rn;
            ln->parent = rn->parent;
            rn->parent->child = ln;
            rn->parent = ln;
            break;
        } else if (rn->weight>w&&rn->parent==NULL) { // leaf becomes the root node
            ln->child = rn;
            rn->parent = ln;
            break;
        }
    }
}

void print_queue(PQ_NODE *headNode) {
    PQ_NODE *tempNode = headNode;
    while(tempNode->parent!=NULL) tempNode = tempNode->parent;
    while (true) {
        bool parentNULL = (tempNode->parent==NULL);
        printf("weight:%i\tvalue:%c \tparentNULL:%i\n",tempNode->weight,tempNode->value,parentNULL);
        if (tempNode->child==NULL) break;
        tempNode = tempNode->child;
    }
}

int main() {
    PQ_NODE *rootNode = (PQ_NODE*)malloc(sizeof(PQ_NODE));

    insert_with_priority(rootNode,104,'c');
    insert_with_priority(rootNode,101,'a');
    insert_with_priority(rootNode,102,'b');
    insert_with_priority(rootNode,103,'d');
    insert_with_priority(rootNode,97,'e');
    insert_with_priority(rootNode,-1,'f');
    insert_with_priority(rootNode,-7,'g');
    insert_with_priority(rootNode,-6,'h');

    bool test = (-1>-7);
    printf("%d",test);

    print_queue(rootNode);

    return 0;
}