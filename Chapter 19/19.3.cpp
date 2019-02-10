#include <iostream>
#include <vector>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <future>
using namespace std;

condition_variable cond_var;
mutex m;

void EvenOdd(vector<int>* A_ptr);

void FillEven(vector<int>* A_ptr) {
    for (int i = 2; i <= 100; i += 2) {
        unique_lock<mutex> lock(m);
        while (A_ptr->back() % 2 == 0) {
            cond_var.wait(lock);
        }
        // At this point, we know the last one is odd, so we can add our next even
        A_ptr->push_back(i);
        lock.unlock();
        cond_var.notify_all();
    }
}

void FillOdd(vector<int>* A_ptr) {
    for (int i = 1; i <= 100; i += 2) {
        unique_lock<mutex> lock(m);
        while (A_ptr->back() % 2 != 0) {
            cond_var.wait(lock);
        }
        // At this point, we know the last one is even, so we can add our next odd
        A_ptr->push_back(i);
        lock.unlock();
        cond_var.notify_all();
    }
}

// int main() {
//     vector<int>* A_ptr = new vector<int>;
//     A_ptr->push_back(0);
//     EvenOdd(A_ptr);

//     for (auto a : *A_ptr) {
//         cout << a << " ";
//     }
//     cout << endl;
// }

// std::condition_variable cv;
// mutex m;

int main() {


  vector<int>* A_ptr = new vector<int>;
  A_ptr->push_back(0);

  auto evens = [&](void){
    //   cout << "in evens" << endl;
    for (int i = 2; i <= 100; i += 2) {
      unique_lock<mutex> lock(m);
    //   cout << "acquired evens lock" << endl;
      while (A_ptr->back() % 2 == 0) {
        //   cout << "in evens while" << endl;
        cond_var.wait(lock);
      }
      A_ptr->push_back(i);
      lock.unlock();
      cond_var.notify_all();
    }
  };

  auto odds = [&](void){
    //   cout << "in odds" << endl;
    for (int i = 1; i <= 100; i += 2) {
      unique_lock<mutex> lock(m);
    //   cout << "acquired odds lock" << endl;
      while (A_ptr->back() % 2 != 0) {
        //   cout << "in odds while" << endl;
        cond_var.wait(lock);
      }
      A_ptr->push_back(i);
      lock.unlock();
      cond_var.notify_all();
    }
  };

  thread a(evens);
  thread b(odds);
  a.join();
  b.join();
  // TODO - you fill in here.
  // we are modifying A_ptr

  for (auto i : *A_ptr) {
      cout << i << " ";
  }
  cout << endl;
  return 0;
}

void EvenOdd(vector<int>* A_ptr) {
    thread evens(::FillEven, A_ptr);
    thread odds(::FillOdd, A_ptr);
    evens.join();
    odds.join();
}
