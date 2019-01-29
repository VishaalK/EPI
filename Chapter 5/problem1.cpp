#include <iostream>
#include <vector>
using namespace std;

void partition(vector<int>& A, int pivotIndex) {
    // int i = 0;
    int pivot = A[pivotIndex];


    // for 
    // if a[0] < a[i], let it be,
    // otherwise, if a[j] == a[i], then swap it with a[i+1], increment i, and continue
    // if a[j] > a[i], swap it with the end, j--, continue, do this until, left > right]
    // int n = A.size();

    // keep track of the current pivot's location
    // if its less than the pivot, swap A[l], A[j]
    // if its greater than the pivot, swap(A[l])
    int left = 0;
    int middle = 0;
    int right = A.size() - 1;
    int iter = 0;
    // int i = 0;

    while (middle < right) {
        if (A[iter] < pivot) {
            swap(A[iter], A[left]);
            iter++, left++, middle++;
        } else if (A[iter] == pivot) {
            swap(A[iter], A[middle]);
            iter++, middle++;
        } else {
            swap(A[right], A[iter]);
            right--;
        }
    }
}

void test1() {
    vector<int> A{2,3,1,2,3,1};
    partition(A, 0);

    for (auto a : A) {
        cout << a << " , ";
    }
    cout << endl;
}

void test2() {
    vector<int> A{2,2,2,2,2,2};
    partition(A, 0);

    for (auto a : A) {
        cout << a << " , ";
    }
    cout << endl;
}

void test3() {
    vector<int> A{0,1,0,1,0,1,0,2};
    partition(A, 1);

    for (auto a : A) {
        cout << a << " , ";
    }
    cout << endl;
}

void test4() {
    vector<int> A{1,1,0,2};
    partition(A, 1);

    for (auto a : A) {
        cout << a << " , ";
    }
    cout << endl;
}

void test5() {
    vector<int> A{1, 0, 2, 0, 2, 1, 2, 1, 2, 0, 0, 0, 1, 0, 2, 1, 0, 2, 0, 1, 0, 2, 1, 0, 2, 1, 2, 0, 2, 1, 1, 2, 2, 0, 1, 1, 0, 1, 1, 1, 2, 1, 0, 1, 2, 1, 2,1, 2, 2, 2, 0, 1, 0, 1, 1, 2, 1, 1, 2, 2, 1, 1, 1, 0, 2, 0, 1, 2, 1, 1, 1, 0, 2, 0, 1, 2, 1, 1, 2, 1, 2, 2, 1, 0, 1, 2, 2, 1, 2, 2, 1, 1, 2, 0, 1, 0, 1, 2, 0, 2, 1, 2, 1, 1, 1, 2, 2, 2, 0, 0, 0, 1, 2, 0, 0, 0, 0};
    partition(A, 101);
    cout << A[101] << endl;
    for (auto a : A) {
        cout << a << " , ";
    }
    cout << endl;
}

void test6() {
    vector<int> A{0, 0, 1, 2, 0, 0, 1, 0, 1, 2, 0, 0, 2, 2, 1, 0, 2, 0, 1, 1, 1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0,1, 2, 0, 0, 1, 1, 1, 1, 1, 2, 1, 0, 1, 2, 1, 2};
    partition(A, 52);
    cout << A[52] << endl;
    for (auto a : A) {
        cout << a << " , ";
    }
    cout << endl;
}

int main() {
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    test6();
}