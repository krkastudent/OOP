#include <iostream>
using namespace std;

struct SafeArray {
    int* data;
    int size;
};

SafeArray createArray(int size) {
    SafeArray arr;
    arr.size = size;
    arr.data = new int[size]{};
    return arr;
}