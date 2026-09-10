#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int sum = 0;

    for (int i = 1;i <= n; i++){
        if (i % 7 == 3 && i % 11 != 0){
            cout << i << " ";
            sum += i;
        }
    }
    cout << sum;
    return 0;
}