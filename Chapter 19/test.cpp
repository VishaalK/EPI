#include <thread>
using namespace std;

void fill(int n) {
    return;
}

int main() {
    thread test(fill, 5);
}