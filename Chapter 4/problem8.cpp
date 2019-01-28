#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

long long reverse(int x) {
    // TODO - you fill in here.
    bool negative = x < 0;
    x = abs(x);

    int power = 0;

    struct digit {
        int digit;
        int power;
    };

    vector<digit> digits;
    while (x) {
        int digit = x % 10;
        digits.push_back({digit, power});
        power++;

        x /= 10;
    }
    power--;

    long long res = 0;
    for (auto digit : digits) {
        // cout << power - digit.power << " , " << digit.digit << endl;
        res += pow(10, power - digit.power) * digit.digit;
    }

    return negative ? -res : res;
    // return 0;
}

void test0() {
    assert(reverse(1) == 1);
    assert(reverse(0) == 0);
}

void test1() {
    cout  << reverse(42) << endl;
    assert(reverse(42) == 24);
}

void test2() {
    cout  << reverse(-213) << endl;
    assert(reverse(-213) == -312);
}

int main() {
    test0();
    test1();
    test2();
}