#include <iostream>
using namespace std;

// 1. Структура SafeArray
struct SafeArray {
    int* data;
    int size;
};

// 2. Создание массива, выделение памяти, возврат структуры по значению
SafeArray createArray(int size) {
    SafeArray arr;
    arr.size = size;
    arr.data = new int[size]{};
    return arr;
}

// 3. Безопасный доступ к элементу по индексу
int& getElement(SafeArray& arr, int index) {
    // 3.1 Проверка выхода за границы
    if (index < 0 || index >= arr.size) {
        cout << "Ошибка: индекс " << index << " вне границ массива (размер " << arr.size << ")\n";
        static int dummy = 0; 
        return dummy;
    }
    // 3.2 Индекс корректный — возвращаем ссылку на реальный элемент
    return arr.data[index];
}

// 5. Печать массива без возможности его изменить
void printSafe(const SafeArray& arr) {
    cout << "Массив: ";
    for (int i = 0; i < arr.size; i++) {
        cout << arr.data[i] << " ";
    }
    cout << "\n";
}

// 6. Изменение размера массива с N элементов на M
void reSizeArray(SafeArray& arr, int M) {
    int N = arr.size;
    int* newData = new int[M]{};

    if (M < N) {
        // 6.1 Массив уменьшился — выводим удалённые элементы
        cout << "Удалённые элементы: ";
        for (int i = M; i < N; i++) {
            cout << arr.data[i] << " ";
        }
        cout << "\n";

        for (int i = 0; i < M; i++) {
            newData[i] = arr.data[i];
        }
    } else {
        // 6.2 Массив увеличился — старые элементы копируются, новые = 0
        for (int i = 0; i < N; i++) {
            newData[i] = arr.data[i];
        }
    }

    delete[] arr.data;
    arr.data = newData;
    arr.size = M;
}

int main() {
    SafeArray myArr = createArray(5);
    for (int i = 0; i < myArr.size; i++) {
        myArr.data[i] = (i + 1) * 10; // 10 20 30 40 50
    }

    cout << "--- Исходный массив ---\n";
    printSafe(myArr);

    // 4. Использование getElement слева от знака равенства
    getElement(myArr, 2) = 999;
    cout << "--- После getElement(myArr, 2) = 999; ---\n";
    printSafe(myArr);

    getElement(myArr, 10) = 123;
    cout << "--- После попытки записи по неверному индексу (10) ---\n";
    printSafe(myArr);

    // 6. Изменение размера — уменьшение
    cout << "--- Уменьшаем размер с 5 до 3 ---\n";
    reSizeArray(myArr, 3);
    printSafe(myArr);

    // 6. Изменение размера — увеличение
    cout << "--- Увеличиваем размер с 3 до 6 ---\n";
    reSizeArray(myArr, 6);
    printSafe(myArr);

    delete[] myArr.data;
    myArr.data = nullptr;

    return 0;
}