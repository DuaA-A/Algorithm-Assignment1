#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

class Heap {
private:
    vector<int> heap;

    void heapifyUp(int index) {
        int parentIndex = (index - 1) / 2;
        while (index > 0 && heap[index] > heap[parentIndex]) {
            swap(heap[index], heap[parentIndex]);
            index = parentIndex;
            parentIndex = (index - 1) / 2;
        }
    }

    void heapifyDown(int index, int size) {
        int largest = index;
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;

        if (leftChild < size && heap[leftChild] > heap[largest]) {
            largest = leftChild;
        }
        if (rightChild < size && heap[rightChild] > heap[largest]) {
            largest = rightChild;
        }

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest, size);
        }
    }

public:
    Heap(const vector<int>& arr) : heap(arr) {
        buildMaxHeap();
    }
    Heap(){
        heap.clear();
    }

    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    int extractMax() {
        if (heap.empty()) {
            throw out_of_range("Heap is empty");
        }

        return heap[0];
    }

    int extractMin() {
        if (heap.empty()) {
            throw out_of_range("Heap is empty");
        }

        auto minIt = min_element(heap.begin(), heap.end());
        return *minIt;
    }
    bool isEmpty(){
        return heap.empty();
    }


//-------------3.Implement a Heap sort----------

     void buildMaxHeap() {
        for (int i = (heap.size() / 2) - 1; i >= 0; --i) {
            heapifyDown(i, heap.size());
        }
    }

    void heapSort() {
        int originalSize = heap.size();
        buildMaxHeap();
        for (int i = heap.size() - 1; i > 0; --i) {
            swap(heap[0], heap[i]);
            heapifyDown(0, i);
        }
        heap.resize(originalSize);
    }

    void displayHeap() const {
        for (int val : heap) {
            cout << val << " ";
        }
        cout << endl;
    }
};

//-------------2.Implement a Priority Queue---------
class PriorityQueue{
    Heap maxHeap;
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


    vector<int> arr = {10, 20, 5, 7, 30, 15, 1};
    Heap heap(arr);

    cout << "Original array: ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;

    heap.heapSort();

    cout << "Sorted array: ";
    heap.displayHeap();


    cout << "\nTesting insertions:\n";
    heap.insert(25);
    heap.insert(8);
    heap.insert(40);

    cout << "Heap after insertions: ";
    heap.displayHeap();

    cout << "\nTesting extractMax and extractMin:\n";
    cout << "Max element extracted: " << heap.extractMax() << endl;
    cout << "Min element extracted: " << heap.extractMin() << endl;
    

    return 0;
}
