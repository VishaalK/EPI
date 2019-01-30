#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

char convert(int digit) {
    switch (digit) {
        case 16:
        case 15:
        case 14:
        case 13:
        case 12:
        case 11:
        case 10:
            return char(digit - 10 + 'A');
        default:
            return char(digit + '0');
        }
}

int convert(char digit) {
    switch (digit) {
        case 'A':
            return 10;
        case 'B':
            return 11;
        case 'C':
            return 12;
        case 'D':
            return 13;
        case 'E':
            return 14;
        case 'F':
            return 15;
        default:
            return digit - '0';
    }
}

string ConvertBase(const string& num_as_string, int b1, int b2) {
    //  convert to base 10 and then convert back ?
    bool negate = num_as_string.front() == '-' ? true : false;

    int numInBase10 = 0;
    for (char c : num_as_string) {
        if (c == '-') {
            continue;
        }
        int digit = convert(c);
        numInBase10 = numInBase10 * b1 + digit;
        // cout << numInBase10 << endl;
    }

    string ret;
    while (numInBase10) {
        auto digit = numInBase10 % b2;
        numInBase10 /= b2;
        ret.push_back(convert(digit));
    }

    if (ret.empty()) {
        ret.push_back('0');
    }

    if (negate) {
        ret.push_back('-');
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

void test1() {
    auto ans = ConvertBase(string("615"), 7, 13);
    cout << ans << endl;
    assert(ans == "1A7");
}

void test2() {
    auto ans = ConvertBase(string("-615"), 7, 13);
    cout << ans << endl;
    assert(ans == "-1A7");
}

void test3() {
    auto ans = ConvertBase(string("1A7"), 13, 7);
    cout << ans << endl;
    assert(ans == "615");
}

void test4() {
    auto ans = ConvertBase(string("-1A7"), 13, 7);
    cout << ans << endl;
    assert(ans == "-615");
}

void test5() {
    auto ans = ConvertBase(string("0"), 13, 7);
    cout << ans << endl;
    assert(ans == "0");
}

void test6() {
    auto ans = ConvertBase(string("1"), 13, 7);
    cout << ans << endl;
    assert(ans == "1");
}

void test7() {
    auto ans = ConvertBase(string("C"), 13, 7);
    cout << ans << endl;
    assert(ans == "15");
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
}