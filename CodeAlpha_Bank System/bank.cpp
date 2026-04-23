#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// ================= TRANSACTION =================
class Transaction {
public:
    string type;
    double amount;

    Transaction(string t, double a) {
        type = t;
        amount = a;
    }

    void display() const {
        cout << left << setw(15) << type
             << " | " << amount << endl;
    }
};

// ================= ACCOUNT =================
class Account {
private:
    int accountNumber;
    string holderName;
    string accountType;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accNo, string name, string type, double openingBalance) {
        accountNumber = accNo;
        holderName = name;
        accountType = type;
        balance = openingBalance;

        transactions.push_back(Transaction("Opening Balance", openingBalance));
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid amount!\n";
            return;
        }
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount));
        cout << "Deposit successful!\n";
    }

    void withdraw(double amount) {
        if (amount <= 0 || amount > balance) {
            cout << "Invalid or insufficient balance!\n";
            return;
        }
        balance -= amount;
        transactions.push_back(Transaction("Withdraw", amount));
        cout << "Withdraw successful!\n";
    }

    void transfer(Account &toAccount, double amount) {
        if (amount <= 0 || amount > balance) {
            cout << "Transfer failed!\n";
            return;
        }

        balance -= amount;
        toAccount.balance += amount;

        transactions.push_back(Transaction("Transfer Out", amount));
        toAccount.transactions.push_back(Transaction("Transfer In", amount));

        cout << "Transfer successful!\n";
    }

    void showTransactions() const {
        cout << "\n===== Transaction History =====\n";
        cout << "Account No: " << accountNumber << endl;

        for (const auto &t : transactions) {
            t.display();
        }
    }

    void displayAccount() const {
        cout << "\n=================================\n";
        cout << "Account No   : " << accountNumber << endl;
        cout << "Holder Name  : " << holderName << endl;
        cout << "Account Type : " << accountType << endl;
        cout << "Balance      : " << balance << endl;
        cout << "=================================\n";
    }
};

// ================= CUSTOMER =================
class Customer {
private:
    int id;
    string name;
    vector<Account*> accounts;   // FIXED: pointers instead of copies

public:
    Customer(int i, string n) {
        id = i;
        name = n;
    }

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    void addAccount(Account* acc) {
        accounts.push_back(acc);
    }

    Account* getAccount(int accNo) {
        for (auto acc : accounts) {
            if (acc->getAccountNumber() == accNo) {
                return acc;
            }
        }
        return nullptr;
    }

    void displayCustomer() const {
        cout << "\n######## CUSTOMER DETAILS ########\n";
        cout << "Customer ID : " << id << endl;
        cout << "Name        : " << name << endl;

        for (auto acc : accounts) {
            acc->displayAccount();
        }
    }
};

// ================= BANK SYSTEM =================
class BankSystem {
private:
    vector<Customer> customers;
    vector<Account> accounts;

    int nextCustomerId = 1;
    int nextAccountNumber = 1001;

public:
    void createCustomer() {
        string name;
        cout << "Enter customer name: ";
        cin >> name;

        customers.push_back(Customer(nextCustomerId, name));

        cout << "\nCustomer created successfully!\n";
        cout << "Customer ID: " << nextCustomerId << endl;

        nextCustomerId++;
    }

    Customer* findCustomer(int id) {
        for (auto &c : customers) {
            if (c.getId() == id) {
                return &c;
            }
        }
        return nullptr;
    }

    void createAccount() {
        int id;
        string type;
        double openingBalance;

        cout << "Enter customer ID: ";
        cin >> id;

        Customer* c = findCustomer(id);
        if (!c) {
            cout << "Customer not found!\n";
            return;
        }

        cout << "Enter account type (Savings/Current): ";
        cin >> type;

        cout << "Enter opening balance: ";
        cin >> openingBalance;

        Account newAcc(nextAccountNumber++, c->getName(), type, openingBalance);

        cout << "\n===== ACCOUNT CREATED =====\n";
        newAcc.displayAccount();

        accounts.push_back(newAcc);
        c->addAccount(&accounts.back());
    }

    void deposit() {
        int cid, accNo;
        double amount;

        cout << "Customer ID: ";
        cin >> cid;

        Customer* c = findCustomer(cid);
        if (!c) {
            cout << "Customer not found!\n";
            return;
        }

        cout << "Account Number: ";
        cin >> accNo;

        Account* acc = c->getAccount(accNo);
        if (!acc) {
            cout << "Account not found!\n";
            return;
        }

        cout << "Amount: ";
        cin >> amount;

        acc->deposit(amount);
    }

    void withdraw() {
        int cid, accNo;
        double amount;

        cout << "Customer ID: ";
        cin >> cid;

        Customer* c = findCustomer(cid);
        if (!c) {
            cout << "Customer not found!\n";
            return;
        }

        cout << "Account Number: ";
        cin >> accNo;

        Account* acc = c->getAccount(accNo);
        if (!acc) {
            cout << "Account not found!\n";
            return;
        }

        cout << "Amount: ";
        cin >> amount;

        acc->withdraw(amount);
    }

    void transfer() {
        int cid1, cid2, acc1, acc2;
        double amount;

        cout << "From Customer ID: ";
        cin >> cid1;

        cout << "From Account No: ";
        cin >> acc1;

        cout << "To Customer ID: ";
        cin >> cid2;

        cout << "To Account No: ";
        cin >> acc2;

        Customer* c1 = findCustomer(cid1);
        Customer* c2 = findCustomer(cid2);

        if (!c1 || !c2) {
            cout << "Customer not found!\n";
            return;
        }

        Account* a1 = c1->getAccount(acc1);
        Account* a2 = c2->getAccount(acc2);

        if (!a1 || !a2) {
            cout << "Account not found!\n";
            return;
        }

        cout << "Amount: ";
        cin >> amount;

        a1->transfer(*a2, amount);
    }

    void showAll() {
        for (auto &c : customers) {
            c.displayCustomer();
        }
    }
};

// ================= MAIN =================
int main() {
    BankSystem bank;
    int choice;

    do {
        cout << "\n========== BANK MENU ==========\n";
        cout << "1. Create Customer\n";
        cout << "2. Create Account\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Transfer\n";
        cout << "6. Show All Data\n";
        cout << "0. Exit\n";
        cout << "================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bank.createCustomer(); break;
            case 2: bank.createAccount(); break;
            case 3: bank.deposit(); break;
            case 4: bank.withdraw(); break;
            case 5: bank.transfer(); break;
            case 6: bank.showAll(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}