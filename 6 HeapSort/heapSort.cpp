#include <iostream>
//! To define some basic operations
#define PARENT(i) ((i/2) - 1)
#define LEFT(i) (2 * i + 1)
#define RIGHT(i) (2 * i + 2)
using namespace std;

//! To define the data structure
typedef struct {
    int length;
    int heapSize;
    int *nodes;
}heap;

//! To define the maxHeapify

void maxHeapify(heap *A, int i) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int largest;
    if (l <= A->heapSize && A->nodes[l] > A->nodes[i])
        largest = l;
    else largest = i;
    if (r <= A->heapSize && A->nodes[r] > A->nodes[largest])
        largest = r;
    if( largest != i) {
        swap(A->nodes[i], A->nodes[largest]);
        maxHeapify(A,largest);
    }
}

//! To define the initial maxHeap
void maxHeap(heap *A) {
    // To initialize the heapSize
    A->heapSize = A->length - 1;
    for(int i = A->length / 2 -1; i >=0; i--) 
        maxHeapify(A,i);
}

//! To define the heapSort algorithm
void heapSort(heap *A) {
    maxHeap(A);
    for(int i = A->length - 1; i>0; i--) {
        swap(A->nodes[0], A->nodes[i]);
        A->heapSize = A->heapSize - 1; 
        maxHeapify(A,0);
    }
}


int main() {
    //! Test
    heap *A = new heap;
    A->nodes = new int[10];
    A->nodes[0] = 5;
    A->nodes[1] = 4;
    A->nodes[2] = 3;
    A->nodes[3] = 7;
    A->nodes[4] = 8;
    A->nodes[5] = 1;
    A->nodes[6] = 2;
    A->nodes[7] = 10;
    A->nodes[8] = 7;
    A->nodes[9] = 4;
    A->length = 10;
    heapSort(A);
    for(int i = 0; i < 10; i++) {
        cout << A->nodes[i] << " ";
    }
    cout << endl;
    delete[] A->nodes;
    A -> nodes = nullptr;
    delete A;
    A = nullptr;
    return 0;
}