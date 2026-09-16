#include <iostream>
using namespace std;

int main(){
    int N;
    cout << "Введите размер массива N: ";
    cin >> N;

    int* arr = new int[]{};

    cout << "Введите " << N << " целых чисел: " << endl;
    for (int i = 0; i < N; i++){
        cin >> arr[i];
    }

    cout << "Введённый массив: ";
    for (int i = 0; i < N; i++){
        cout << arr[i] << " ";
    }
    cout << "\n";

    delete[] arr;
    return 0;
}