#pragma once
#include <iostream>
#include <string>
using namespace std;

enum class AccountType
{
    Debit,
    Salary,
    Savings
};

class BankAccount
{
    private:
    string owner;
    string accountNumber;
    double balance;
    AccountType type;
    bool blocked;

    static int objectCount;
    static long long nextAccountNumber;
    
    void validateOwner(const string& owner) const;
    void validateAccountNumber(const string& number) const;
    void validateBalance(double balance) const;
};