#include <iostream>
#include <mutex>
#include <thread>
using std::mutex;
using std::unique_lock;
using std::thread;
using std::cout;
using std::endl;

int global = 0;

// Separate access to our internal variables
// and access to whatever variable the caller wants
class ReaderWriterLock {
private:
    bool writer;

    int num_readers;
    std::atomic<int> num_writers;

public:
    ReaderWriterLock(const std::mutex& m_, bool writer = false) {
        writer = writer;
        std::unique_lock<std::mutex> lck(m_);
        conditional_variable cv;

        // if reader lock, can only grant if no writer
        // if writer lock, can only grant if no writer and no readers
        if (writer) {
            while (num_writers >= 0 || num_readers >= 0) {
                cv.wait(lck);
            }
        } else {
            while (num_writers >= 0) {
                cv.wait(lck);
            }
        }

        if (writer) {
            cout << "Acquired Write lock" << endl;
            num_writers++;
        } else {
            cout << "Acquired reader lock" << endl;
            num_readers++;
        }
    }

    ~ReaderWriterLock() {
        if (writer) {
            num_writers--;
        }
    }
};

void read(std::mutex m) {
    ReaderWriterLock r(m);
    cout << "Read: " << global << endl;
}

void write(std::mutex m) {
    ReaderWriterLock r(m, true);
    global += 1;
}

int main() {
    mutex increment;

    std::thread read1(read, increment);
    std::thread read2(read, increment);

    std::thread writer(read, increment);
}