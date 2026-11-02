#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Abstract Base Class
class ATM {
protected:
    string name;
    int accountNumber;

public:
    ATM(string n, int acc) {
        name = n;
        accountNumber = acc;
    }

    virtual void showDetails() = 0;

    virtual ~ATM() {}
};

// Inheritance + Encapsulation
class SmartATM : public ATM {
private:
    int pin;
    double balance;
    vector<string> history;

public:
    SmartATM(string n, int acc, int p, double b)
        : ATM(n, acc) {
        pin = p;
        balance = b;
    }

    bool verifyPin(int enteredPin) {
        return pin == enteredPin;
    }

    void showDetails() override {
        cout << "\nAccount Holder: " << name;
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nAvailable Balance: Rs. " << balance << endl;
    }

    void checkBalance() {
        cout << "\nYour Balance: Rs. " << balance << endl;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            history.push_back("Deposited: Rs. " + to_string(amount));
            cout << "Money Deposited Successfully!\n";
        } else {
            cout << "Invalid Amount!\n";
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            history.push_back("Withdrawn: Rs. " + to_string(amount));
            cout << "Please Collect Your Cash!\n";
        } else {
            cout << "Insufficient Balance or Invalid Amount!\n";
        }
    }

    void changePin(int newPin) {
        if (newPin >= 1000 && newPin <= 9999) {
            pin = newPin;
            cout << "PIN Changed Successfully!\n";
        } else {
            cout << "PIN Must Be 4 Digits!\n";
        }
    }

    void showHistory() {
        cout << "\n===== TRANSACTION HISTORY =====\n";

        if (history.empty()) {
            cout << "No Transactions Yet!\n";
        } else {
            for (int i = 0; i < history.size(); i++) {
                cout << i + 1 << ". " << history[i] << endl;
            }
        }
    }
};

int main() {
    string name;
    int accountNumber, pin, enteredPin;
    double balance, amount;

    cout << "===== SMART ATM SYSTEM =====\n";

    cout << "Enter Your Name: ";
    getline(cin, name);

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    cout << "Create 4 Digit ATM PIN: ";
    cin >> pin;

    if (pin < 1000 || pin > 9999) {
        cout << "Invalid PIN! PIN must be 4 digits.\n";
        return 0;
    }

    cout << "Enter Initial Balance: ";
    cin >> balance;

    if (balance < 0) {
        cout << "Invalid Balance!\n";
        return 0;
    }

    SmartATM user(name, accountNumber, pin, balance);

    cout << "\nEnter ATM PIN to Login: ";
    cin >> enteredPin;

    if (!user.verifyPin(enteredPin)) {
        cout << "Incorrect PIN! Access Denied.\n";
        return 0;
    }

    cout << "\nLogin Successful!\n";

    ATM* atm = &user;
    int choice;

    do {
        cout << "\n===== ATM MENU =====\n";
        cout << "1. Account Details\n";
        cout << "2. Check Balance\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Change PIN\n";
        cout << "6. Transaction History\n";
        cout << "7. Exit\n";

        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                atm->showDetails();
                break;

            case 2:
                user.checkBalance();
                break;

            case 3:
                cout << "Enter Deposit Amount: ";
                cin >> amount;
                user.deposit(amount);
                break;

            case 4:
                cout << "Enter Withdrawal Amount: ";
                cin >> amount;
                user.withdraw(amount);
                break;

            case 5:
                cout << "Enter New 4 Digit PIN: ";
                cin >> pin;
                user.changePin(pin);
                break;

            case 6:
                user.showHistory();
                break;

            case 7:
                cout << "Thank You For Using Smart ATM!\n";
                break;

            default:
                cout << "Invalid Choice!\n";
        }

    } while (choice != 7);

    return 0;
}