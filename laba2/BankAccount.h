#pragma once

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Тип банковского счёта.
 */
enum class AccountType
{
    Debit,      ///< Дебетовый счёт
    Salary,     ///< Зарплатный счёт
    Savings     ///< Накопительный счёт
};

/**
 * @brief Класс, моделирующий банковский счёт.
 *
 * Класс хранит информацию о владельце, номере счёта,
 * текущем балансе, типе счёта и состоянии блокировки.
 */
class BankAccount
{
private:
    string owner;              ///< Имя владельца счёта
    string accountNumber;      ///< Номер банковского счёта
    double balance;            ///< Текущий баланс
    AccountType type;           ///< Тип банковского счёта
    bool blocked;              ///< Признак блокировки счёта

    static int objectCount;     ///< Количество существующих объектов
    static long long nextAccountNumber; ///< Следующий автоматически создаваемый номер

    /**
     * @brief Проверяет корректность имени владельца.
     * @param owner Имя владельца.
     */
    void validateOwner(const string& owner) const;

    /**
     * @brief Проверяет корректность номера счёта.
     * @param number Номер счёта.
     */
    void validateAccountNumber(const string& number) const;

    /**
     * @brief Проверяет корректность начального баланса.
     * @param balance Начальный баланс.
     */
    void validateBalance(double balance) const;

public:

    /**
     * @brief Создаёт банковский счёт со значениями по умолчанию.
     */
    BankAccount();

    /**
     * @brief Создаёт банковский счёт с заданными параметрами.
     *
     * @param owner Имя владельца.
     * @param accountNumber Номер счёта.
     * @param initialBalance Начальный баланс.
     * @param type Тип счёта.
     */
    BankAccount(
        const string& owner,
        const string& accountNumber,
        double initialBalance,
        AccountType type
    );

    /**
     * @brief Создаёт банковский счёт с автоматическим номером.
     *
     * @param owner Имя владельца.
     * @param initialBalance Начальный баланс.
     * @param type Тип счёта.
     */
    BankAccount(
        const string& owner,
        double initialBalance,
        AccountType type
    );

    /**
     * @brief Уничтожает объект банковского счёта.
     */
    ~BankAccount();

    /**
     * @brief Возвращает имя владельца.
     * @return Имя владельца.
     */
    string getOwner() const;

    /**
     * @brief Возвращает номер счёта.
     * @return Номер счёта.
     */
    string getAccountNumber() const;

    /**
     * @brief Возвращает текущий баланс.
     * @return Баланс счёта.
     */
    double getBalance() const;

    /**
     * @brief Возвращает тип счёта.
     * @return Тип счёта.
     */
    AccountType getType() const;

    /**
     * @brief Проверяет, заблокирован ли счёт.
     * @return true, если счёт заблокирован, иначе false.
     */
    bool isBlocked() const;

    /**
     * @brief Пополняет баланс счёта.
     *
     * @param amount Сумма пополнения.
     * @throws invalid_argument Если сумма меньше или равна нулю.
     * @throws runtime_error Если счёт заблокирован.
     */
    void deposit(double amount);

    /**
     * @brief Снимает деньги со счёта.
     *
     * @param amount Сумма снятия.
     * @return true, если операция выполнена успешно.
     * @return false, если недостаточно средств.
     * @throws invalid_argument Если сумма меньше или равна нулю.
     * @throws runtime_error Если счёт заблокирован.
     */
    bool withdraw(double amount);

    /**
     * @brief Блокирует банковский счёт.
     */
    void block();

    /**
     * @brief Разблокирует банковский счёт.
     */
    void unblock();

    /**
     * @brief Выводит информацию о банковском счёте.
     */
    void printInfo() const;

    /**
     * @brief Возвращает количество существующих объектов класса.
     * @return Количество объектов.
     */
    static int getObjectCount();
};