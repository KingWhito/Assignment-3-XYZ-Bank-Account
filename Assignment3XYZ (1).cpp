#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

// =====================
// Transaction Class
// =====================
class Transaction {
private:
    double amount;
    string type;

public:
    Transaction(double amt, const string& t) {
        if (amt < 0) {
            throw invalid_argument("Transaction amount cannot be negative");
        }
        amount = amt;
        type = t;
    }

    string report() const {
        stringstream ss;
        ss << "Transaction Type: " << type << " | Amount: $" << amount;
        return ss.str();
    }
};

// =====================
// Account Class
// =====================
class Account {
private:
    double balance;                      
    vector<Transaction> log;

public:
    Account(double initialBalance) {
        if (initialBalance >= 1000) {
            balance = initialBalance;
        } else {
            balance = 0;
            cout << "Warning: Initial balance invalid. Balance set to 0." << endl;
        }
    }

    void deposit(double amount) {
        balance += amount;
        addTransaction(Transaction(amount, "Deposit"));
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Debit amount exceeded account balance." << endl;
        } else {
            balance -= amount;
            addTransaction(Transaction(amount, "Withdrawal"));
        }
    }

    double getBalance() {
        addTransaction(Transaction(balance, "Balance Inquiry"));
        return balance;
    }

    void addTransaction(const Transaction& t) {
        log.push_back(t);
    }

    string report() const {
        stringstream ss;
        ss << "==== Transaction Report ====" << endl;
        for (const auto& t : log) {
            ss << t.report() << endl;
        }
        return ss.str();
    }

    void saveToFile(const string& path) const {
        ofstream file(path);
        if (file) {
            throw runtime_error("Could not open file for writing");
        }
        file << report();
        file.close();
    }
};

// =====================
// Main Testing Section
// =====================
int main() {
    try {
        Account acc(1500);

        acc.deposit(500);
        acc.withdraw(200);
        cout << "Current Balance: $" << acc.getBalance() << endl;

        cout << acc.report() << endl;

        acc.saveToFile("C:\\transactions.txt");
        cout << "Transactions saved to C:\\transactions.txt" << endl;

    } catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}