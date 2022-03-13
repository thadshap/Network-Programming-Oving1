#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;

bool checkPrimeNumber(int n) {
    bool isPrime = true;

    // 0 and 1 are not prime numbers
    if (n == 0 || n == 1) {
        isPrime = false;
    } else {
        for (int i = 2; i <= n / 2; ++i) {
            if (n % i == 0) {
                isPrime = false;
                break;
            }
        }
    }
    return isPrime;
}

int main() {
    int start, end;

    // Ask user to enter lower value of interval
    cout << "Enter lower bound of the interval: ";
    cin >> start; // Take input

    // Ask user to enter upper value of interval
    cout << "\nEnter upper bound of the interval: ";
    cin >> end; // Take input

    // Print display message
    cout << "\nPrime numbers between "
         << start << " and " << end << " are (UNSORTED): ";

    vector<int> primList;
    mutex sum_mutex;

    thread t1([&primList, &sum_mutex,start,end] {
        for (int i = start; i <= end / 2; i++) {

            if (checkPrimeNumber(i)) {
                unique_lock<mutex> lock(sum_mutex); // Locks sum_mutex
                primList.emplace_back(i);
            }
            // Unlocks sum_mutex when lock is destroyed at end of scope
        }
    });

    thread t2([&primList, &sum_mutex,start,end] {
        for (int i = (end / 2) + 1; i <= end; i++) {

            if (checkPrimeNumber(i)) {
                unique_lock<mutex> lock(sum_mutex); // Locks sum_mutex
                primList.emplace_back(i);
            }
            // Unlocks sum_mutex when lock is destroyed at end of scope
        }
    });
    t1.join();
    t2.join();

    for (int x : primList)
        cout << x << " ";

    // sort all the prim numbers from low to high
    sort(primList.begin(), primList.end());

    cout << "\n\nPrime numbers between "
         << start << " and " << end << " are (SORTED): ";

    for (auto x : primList)
        cout << x << " ";

    return 0;
}

