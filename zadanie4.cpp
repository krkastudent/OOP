#include <iostream>
using namespace std;

int** allocateMatrix(int rows, int cols)
{
    int** matrix = new int*[rows];

    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new int[cols];
    }

    return matrix;
}

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


int main(){

}