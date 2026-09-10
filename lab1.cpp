#include <iostream>
using namespace std;

void fillArray(int (&arr)[10]){
    cout << "Введите 10 целых чисел: " << endl;
    for (int i = 0; i < 10; i++){
        cin >> arr[i];
    }
}

void printArray(int (&arr)[10]){
    for (int i = 0; i < 10; i++){
        cout << arr[i] << " ";
    }
}

int main() {
    int array[10];
    fillArray(array);
    cout << "Вывод массива: ";
    printArray(array);
}