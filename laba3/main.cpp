#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <stdexcept>
#include <clocale>
#include <windows.h>

using namespace std;

/**
 * @brief Класс для хранения и обработки денежных сумм.
 *
 * Сумма хранится в целых копейках. Класс поддерживает арифметические
 * операции, сравнение сумм и изменение на одну копейку.
 */
class Money {
private:
    /** @brief Денежная сумма в копейках. */
    long long kopecks;

    /**
     * @brief Счётчик обращений к сумме.
     * @details Поле mutable можно изменять даже у константного объекта.
     */
    mutable int accessCount = 0;

    /** @brief Общее количество созданных объектов Money. */
    static int totalCreated;

public:
    /**
     * @brief Создаёт денежную сумму, равную нулю.
     */
    Money() : kopecks(0) {
        totalCreated++;
    }

    /**
     * @brief Создаёт денежную сумму из рублей и копеек.
     * @param rubles Количество рублей.
     * @param cents Количество копеек.
     */
    Money(long long rubles, int cents)
        : kopecks(rubles * 100 + cents) {
        totalCreated++;
    }

    /**
     * @brief Создаёт денежную сумму из общего количества копеек.
     * @param cents Денежная сумма в копейках.
     * @details explicit запрещает неявное преобразование числа в Money.
     */
    explicit Money(long long cents) : kopecks(cents) {
        totalCreated++;
    }

    /**
     * @brief Возвращает сумму в копейках.
     * @return Денежная сумма в копейках.
     * @details Увеличивает счётчик обращений.
     */
    long long getKopecks() const {
        accessCount++;
        return kopecks;
    }

    /**
     * @brief Возвращает количество обращений к сумме.
     * @return Количество обращений.
     */
    int getAccessCount() const {
        return accessCount;
    }

    /**
     * @brief Выводит денежную сумму в рублях и копейках.
     */
    void print() const {
        long long amount = getKopecks();

        cout << (amount < 0 ? "-" : "")
             << abs(amount / 100) << " руб. "
             << setw(2) << setfill('0')
             << abs(amount % 100) << " коп."
             << setfill(' ');
    }

    /**
     * @brief Возвращает количество созданных объектов.
     * @return Общее количество созданных объектов Money.
     */
    static int getTotalCreated() {
        return totalCreated;
    }

    /**
     * @brief Префиксный инкремент.
     * @return Ссылка на изменённый объект.
     */
    Money& operator++() {
        ++kopecks;
        return *this;
    }

    /**
     * @brief Постфиксный инкремент.
     * @param int Не используется; отличает постфиксную форму.
     * @return Копия объекта до увеличения суммы.
     */
    Money operator++(int) {
        Money old = *this;
        ++kopecks;
        return old;
    }

    /**
     * @brief Префиксный декремент.
     * @return Ссылка на изменённый объект.
     */
    Money& operator--() {
        --kopecks;
        return *this;
    }

    /**
     * @brief Постфиксный декремент.
     * @param int Не используется; отличает постфиксную форму.
     * @return Копия объекта до уменьшения суммы.
     */
    Money operator--(int) {
        Money old = *this;
        --kopecks;
        return old;
    }

    /**
     * @brief Прибавляет денежную сумму к текущей.
     * @param other Денежная сумма для прибавления.
     * @return Ссылка на текущий объект.
     */
    Money& operator+=(const Money& other) {
        kopecks += other.kopecks;
        return *this;
    }

    /**
     * @brief Вычитает денежную сумму из текущей.
     * @param other Денежная сумма для вычитания.
     * @return Ссылка на текущий объект.
     */
    Money& operator-=(const Money& other) {
        kopecks -= other.kopecks;
        return *this;
    }

    /**
     * @brief Умножает текущую сумму на число.
     * @param number Множитель.
     * @return Ссылка на текущий объект.
     */
    Money& operator*=(int number) {
        kopecks *= number;
        return *this;
    }

