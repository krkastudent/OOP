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

void swapElements(int (&arr)[10], int &first, int &second){
    int a = arr[first];
    arr[first] = arr[second];
    arr[second] = a;
}

int main() {
    int array[10];
    fillArray(array);
    cout << "Исходный массив: ";
    printArray(array);

    int first = 0;
    int second = 9;
    swapElements(array, first, second);
    cout << "Массив, после обмена первого и последнего элемента: ";
    printArray(array);
}