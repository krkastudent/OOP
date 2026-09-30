#include "BankAccount.h"

#include <iomanip>
#include <stdexcept>
#include <cctype>
#include <algorithm>

int BankAccount::objectCount = 0;
long long BankAccount::nextAccountNumber = 1000000000;

BankAccount::BankAccount()
    : owner("Без имени"),
      accountNumber(to_string(nextAccountNumber++)),
      balance(0.0),
      type(AccountType::Debit),
      blocked(false)
{
    objectCount++;
}


BankAccount::BankAccount(
    const string& owner,
    const string& accountNumber,
    double initialBalance,
    AccountType type)
    : owner(owner),
      accountNumber(accountNumber),
      balance(initialBalance),
      type(type),
      blocked(false)
{
    validateOwner(owner);
    validateAccountNumber(accountNumber);
    validateBalance(balance);

    objectCount++;
}


BankAccount::BankAccount(
    const string& owner,
    double initialBalance,
    AccountType type)
    : BankAccount(
        owner,
        to_string(nextAccountNumber++),
        initialBalance,
        type)
{
}


BankAccount::~BankAccount()
{
    cout << "Деструктор: счёт "
         << accountNumber
         << " уничтожен." << endl;

    objectCount--;
}

void BankAccount::validateOwner(const string& owner) const
{
    if (owner.empty())
    {
        throw invalid_argument(
            "Ошибка: имя владельца не может быть пустым."
        );
    }
}


void BankAccount::validateAccountNumber(
    const string& number) const
{
    if (number.length() != 10 ||
        !all_of(
            number.begin(),
            number.end(),
            [](unsigned char c)
            {
                return isdigit(c);
            }))
    {
        throw invalid_argument(
            "Ошибка: номер счёта должен содержать ровно 10 цифр."
        );
    }
}


void BankAccount::validateBalance(double balance) const
{
    if (balance < 0)
    {
        throw invalid_argument(
            "Ошибка: начальный баланс не может быть отрицательным."
        );
    }
}

string BankAccount::getOwner() const
{
    return owner;
}


string BankAccount::getAccountNumber() const
{
    return accountNumber;
}


double BankAccount::getBalance() const
{
    return balance;
}


AccountType BankAccount::getType() const
{
    return type;
}


bool BankAccount::isBlocked() const
{
    return blocked;
}

void BankAccount::deposit(double amount)
{
    if (blocked)
    {
        throw runtime_error(
            "Ошибка: счёт заблокирован."
        );
    }

    if (amount <= 0)
    {
        throw invalid_argument(
            "Ошибка: сумма пополнения должна быть больше нуля."
        );
    }

    balance += amount;
}


bool BankAccount::withdraw(double amount)
{
    if (blocked)
    {
        throw runtime_error(
            "Ошибка: счёт заблокирован."
        );
    }

    if (amount <= 0)
    {
        throw invalid_argument(
            "Ошибка: сумма снятия должна быть больше нуля."
        );
    }

    if (amount > balance)
    {
        return false;
    }

    balance -= amount;

    return true;
}

void BankAccount::block()
{
    blocked = true;
}


void BankAccount::unblock()
{
    blocked = false;
}

string accountTypeToString(AccountType type)
{
    switch (type)
    {
    case AccountType::Debit:
        return "Дебетовый";

    case AccountType::Salary:
        return "Зарплатный";

    case AccountType::Savings:
        return "Накопительный";

    default:
        return "Неизвестный";
    }
}

void BankAccount::printInfo() const
{
    cout << "-----------------------------" << endl;

    cout << "Владелец: "
         << owner << endl;

    cout << "Номер счёта: "
         << accountNumber << endl;

    cout << "Баланс: "
         << fixed
         << setprecision(2)
         << balance
         << " руб." << endl;

    cout << "Тип счёта: "
         << accountTypeToString(type)
         << endl;

    cout << "Состояние: "
         << (blocked ? "заблокирован" : "активен")
         << endl;

    cout << "-----------------------------" << endl;
}