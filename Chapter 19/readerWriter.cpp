#include <mutex>
#include <iostream>
#include <thread>
using namespace std;

class RWLock {
    private:
        mutex m;
        condition_variable cv;

        int num_readers;
        int num_writers;
    public:
        RWLock(): num_readers(0), num_writers(0) {}

        // caller calls this, and when they return
        // they should have the locks
        void read_lock() {
            std::unique_lock<std::mutex> lck(m);
            while (num_writers > 0) {
                cv.wait(lck);
            }
            cout << "Acquired read lock" << endl;
            num_readers++;
        }

        void read_unlock() {
            std::unique_lock<std::mutex> lck(m);
            num_readers--;
            bool isZero = num_readers == 0;
            lck.unlock();
            if (isZero) {
                cv.notify_all();
            }
        }

        void write_lock() {
            std::unique_lock<std::mutex> lck(m);
            while (num_readers || num_writers) {
                cv.wait(lck);
            }
            cout << "Acquired write lock" << endl;
            num_writers++;
        }

        void write_unlock() {
            std::unique_lock<std::mutex> lck(m);
            num_writers--;
            lck.unlock();
            cv.notify_all();
        }
};

int global = 5;

RWLock rw;

void Read() {
    // cout << "Before read_lock" << endl;
    rw.read_lock();
    // cout << "After read_lock" << endl;
    cout << "Global: " << global << endl;
    rw.read_unlock();
}

void Write() {
    rw.write_lock();
    global += 1;
    rw.write_unlock();
}

int main() {
    // RWLock rw;
    // cout << "Before" << endl;
    std::thread w(::Write);
    std::thread r1(Read);
    // cout << "After" << endl;
    std::thread r2(::Read);

    std::thread r3(::Read);
    std::thread r4(::Read);

    w.join();
    r1.join();
    r2.join();
    r3.join();
    r4.join();

    std::thread r5(::Read);
    r5.join();
}