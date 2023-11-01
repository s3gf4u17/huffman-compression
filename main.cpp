#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

class PriorityNode {
public:
    int priority,value;
    PriorityNode *left,*right;
    PriorityNode(int priority,int value) : priority(priority), value(value) {}
    PriorityNode(int priority,PriorityNode *left,PriorityNode *right) : priority(priority), left(left), right(right) {}
};

class PriorityQueue {
public:
    std::vector<PriorityNode> nodes;
    PriorityQueue() {}
    void insert_node(int priority,int value) {
        nodes.push_back(PriorityNode(priority,value));
        std::sort(nodes.begin(),nodes.end(),[](PriorityNode const &a, PriorityNode const &b) {return a.priority>b.priority;});
    }
    void merge_nodes() {
        while (nodes.size()>1) {
            PriorityNode last0 = nodes.back();
            nodes.pop_back();
            PriorityNode last1 = nodes.back();
            nodes.pop_back();
            nodes.push_back(PriorityNode(last0.priority+last1.priority,&last0,&last1));
        }
    }
};

int main() {
    PriorityQueue *pq = new PriorityQueue();

    char ch;
    int symbols[256] = {0};
    std::fstream fin("input.txt",std::fstream::in);
    while (fin>>std::noskipws>>ch) {
        symbols[ch]+=1;
    }

    for (int i= 0; i < 256;i++) {
        if (symbols[i]<=0) continue;
        pq->insert_node(symbols[i],i);
    }

    for (PriorityNode pn : pq->nodes) {
        std::cout << pn.priority << "\t" << pn.value << std::endl;
    }

    pq->merge_nodes();

    std::cout << pq->nodes[0].left->priority << std::endl;

    return 0;
}