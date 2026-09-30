@startuml

title UML-диаграмма класса BankAccount

enum AccountType {
    Debit
    Salary
    Savings
}

class BankAccount {
    - owner : string
    - accountNumber : string
    - balance : double
    - type : AccountType
    - blocked : bool
    - {static} objectCount : int
    - {static} nextAccountNumber : long long

    - validateOwner(owner : string) : void
    - validateAccountNumber(number : string) : void
    - validateBalance(balance : double) : void

    + BankAccount()
    + BankAccount(owner : string, accountNumber : string, initialBalance : double, type : AccountType)
    + BankAccount(owner : string, initialBalance : double, type : AccountType)
    + ~BankAccount()

    + getOwner() : string
    + getAccountNumber() : string
    + getBalance() : double
    + getType() : AccountType
    + isBlocked() : bool

    + deposit(amount : double) : void
    + withdraw(amount : double) : bool
    + block() : void
    + unblock() : void

    + printInfo() : void
    + {static} getObjectCount() : int
}

BankAccount --> AccountType

@enduml