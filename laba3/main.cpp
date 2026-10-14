#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <stdexcept>
using namespace std;

class Money {
private:
    long long kopecks;
    mutable int accessCount = 0;
    static int totalCreated;

public:
    Money() : kopecks(0) {
        totalCreated++;
    }

    Money(long long rubles, int cents)
        : kopecks(rubles * 100 + cents) {
        totalCreated++;
    }

    explicit Money(long long cents) : kopecks(cents) {
        totalCreated++;
    }

    long long getKopecks() const {
        accessCount++;
        return kopecks;
    }

    int getAccessCount() const {
        return accessCount;
    }

    void print() const {
        long long amount = getKopecks();

        cout << (amount < 0 ? "-" : "")
             << abs(amount / 100) << " руб. "
             << setw(2) << setfill('0')
             << abs(amount % 100) << " коп."
             << setfill(' ');
    }

    static int getTotalCreated() {
        return totalCreated;
    }

        Money& operator++() {
        ++kopecks;
        return *this;
    }

    Money operator++(int) {
        Money old = *this;
        ++kopecks;
        return old;
    }

    Money& operator--() {
        --kopecks;
        return *this;
    }

    Money operator--(int) {
        Money old = *this;
        --kopecks;
        return old;
    }

    Money& operator+=(const Money& other) {
        kopecks += other.kopecks;
        return *this;
    }

    Money& operator-=(const Money& other) {
        kopecks -= other.kopecks;
        return *this;
    }

    Money& operator*=(int number) {
        kopecks *= number;
        return *this;
    }

    Money& operator/=(int number) {
        if (number == 0)
            throw invalid_argument("Деление на ноль");

        kopecks /= number;
        return *this;
    }

    friend Money operator+(Money left, const Money& right) {
        left += right;
        return left;
    }

    friend Money operator-(Money left, const Money& right) {
        left -= right;
        return left;
    }

    friend Money operator*(Money left, int number) {
        left *= number;
        return left;
    }

    friend Money operator/(Money left, int number) {
        left /= number;
        return left;
    }

    bool operator<(const Money& other) const {
        return kopecks < other.kopecks;
    }

    bool operator>(const Money& other) const {
        return kopecks > other.kopecks;
    }

    bool operator<=(const Money& other) const {
        return kopecks <= other.kopecks;
    }

    bool operator>=(const Money& other) const {
        return kopecks >= other.kopecks;
    }

    bool operator==(const Money& other) const {
        return kopecks == other.kopecks;
    }

    bool operator!=(const Money& other) const {
        return kopecks != other.kopecks;
    }

    ~Money() {
        cout << "Объект Money уничтожен" << endl;
    }
};
int Money::totalCreated = 0;

class BankAccount {
private:
    string owner;
    Money balance;
    vector<string> history;

public:
    BankAccount(string name, Money initialBalance)
        : owner(name), balance(initialBalance) {
        history.push_back("Открытие счёта");
    }

    void deposit(const Money& amount) {
        if (amount <= Money()) {
            cout << "Сумма должна быть положительной\n";
            return;
        }

        balance += amount;
        history.push_back("Зачисление");
        cout << "Деньги зачислены\n";
    }

    void withdraw(const Money& amount) {
        if (amount <= Money()) {
            cout << "Сумма должна быть положительной\n";
            return;
        }

        if (amount > balance) {
            cout << "Недостаточно средств\n";
            return;
        }

        balance -= amount;
        history.push_back("Расход");
        cout << "Деньги списаны\n";
    }

    void transfer(BankAccount& recipient, const Money& amount) {
        if (this == &recipient) {
            cout << "Нельзя перевести деньги самому себе\n";
            return;
        }

        if (amount <= Money()) {
            cout << "Сумма должна быть положительной\n";
            return;
        }

        if (amount > balance) {
            cout << "Недостаточно средств для перевода\n";
            return;
        }

        balance -= amount;
        recipient.balance += amount;

        history.push_back("Перевод другому клиенту");
        recipient.history.push_back("Получение перевода");

        cout << "Перевод выполнен\n";
    }

    void showBalance() const {
        cout << owner << ": ";
        balance.print();
        cout << '\n';
    }

    void showHistory() const {
        cout << "История операций (" << owner << "):\n";

        for (const string& operation : history) {
            cout << "- " << operation << '\n';
        }
    }
};


int main(){

}