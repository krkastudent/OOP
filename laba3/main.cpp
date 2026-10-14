#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <stdexcept>
using namespace std;

class Money {
private:
    long long kopecks;
    mutable int accessCount = 0;
    static int totalCreated;

public:
    Money() : kopecks(0) {
        totalCreated++;
    }

    Money(long long rubles, int cents)
        : kopecks(rubles * 100 + cents) {
        totalCreated++;
    }

    explicit Money(long long cents) : kopecks(cents) {
        totalCreated++;
    }

    long long getKopecks() const {
        accessCount++;
        return kopecks;
    }

    int getAccessCount() const {
        return accessCount;
    }

    void print() const {
        long long amount = getKopecks();

        cout << (amount < 0 ? "-" : "")
             << abs(amount / 100) << " руб. "
             << setw(2) << setfill('0')
             << abs(amount % 100) << " коп."
             << setfill(' ');
    }

    static int getTotalCreated() {
        return totalCreated;
    }

        Money& operator++() {
        ++kopecks;
        return *this;
    }

    Money operator++(int) {
        Money old = *this;
        ++kopecks;
        return old;
    }

    Money& operator--() {
        --kopecks;
        return *this;
    }

    Money operator--(int) {
        Money old = *this;
        --kopecks;
        return old;
    }

int main(){

}