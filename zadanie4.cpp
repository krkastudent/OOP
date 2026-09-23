#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Выделяет память под двумерный динамический двумерный массив.
 *
 * Создаёт массив указателей на строки и выделяет память
 * для каждой строки матрицы.
 *
 * @param rows Количество строк матрицы.
 * @param cols Количество столбцов матрицы.
 * @return Указатель на созданную матрицу.
 */
int** allocateMatrix(int rows, int cols)
{
    int** matrix = new int*[rows];

    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new int[cols];
    }

    return matrix;
}


/**
 * @brief Заполняет матрицу значениями, введёнными пользователем.
 *
 * @param matrix Матрица для заполнения.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 */
void fillMatrix(int** matrix, int rows, int cols)
{
    cout << "Введите оценки студентов:" << endl;

    for (int i = 0; i < rows; i++)
    {
        cout << "\nСтудент " << i + 1 << ":" << endl;

        for (int j = 0; j < cols; j++)
        {
            cout << "Оценка по предмету " << j + 1 << ": ";
            cin >> matrix[i][j];
        }
    }
}


/**
 * @brief Выводит матрицу на экран с возможностью отображения рамки.
 *
 * @param matrix Матрица для вывода.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @param showBorders Флаг отображения рамки вокруг матрицы.
 * @param title Заголовок вывода матрицы.
 */
void printMatrix(int** matrix, int rows, int cols,
                 bool showBorders = true,
                 string title = "Matrix")
{
    cout << "\n" << title << endl;

    if (showBorders)
    {
        for (int i = 0; i < cols * 5 + 2; i++)
        {
            cout << "*";
        }

        cout << endl;
    }

    for (int i = 0; i < rows; i++)
    {
        if (showBorders)
            cout << "*";

        for (int j = 0; j < cols; j++)
        {
            cout << "  " << matrix[i][j] << "  ";
        }

        if (showBorders)
            cout << "*";

        cout << endl;
    }

    if (showBorders)
    {
        for (int i = 0; i < cols * 5 + 2; i++)
        {
            cout << "*";
        }

        cout << endl;
    }
}


/**
 * @brief Перегруженная версия вывода матрицы с заголовком.
 *
 * Вызывает основную функцию printMatrix с включённой рамкой.
 *
 * @param matrix Матрица для вывода.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @param title Заголовок вывода.
 */
void printMatrix(int** matrix, int rows, int cols, string title)
{
    printMatrix(matrix, rows, cols, true, title);
}


/**
 * @brief Освобождает память, выделенную под двумерный массив.
 *
 * Удаляет сначала строки матрицы, затем массив указателей.
 *
 * @param matrix Матрица для удаления.
 * @param rows Количество строк.
 */
void freeMatrix(int** matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}


/**
 * @brief Главная функция программы.
 *
 * Выполняет ввод размеров матрицы, создание, заполнение,
 * вывод и освобождение памяти.
 *
 * @return Код завершения программы.
 */
int main()
{
    int rows;
    int cols;

    cout << "Количество студентов: ";
    cin >> rows;

    cout << "Количество предметов: ";
    cin >> cols;

    int** grades = allocateMatrix(rows, cols);

    fillMatrix(grades, rows, cols);


    // 4. Три варианта вызова функции

    printMatrix(grades, rows, cols);

    printMatrix(grades, rows, cols, "Оценки студентов");

    printMatrix(grades, rows, cols, false, "Оценки без рамки");

    freeMatrix(grades, rows);

    return 0;
}