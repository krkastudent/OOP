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