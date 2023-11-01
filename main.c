#include <cstdlib>
#include <stdio.h>

struct SymbolHash {
    short SymbolDepth;
    short value;
    int Hash;
};

struct CompressionHeader {
    short HuffmannCodingTreeDepth;
    short SymbolCount;
    SymbolHash *SymbolHashMap;
};

struct Node {
    int value,priority;
    Node *next,*left,*right;
};

Node* create_node(int value,int priority) {
    Node *newnode = (Node*)malloc(sizeof(Node));
    newnode->value = value;
    newnode->priority = priority;
    return newnode;
}

Node* create_node(Node *left,Node *right) {
    Node *newnode = (Node*)malloc(sizeof(Node));
    newnode->priority = left->priority+right->priority;
    newnode->left = left;
    newnode->right = right;
    newnode->value = -1;
    return newnode;
}

void pq_insert(Node **pq,int value,int priority) {
    Node *newnode = create_node(value,priority);
    if (*pq==NULL||priority<((*pq)->priority)) {
        newnode->next = *pq;
        *pq = newnode;
    } else {
        Node *current = *pq;
        while (current->next!=NULL&&current->next->priority<=priority) current = current->next;
        newnode->next = current->next;
        current->next = newnode;
    }
}

void pq_insert(Node **pq,Node *left,Node *right) {
    Node *newnode = create_node(left,right);
    if (*pq==NULL||newnode->priority<((*pq)->priority)) {
        newnode->next = *pq;
        *pq = newnode;
    } else {
        Node *current = *pq;
        while (current->next!=NULL&&current->next->priority<=newnode->priority) current = current->next;
        newnode->next = current->next;
        current->next = newnode;
    }
}

void pq_pop(Node **pq) {
    if (*pq == NULL) return;
    *pq = (*pq)->next;
}

void single_merge(Node **pq) {
    Node *left = *pq;
    Node *right = (*pq)->next;
    pq_pop(pq);pq_pop(pq);
    pq_insert(pq,left,right);
}

void mass_merge(Node **pq) {
    while (true) {
        if ((*pq)->next==NULL) break;
        single_merge(pq);
    }
}

void print(Node **pq) {
    while (true) {
        printf("p:%d\tv:%d\n",(*pq)->priority,(*pq)->value);
        if ((*pq)->next==NULL) break;
        (*pq)=(*pq)->next;
    }
}

void load_keys(Node **pq,int *symbols,int path=0,int depth=0) {
    if ((*pq)->value>=0) {
        symbols[(*pq)->value] = path;
        printf("v:%c\tk:%10d\td:%d\tp:%d\n",(*pq)->value,path,depth,(*pq)->priority);
    } else {
        path=path*10;
        if((*pq)->left!=NULL) {
            load_keys(&(*pq)->left,symbols,path+0,depth+1);
        }
        if((*pq)->right!=NULL) {
            load_keys(&(*pq)->right,symbols,path+1,depth+1);
        }
    }
}

int main(int argc,char **argv) {
    Node *pq = NULL;
    int symbols[256] = {0};
    FILE *input = fopen("input.txt","r");
    char charvar;
    while (fscanf(input,"%c",&charvar)==1) {
        symbols[charvar]+=1;
    }
    fclose(input);
    for (int i = 0 ; i < 256; i++) {
        if(symbols[i]<=0) continue;
        pq_insert(&pq,i,symbols[i]);
    }

    mass_merge(&pq);

    load_keys(&pq,symbols);

    printf("%d\n",symbols['i']);

    input = fopen("input.txt","r");
    FILE *output = fopen("output.bin","w");
    while (fscanf(input,"%c",&charvar)==1) {
        fprintf(output,"%d",symbols[charvar]);
    }
    fclose(input);
    fclose(output);

    return 0;
}