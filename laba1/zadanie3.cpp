/**
 * @file zadanie3.cpp
 * @brief Работа с безопасным динамическим массивом целых чисел.
 *
 * Программа:
 *  - создаёт динамический массив через структуру SafeArray;
 *  - предоставляет безопасный доступ к элементам с проверкой границ;
 *  - изменяет размер массива с сохранением данных;
 *  - освобождает выделенную память.
 *
 * @author krkastudent Погосян Даниил 606-42
 * @date 2026
 */

#include <iostream>
using namespace std;

/**
 * @brief Структура безопасного динамического массива.
 *
 * Хранит указатель на динамический массив целых чисел
 * и его текущий размер.
 */
struct SafeArray {
    int* data;  ///< Указатель на данные массива.
    int size;   ///< Количество элементов массива.
};

/**
 * @brief Создаёт новый динамический массив.
 *
 * Выделяет память под заданное количество элементов и
 * возвращает структуру SafeArray по значению.
 *
 * @param size Размер создаваемого массива.
 * @return Созданный объект SafeArray.
 */
SafeArray createArray(int size) {
    SafeArray arr;
    arr.size = size;
    arr.data = new int[size]{};
    return arr;
}

/**
 * @brief Возвращает элемент массива по индексу с проверкой границ.
 *
 * При корректном индексе возвращает ссылку на настоящий элемент массива.
 * При ошибочном индексе возвращает ссылку на временную безопасную переменную.
 *
 * @param arr Массив, из которого берётся элемент.
 * @param index Индекс элемента.
 * @return Ссылка на элемент массива.
 */
int& getElement(SafeArray& arr, int index) {
    if (index < 0 || index >= arr.size) {
        cout << "Ошибка: индекс " << index << " вне границ массива (размер " << arr.size << ")\n";
        static int dummy = 0;
        return dummy;
    }

    return arr.data[index];
}

/**
 * @brief Выводит содержимое массива на экран.
 *
 * Массив передаётся по константной ссылке, поэтому функция
 * не может изменить его содержимое.
 *
 * @param arr Массив для вывода.
 */
void printSafe(const SafeArray& arr) {
    cout << "Массив: ";
    for (int i = 0; i < arr.size; i++) {
        cout << arr.data[i] << " ";
    }
    cout << "\n";
}

/**
 * @brief Изменяет размер динамического массива.
 *
 * При уменьшении размера удалённые элементы выводятся на экран.
 * При увеличении новые элементы инициализируются нулями.
 *
 * @param arr Массив, размер которого необходимо изменить.
 * @param M Новый размер массива.
 */
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

/**
 * @brief Точка входа в программу.
 *
 * Последовательно выполняет:
 *  1. Создание динамического массива SafeArray.
 *  2. Заполнение массива начальными значениями.
 *  3. Проверку изменения элемента через getElement().
 *  4. Проверку обработки неверного индекса.
 *  5. Изменение размера массива функцией reSizeArray().
 *  6. Освобождение памяти.
 *
 * @return Код завершения программы.
 *
 * @note После освобождения памяти указатель data обнуляется.
 */
int main() {
    SafeArray myArr = createArray(5);
    for (int i = 0; i < myArr.size; i++) {
        myArr.data[i] = (i + 1) * 10;
    }

    cout << "--- Исходный массив ---\n";
    printSafe(myArr);

    getElement(myArr, 2) = 999;
    cout << "--- После getElement(myArr, 2) = 999; ---\n";
    printSafe(myArr);

    getElement(myArr, 10) = 123;
    cout << "--- После попытки записи по неверному индексу (10) ---\n";
    printSafe(myArr);

    cout << "--- Уменьшаем размер с 5 до 3 ---\n";
    reSizeArray(myArr, 3);
    printSafe(myArr);

    cout << "--- Увеличиваем размер с 3 до 6 ---\n";
    reSizeArray(myArr, 6);
    printSafe(myArr);

    delete[] myArr.data;
    myArr.data = nullptr;

    return 0;
}
