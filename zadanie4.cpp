#include <iostream>
#include <string>

using namespace std;

// 1. Выделение памяти под двумерный массив
int** allocateMatrix(int rows, int cols)
{
    int** matrix = new int*[rows];

    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new int[cols];
    }

    return matrix;
}


// 2. Заполнение матрицы
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


// 3. Красивый вывод матрицы
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


void printMatrix(int** matrix, int rows, int cols, string title)
{
    printMatrix(matrix, rows, cols, true, title);
}


// 5. Освобождение памяти
void freeMatrix(int** matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}


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