#include <iostream>
using namespace std;
//! To define the structure
const int INF = 32767;
typedef struct {
    int low;
    int high;
    int sum;    
}node;

//! To solve the middle situation
node findMaxCrossingSubarray(int A[], int low, int mid, int high) {
    int leftSum = -INF , rightSum = - INF;
    int left, right, sum = 0;
    //! From the left to the right
    for (int i = mid; i >= low; i--) {
        sum += A[i];
        if(sum > leftSum) {
            left = i;
            leftSum = sum;
        }
    }
    // To reset the sum
    sum = 0;
    //! From the right to the left
    for (int i = mid + 1; i <= high; i++) {
        sum += A[i];
        if(sum > rightSum) {
            right = i;
            rightSum = sum;
        }
    }
    node result;
    result.sum = leftSum + rightSum;
    result.low = left;
    result.high = right;
    return result;
}

node findMaximumSubarray(int A[], int low, int high) {
    if(A == nullptr) exit(-1);
    node result, left, right, cross;
    if(low == high) {
        result.low = result.high = low;
        result.sum = A[low];
        return result;
    }
    int mid = (low + high) / 2 ;
    left = findMaximumSubarray(A, low, mid);
    right = findMaximumSubarray(A, mid + 1, high);
    cross = findMaxCrossingSubarray(A, low, mid, high);
    if (left.sum >= right.sum && left.sum >=cross.sum) 
        return left;
    else if (right. sum >= left.sum && right.sum >=cross.sum)
        return right;
    else return cross;
}

int main() {
    // To test the question
    int A[] ={13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,-7};
    node q;
    q = findMaximumSubarray(A,0,15);
    cout<<q.low<<endl;
    cout<<q.high<<endl;
    cout<<q.sum<<endl;
    return 0;
}