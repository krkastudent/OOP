#include <iostream>
#include <stdexcept>

#include "BankAccount.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "Лабораторная работа №2 по ООП" << endl;
    cout << "Вариант: Банковский счёт" << endl;
    cout << endl;


    // Создание трёх объектов разными конструкторами

    BankAccount account1;


    BankAccount account2(
        "Иван Иванов",
        "1234567890",
        15000.0,
        AccountType::Salary
    );


    BankAccount account3(
        "Пётр Петров",
        5000.0,
        AccountType::Savings
    );


    cout << "Количество существующих объектов: "
         << BankAccount::getObjectCount()
         << endl;
}