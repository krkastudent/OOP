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


    cout << endl;
    cout << "===== НАЧАЛЬНОЕ СОСТОЯНИЕ =====" << endl;

    cout << endl;
    cout << "Счёт 1:" << endl;
    account1.printInfo();

    cout << endl;
    cout << "Счёт 2:" << endl;
    account2.printInfo();

    cout << endl;
    cout << "Счёт 3:" << endl;
    account3.printInfo();



    cout << endl;
    cout << "===== КОРРЕКТНЫЕ ОПЕРАЦИИ =====" << endl;

    account1.deposit(5000.0);
    cout << "На счёт 1 внесено 5000 рублей." << endl;


    if (account1.withdraw(1500.0))
    {
        cout << "Со счёта 1 снято 1500 рублей." << endl;
    }


    account2.deposit(3000.0);
    cout << "На счёт 2 внесено 3000 рублей." << endl;


    if (account2.withdraw(2000.0))
    {
        cout << "Со счёта 2 снято 2000 рублей." << endl;
    }
}

