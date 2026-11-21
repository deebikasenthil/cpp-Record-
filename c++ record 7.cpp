
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// Base custom exception class
class BankException : public exception
{
protected:
    string message;

public:
    BankException(string msg)
    {
        message = msg;
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

// Derived exception class
class InsufficientFundsException : public BankException
{
public:
    InsufficientFundsException()
        : BankException("Error: Not enough money in account.")
    {
    }
};

// Another derived exception class
class InvalidAmountException : public BankException
{
public:
    InvalidAmountException()
        : BankException("Error: Enter a valid transaction amount.")
    {
    }
};

// Bank Account class
class BankAccount
{
private:
    string name;
    double balance;

public:
    BankAccount(string n, double b)
    {
        name = n;
        balance = b;
    }

    void deposit(double amount)
    {
        if (amount <= 0)
            throw InvalidAmountException();

        balance += amount;
        cout << "Deposit completed successfully." << endl;
    }

    void withdraw(double amount)
    {
        if (amount <= 0)
            throw InvalidAmountException();

        if (amount > balance)
            throw InsufficientFundsException();

        balance -= amount;
        cout << "Withdrawal completed successfully." << endl;
    }

    void display()
    {
        cout << "Customer Name: " << name << endl;
        cout << "Available Balance: Rs. " << balance << endl;
    }
};

int main()
{
    BankAccount account("Rahul", 8000);

    cout << "Initial Bank Details:" << endl;
    account.display();

    try
    {
        cout << "\nDepositing Rs. 2000..." << endl;
        account.deposit(2000);

        cout << "\nWithdrawing Rs. 3000..." << endl;
        account.withdraw(3000);

        cout << "\nWithdrawing Rs. 15000..." << endl;
        account.withdraw(15000);
    }
    catch (const InsufficientFundsException& e)
    {
        cout << e.what() << endl;
    }
    catch (const InvalidAmountException& e)
    {
        cout << e.what() << endl;
    }
    catch (const BankException& e)
    {
        cout << "Bank Error: " << e.what() << endl;
    }
    catch (const exception& e)
    {
        cout << "General Error: " << e.what() << endl;
    }

    cout << "\nFinal Bank Details:" << endl;
    account.display();

    cout << "\nTransaction process completed." << endl;

    return 0;
}