    /**
     * @brief Делит текущую сумму на число.
     * @param number Делитель, не равный нулю.
     * @return Ссылка на текущий объект.
     * @throws invalid_argument Если делитель равен нулю.
     */
    Money& operator/=(int number) {
        if (number == 0) {
            throw invalid_argument("Деление на ноль");
        }

        kopecks /= number;
        return *this;
    }

    /**
     * @brief Складывает две денежные суммы.
     * @param left Первая сумма.
     * @param right Вторая сумма.
     * @return Результат сложения.
     */
    friend Money operator+(Money left, const Money& right) {
        left += right;
        return left;
    }

    /**
     * @brief Вычитает одну денежную сумму из другой.
     * @param left Уменьшаемая сумма.
     * @param right Вычитаемая сумма.
     * @return Результат вычитания.
     */
    friend Money operator-(Money left, const Money& right) {
        left -= right;
        return left;
    }

    /**
     * @brief Умножает денежную сумму на число.
     * @param left Денежная сумма.
     * @param number Множитель.
     * @return Результат умножения.
     */
    friend Money operator*(Money left, int number) {
        left *= number;
        return left;
    }

    /**
     * @brief Делит денежную сумму на число.
     * @param left Денежная сумма.
     * @param number Делитель.
     * @return Результат деления.
     */
    friend Money operator/(Money left, int number) {
        left /= number;
        return left;
    }

    /**
     * @brief Проверяет, меньше ли текущая сумма другой.
     * @param other Сумма для сравнения.
     * @return true, если текущая сумма меньше.
     */
    bool operator<(const Money& other) const {
        return kopecks < other.kopecks;
    }

    /**
     * @brief Проверяет, больше ли текущая сумма другой.
     * @param other Сумма для сравнения.
     * @return true, если текущая сумма больше.
     */
    bool operator>(const Money& other) const {
        return kopecks > other.kopecks;
    }

    /**
     * @brief Проверяет, меньше ли сумма или равна другой.
     * @param other Сумма для сравнения.
     * @return true, если условие выполняется.
     */
    bool operator<=(const Money& other) const {
        return kopecks <= other.kopecks;
    }

    /**
     * @brief Проверяет, больше ли сумма или равна другой.
     * @param other Сумма для сравнения.
     * @return true, если условие выполняется.
     */
    bool operator>=(const Money& other) const {
        return kopecks >= other.kopecks;
    }

    /**
     * @brief Проверяет равенство денежных сумм.
     * @param other Сумма для сравнения.
     * @return true, если суммы равны.
     */
    bool operator==(const Money& other) const {
        return kopecks == other.kopecks;
    }

    /**
     * @brief Проверяет неравенство денежных сумм.
     * @param other Сумма для сравнения.
     * @return true, если суммы не равны.
     */
    bool operator!=(const Money& other) const {
        return kopecks != other.kopecks;
    }

    /**
     * @brief Деструктор класса Money.
     * @details Выводит сообщение при уничтожении объекта.
     */
    ~Money() {
        cout << "Объект Money уничтожен" << endl;
    }
};

/** @brief Инициализация статического счётчика объектов. */
int Money::totalCreated = 0;

/**
 * @brief Класс банковского счёта.
 *
 * Хранит имя владельца, текущий баланс и историю операций.
 */
class BankAccount {
private:
    /** @brief Имя владельца счёта. */
    string owner;

    /** @brief Текущий баланс счёта. */
    Money balance;

    /** @brief История операций по счёту. */
    vector<string> history;

public:
    /**
     * @brief Создаёт банковский счёт.
     * @param name Имя владельца.
     * @param initialBalance Начальный баланс.
     */
    BankAccount(string name, Money initialBalance)
        : owner(name), balance(initialBalance) {
        history.push_back("Открытие счёта");
    }

