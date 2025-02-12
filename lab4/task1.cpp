#include <iostream>
#include <string>

using namespace std;

class Account {
protected:
    int accountNumber;
    double balance;
    string ownerName;

public:

    Account() = default;

    Account(int accNum, double bal, const string& name)
            : accountNumber(accNum), balance(bal), ownerName(name) {}

    Account(const Account&) = delete;

    Account& operator=(const Account&) = delete;


    void deposit(double amount) {
        if (amount > 0) {
            this->balance += amount;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && this->balance >= amount) {
            this->balance -= amount;
        }
    }

    double getBalance() const {
        return this->balance;
    }

    int getAccountNumber() const {
        return this->accountNumber;
    }

    string getOwnerName() const {
        return this->ownerName;
    }
};

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(int accNum, double bal, const string& name, double rate)
            : Account(accNum, bal, name), interestRate(rate) {}

    void calculateInterest() {
        double interest = this->balance * this->interestRate / 100;
        this->deposit(interest);
    }

    double getInterestRate() const {
        return this->interestRate;
    }
};

int main() {
    SavingsAccount savings(123456, 1000.0, "John Doe", 2.5);
    savings.deposit(500.0);
    savings.withdraw(200.0);
    savings.calculateInterest();

    cout << "Account Number: " << savings.getAccountNumber() << endl;
    cout << "Owner's Name: " << savings.getOwnerName() << endl;
    cout << "Current Balance: " << savings.getBalance() << endl;
    cout << "Interest Rate: " << savings.getInterestRate() << "%" << endl;

    return 0;
}