#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

double BuyAndSellStockOnce(const vector<double>& prices) {
  // TODO - you fill in here.
  // can compute all pair wise intervals such that [i] < [j] (valid)
  // throw it into a max heap, return the highest one
  // O(n^2) time
  // O(n^2) space
  double maxDifferenceSoFar = 0;
  double minPriceSoFar = prices.front();
  for (int i = 1; i < prices.size(); i++) {
    auto diff = prices[i] - minPriceSoFar;
    maxDifferenceSoFar = max(maxDifferenceSoFar, diff);
    minPriceSoFar = min(prices[i], minPriceSoFar);
  }
  
  return maxDifferenceSoFar;
}

void test1() {
    vector<double> prices{10, 50, 20, 70, 30, 100};
    assert(BuyAndSellStockOnce(prices) == 90);
}

void test0() {
    vector<double> prices{0};
    assert(BuyAndSellStockOnce(prices) == 0);

    prices = {};
    assert(BuyAndSellStockOnce(prices) == 0);
}

void test2() {
    vector<double> prices{310, 315, 275, 295, 260, 270, 290, 230, 255, 250};
    assert(BuyAndSellStockOnce(prices) == 30);

    // prices = {};
    // assert(BuyAndSellStockOnce(prices) == 0);
}

int main() {
    test1();
    test0();
    test2();
}
