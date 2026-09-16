#include <iostream>
using namespace std;

void process(int*& arr, int& size){
    int negIndex = -1;

    for (int i = 0; i < size; i++){
        if (arr[i] < 0 ){
            negIndex = i;
            break;
        }
    }
    cout << "Первый отрицательный элемент на индексе: " << negIndex << "\n";

    if (negIndex != -1){
        int* newArr = new int[negIndex]{};
        for (int i = 0; i < negIndex; i++){
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        size = negIndex;
    }
}


int main() {
    // 1. Спрашиваем размер массива
    int N;
    cout << "Введите размер массива N: ";
    cin >> N;

    // 2. Выделяем память под массив
    int* arr = new int[N]{};

    cout << "Введите " << N << " целых чисел: " << endl;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    // временный вывод для проверки ввода
    cout << "Введённый массив: ";
    for (int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";

    // 3. Обрабатываем массив
    process(arr, N);

    // 4. Выводим результат
    cout << "Результат: ";
    if (N == 0) {
        cout << "(массив пуст)";
    } else {
        for (int i = 0; i < N; i++) {
            cout << arr[i] << " ";
        }
    }
    cout << "\n";

    delete[] arr;
    return 0;
}