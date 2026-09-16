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

int& getElement(SafeArray& arr, int index) {
    if (index < 0 || index >= arr.size) {
        cout << "Ошибка: индекс " << index << " вне границ массива (размер " << arr.size << ")\n";
        static int dummy = 0;
        return dummy;
    }
    return arr.data[index];
}

void printSafe(const SafeArray& arr) {
    cout << "Массив: ";
    for (int i = 0; i < arr.size; i++) {
        cout << arr.data[i] << " ";
    }
    cout << "\n";
}

int main(){
    
}