#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <climits>

using namespace std;
template <typename T, typename Compare = greater<T>>
class Heap {
private:
    vector<T> heap;
    Compare comp; // to make the heap act like a max heap

    void heapifyUp(int index) {
        int parentIndex = (index - 1) / 2;
        while (index > 0 && comp(heap[index], heap[parentIndex])) {
            swap(heap[index], heap[parentIndex]);
            index = parentIndex;
            parentIndex = (index - 1) / 2;
        }
    }

    void heapifyDown(int index, int size) {
        int largest = index;
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        if (leftChild < size && comp(heap[leftChild], heap[largest])) 
            largest = leftChild;

        if (rightChild < size && comp(heap[rightChild], heap[largest])) 
            largest = rightChild;

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest, size);
        }
    }

public:
    Heap() {
        heap.clear();
    }

    Heap(const vector<T>& arr) : heap(arr) {
        buildMaxHeap();
    }

    void insert(const T& value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    T extractTop() {
        if (heap.empty())
            throw runtime_error("Error: empty heap");
        T topValue = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty())
            heapifyDown(0, heap.size());
        return topValue;
    }

    bool isEmpty() const {
        return heap.empty();
    }

    void buildMaxHeap() {
        for (int i = (heap.size() / 2) - 1; i >= 0; --i) {
            heapifyDown(i, heap.size());
        }
    }

//-------------3.Implement a Heap sort----------
    void heapSort() {
        vector<T> temp = heap;
        int originalSize = heap.size();
        buildMaxHeap();
        for (int i = heap.size() - 1; i > 0; --i) {
            swap(heap[0], heap[i]);
            heapifyDown(0, i);
        }
        heap = temp;
    }

    const vector<T>& getHeap() const {
        return heap;
    }
};

//-------------2.Implement a Priority Queue---------
class PriorityQueue {
private:
    using Element = pair<int, int>; // {priority, value}
    Heap<Element> heap;

public:
    PriorityQueue() {}

    void insert(int value, int priority) {
        heap.insert({priority, value});
        cout<<"inserted: Value = "<<value<<", priority = "<<priority<<endl;
    }

    pair<int, int> extractHighestPriority() {
        if (heap.isEmpty())
            throw runtime_error("priority queue is empty.");
        auto top = heap.extractTop();
        cout<<"extracted: Value = "<<top.second<<", priority = "<<top.first<<endl;
        return top;
    }

    bool isEmpty() const {
        return heap.isEmpty();
    }

    void displayQueue() const {
        const auto& elements = heap.getHeap();
        for (const auto& val : elements)
            cout<<"("<<val.first<<", "<<val.second<<") ";
        cout<<endl;
    }
};

int main() {
    PriorityQueue pq;
    pq.insert(10, 1);
    pq.insert(2, 5);
    pq.insert(15, 3);
    pq.displayQueue();

    cout << "\nExtracting elements by priority:\n";
    while (!pq.isEmpty()) {
        auto extracted = pq.extractHighestPriority();
        cout<<"value: "<<extracted.second<<", Priority: "<<extracted.first<<endl;
    }

    vector<int> arr = {10, 20, 5, 7, 30, 15, 1};
    Heap<int> heap(arr);
    cout<<"\noriginal array: ";
    for (auto val : arr)
        cout<<val<<" ";
    cout<<endl;

    cout<<"\nHeap after sorting: ";
    heap.heapSort();
    for (auto val : heap.getHeap())
        cout<<val<<" ";
    cout<<endl;

    cout<<"\ntesting insertions:\n";
    heap.insert(25);
    heap.insert(8);
    heap.insert(40);
    for (auto val : heap.getHeap())
        cout<<val<<" ";
    cout<<endl;

    return 0;
}
