#include <iostream>
#include <stdexcept>

#include "BankAccount.h"

using namespace std;

/**
 * @brief Главная функция программы.
 *
 * Создаёт три объекта класса BankAccount,
 * выполняет корректные и некорректные операции,
 * проверяет сохранение корректного состояния
 * и независимость объектов.
 *
 * @return 0 при успешном завершении программы.
 */
int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "Лабораторная работа №2 по ООП" << endl;
    cout << "Вариант: Банковский счёт" << endl;
    cout << endl;


    /**
     * @brief Создание трёх объектов с использованием разных конструкторов.
     */

    // Конструктор без параметров
    BankAccount account1;


    // Полный параметризованный конструктор
    BankAccount account2(
        "Иван Иванов",
        "1234567890",
        15000.0,
        AccountType::Salary
    );


    // Параметризованный конструктор
    // с автоматическим созданием номера счёта
    BankAccount account3(
        "Пётр Петров",
        5000.0,
        AccountType::Savings
    );


    cout << "Количество существующих объектов: "
         << BankAccount::getObjectCount()
         << endl;


    /**
     * @brief Вывод начального состояния всех объектов.
     */

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


    /**
     * @brief Выполнение корректных операций.
     */

    cout << endl;
    cout << "===== КОРРЕКТНЫЕ ОПЕРАЦИИ =====" << endl;


    account1.deposit(5000.0);

    cout << "На счёт 1 внесено 5000 рублей."
         << endl;


    if (account1.withdraw(1500.0))
    {
        cout << "Со счёта 1 снято 1500 рублей."
             << endl;
    }


    account2.deposit(3000.0);

    cout << "На счёт 2 внесено 3000 рублей."
         << endl;


    if (account2.withdraw(2000.0))
    {
        cout << "Со счёта 2 снято 2000 рублей."
             << endl;
    }


    /**
     * @brief Выполнение некорректных операций.
     *
     * Проверяется реакция класса на отрицательную сумму,
     * недостаток средств, блокировку счёта и
     * некорректные параметры конструктора.
     */

    cout << endl;
    cout << "===== НЕКОРРЕКТНЫЕ ОПЕРАЦИИ =====" << endl;


    // Отрицательное пополнение
    try
    {
        account1.deposit(-1000.0);
    }
    catch (const exception& e)
    {
        cout << e.what() << endl;
    }


    // Попытка снять больше денег, чем есть на счёте
    try
    {
        if (!account2.withdraw(100000.0))
        {
            cout << "Ошибка: недостаточно средств на счёте 2."
                 << endl;
        }
    }
    catch (const exception& e)
    {
        cout << e.what() << endl;
    }


    // Блокировка третьего счёта
    account3.block();


    try
    {
        account3.deposit(1000.0);
    }
    catch (const exception& e)
    {
        cout << e.what() << endl;
    }


    // Попытка создать некорректный объект
    try
    {
        BankAccount badAccount(
            "Алексей",
            "123",
            -500.0,
            AccountType::Debit
        );
    }
    catch (const exception& e)
    {
        cout << e.what() << endl;
    }


    /**
     * @brief Повторный вывод состояния объектов.
     *
     * Позволяет убедиться, что после некорректных
     * операций состояние объектов осталось корректным.
     */

    cout << endl;
    cout << "===== СОСТОЯНИЕ ПОСЛЕ ОПЕРАЦИЙ ====="
         << endl;


    cout << endl;
    cout << "Счёт 1:" << endl;
    account1.printInfo();


    cout << endl;
    cout << "Счёт 2:" << endl;
    account2.printInfo();


    cout << endl;
    cout << "Счёт 3:" << endl;
    account3.printInfo();


    /**
     * @brief Проверка независимости объектов.
     *
     * Изменяется только первый объект,
     * после чего проверяется, что состояние
     * второго и третьего объектов не изменилось.
     */

    cout << endl;
    cout << "===== ПРОВЕРКА НЕЗАВИСИМОСТИ ОБЪЕКТОВ ====="
         << endl;


    double account2BalanceBefore = account2.getBalance();
    double account3BalanceBefore = account3.getBalance();


    // Изменяем только первый счёт
    account1.deposit(2000.0);


    cout << "Изменён только счёт 1."
         << endl;


    cout << "Баланс счёта 1: "
         << account1.getBalance()
         << " руб." << endl;


    cout << "Баланс счёта 2: "
         << account2.getBalance()
         << " руб." << endl;


    cout << "Баланс счёта 3: "
         << account3.getBalance()
         << " руб." << endl;


    if (account2.getBalance() == account2BalanceBefore &&
        account3.getBalance() == account3BalanceBefore)
    {
        cout << "Состояние других объектов не изменилось."
             << endl;
    }


    // Разблокируем третий счёт
    account3.unblock();


    /**
     * @brief Вывод количества объектов перед завершением программы.
     */

    cout << endl;
    cout << "Количество существующих объектов "
            "перед завершением main: "
         << BankAccount::getObjectCount()
         << endl;


    return 0;
}