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

void reSizeArray(SafeArray& arr, int M) {
    int N = arr.size;
    int* newData = new int[M]{};

    if (M < N) {
        cout << "Удалённые элементы: ";
        for (int i = M; i < N; i++) {
            cout << arr.data[i] << " ";
        }
        cout << "\n";

        for (int i = 0; i < M; i++) {
            newData[i] = arr.data[i];
        }
    } else {
        for (int i = 0; i < N; i++) {
            newData[i] = arr.data[i];
        }
    }

    delete[] arr.data;
    arr.data = newData;
    arr.size = M;
}



int main(){

}