    /**
     * @brief Зачисляет деньги на счёт.
     * @param amount Сумма зачисления.
     */
    void deposit(const Money& amount) {
        if (amount <= Money()) {
            cout << "Сумма должна быть положительной\n";
            return;
        }

        balance += amount;
        history.push_back("Зачисление");
        cout << "Деньги зачислены\n";
    }

    /**
     * @brief Списывает деньги со счёта.
     * @param amount Сумма списания.
     */
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

    /**
     * @brief Переводит деньги на другой банковский счёт.
     * @param recipient Счёт получателя.
     * @param amount Сумма перевода.
     */
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

    /**
     * @brief Выводит имя владельца и текущий баланс.
     */
    void showBalance() const {
        cout << owner << ": ";
        balance.print();
        cout << '\n';
    }

    /**
     * @brief Выводит историю операций по счёту.
     */
    void showHistory() const {
        cout << "История операций (" << owner << "):\n";

        for (const string& operation : history) {
            cout << "- " << operation << '\n';
        }
    }
};

/**
 * @brief Демонстрирует работу класса Money и банковских счетов.
 * @return Код завершения программы.
 */
int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "");

    cout << "=== Работа с классом Money ===\n";

    Money a;
    Money b(100, 50);
    Money c(250LL);

    cout << "b = ";
    b.print();

    cout << "\nc = ";
    c.print();
    cout << "\n\n";

    cout << "Постфиксный ++: ";
    (b++).print();

    cout << "\nПосле ++: ";
    b.print();

    cout << "\nПрефиксный ++: ";
    (++b).print();

    cout << "\nПостфиксный --: ";
    (b--).print();

    cout << "\nПрефиксный --: ";
    (--b).print();
    cout << "\n\n";

    cout << "b + c = ";
    (b + c).print();

    cout << "\nb - c = ";
    (b - c).print();

    cout << "\nb * 2 = ";
    (b * 2).print();

    cout << "\nb / 2 = ";
    (b / 2).print();
    cout << "\n\n";

    Money d(10, 0);

    d += Money(5, 0);
    cout << "После +=: ";
    d.print();

    d -= Money(2, 0);
    cout << "\nПосле -=: ";
    d.print();

    d *= 2;
    cout << "\nПосле *=: ";
    d.print();

    d /= 2;
    cout << "\nПосле /=: ";
    d.print();
    cout << "\n\n";

    cout << boolalpha;
    cout << "b < c: " << (b < c) << '\n';
    cout << "b > c: " << (b > c) << '\n';
    cout << "b <= c: " << (b <= c) << '\n';
    cout << "b >= c: " << (b >= c) << '\n';
    cout << "b == c: " << (b == c) << '\n';
    cout << "b != c: " << (b != c) << '\n';

    // Money wrong = 500; // Ошибка: explicit запрещает неявное преобразование.
    Money correct(500LL);

    cout << "\nЯвное создание из копеек: ";
    correct.print();
    cout << '\n';

    const Money constantMoney(123, 45);

    cout << "\nКонстантный объект: ";
    constantMoney.print();

    cout << "\nОбращений к сумме: "
         << constantMoney.getAccessCount() << '\n';

    constantMoney.getKopecks();

    cout << "После повторного обращения: "
         << constantMoney.getAccessCount() << '\n';

    cout << "\nСоздано объектов Money: "
         << Money::getTotalCreated() << "\n\n";

    cout << "=== Банковские счета ===\n";

    BankAccount ivan("Иван", Money(1000, 0));
    BankAccount anna("Анна", Money(500, 0));

    ivan.showBalance();
    anna.showBalance();

    ivan.deposit(Money(200, 50));
    ivan.withdraw(Money(100, 0));
    ivan.transfer(anna, Money(300, 0));

    cout << "\nИтоговые балансы:\n";
    ivan.showBalance();
    anna.showBalance();

    cout << '\n';
    ivan.showHistory();

    cout << '\n';
    anna.showHistory();

    return 0;
}
