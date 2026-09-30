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