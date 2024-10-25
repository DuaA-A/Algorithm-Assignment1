#include <iostream>
#include <vector>
using namespace std;
//-------------1.Implement a Heap---------
class MaxHeap {
    vector<int> heap;

public:
    void heapifyUp(int index);
    void heapifyDown(int index);
    void insert(int value);
    int extractMax();
    bool isEmpty();
};

void MaxHeap::heapifyUp(int index) {
    
}

void MaxHeap::heapifyDown(int index) {
    
}

void MaxHeap::insert(int value) {
    
}

int MaxHeap::extractMax() {
    
}

bool MaxHeap::isEmpty() {
    
}

//-------------2.Implement a Priority Queue---------
class PriorityQueue{
    MaxHeap maxHeap;
public:
    void insert(int element){
        maxHeap.insert(element);
    }
    int extractMaxPriority(){
        return maxHeap.extractMax();
    }
    bool isEmpty(){
    return maxHeap.isEmpty();
    }
};
//-------------3.Implement a Heap sort---------
class HeapSort{
    
};


int main(){
    PriorityQueue pq;
    pq.insert(10);
    pq.insert(20);
    pq.insert(15);

    cout << "Elements in order of priority:\n";
    while (!pq.isEmpty()) {
        cout<<pq.extractMaxPriority()<<" ";
    }
    cout<<endl;

    return 0;
}
