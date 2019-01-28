#include <iostream>
#include <cassert>
#include <cmath>
#include <random>
using namespace std;

class Solution {
    public:
        double pow(double x, int y) {
            // gotta handle negative numbers
            bool negative = false;
            if (y < 0) {
                negative = true;
                y = abs(y);
            }

            if (y == 0) {
                return 1;
            }

            if (x == 0) {
                return 0;
            }

            int powerOf2 = getPowerOf2ClosestToN(y);
            int curPower = 1;
            double res = x;
            while (powerOf2--) {
                curPower *= 2;
                res *= res;
            }

            int remainder = y % curPower;

            res *= pow(x, remainder);
            // while (remainder--) {
            //     res *= x;
            // }

            return negative ? 1/res : res;
        }

        // less than or equal to N ?
        int getPowerOf2ClosestToN(int n) {
            if (n == 0 || n == 1) {
                return 0;
            }

            int ret = 0;
            while (n >>= 1) {
                ret++;
            }

            return ret;
        }
};


void test0() {
    assert(Solution().getPowerOf2ClosestToN(0) == 0);
    assert(Solution().getPowerOf2ClosestToN(1) == 0);
    assert(Solution().getPowerOf2ClosestToN(2) == 1);
    assert(Solution().getPowerOf2ClosestToN(3) == 1);
    assert(Solution().getPowerOf2ClosestToN(7) == 2);
    assert(Solution().getPowerOf2ClosestToN(8) == 3);
}

void test1() {
    assert(Solution().pow(0,0) == 1);
    assert(Solution().pow(1,0) == 1);
    assert(Solution().pow(0,1) == 0);
}

void test2() {
    assert(Solution().pow(2,1) == 2);
    assert(Solution().pow(9,1) == 9);
    assert(Solution().pow(2,5) == 32);
}

void test3() {
    cout << Solution().pow(1.4434757236195281, 12) << endl;
    cout << "actual: " << Solution().pow(-1.0006612108596369, -2217) << ", expected: " << -0.23098094677379155;
}

void randomTesting() {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,9);
    int numRolls = 100;

    while (numRolls--) {
        int a = distribution(generator), b = distribution(generator);
        if (Solution().pow(a,b) != pow(a,b)) {
            cout << a << " " << b << endl;
        }
    }
}

int main() {
    // test0();
    // test1();
    // test2();
    // randomTesting();
    test3();
}