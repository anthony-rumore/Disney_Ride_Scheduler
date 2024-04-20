#include <iostream>
#include <vector>
#pragma once
using namespace std;

class minHeap {
    int parent(int index) {
        return (index - 1) / 2;
    }

    void heapifyUp(int index) {
        while (index > 0 && theheap[index] < theheap[parent(index)]) {
            swap(theheap[index], theheap[parent(index)]);
            index = parent(index);
        }
    }

    void heapifyDown(int index)
    {
        int smallest = index; // Initialize largest as root
        int l = 2 * index + 1; // left = 2*i + 1
        int r = 2 * index + 2; // right = 2*i + 2
        // If left child is smaller than root
        if (l < theheap.size() && theheap[l] < theheap[smallest])
            smallest = l;
        // If right child is smaller than smaller so far
        if (r < theheap.size() && theheap[r] < theheap[smallest])
            smallest = r;
        // If largest is not root
        if (smallest != index) {
            swap(theheap[index], theheap[smallest]);
            heapifyDown(smallest);
        }
    }


public:
    vector<pair<int, float>> theheap;

    void InsertHeap(pair<int, float> interval) {
        theheap.push_back(interval);
        heapifyUp(theheap.size() - 1);
    }

    pair<int, float> getMin() {
        return theheap[0];
    }

    void extractMin() {
        if(theheap.empty()) {
            throw:: out_of_range("empty");
        }

        pair<int, float> min = theheap[0];
        theheap[0] = theheap.back();
        theheap.pop_back();
        heapifyDown(0);
    }
};