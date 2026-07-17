#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class BankAccount
{
private:
    int accountNo;
    char name[50];
    float balance;

public:
    void createAccount();
    void showAccount() const;
    void modifyAccount();
    void deposit(float);
    void withdraw(float);
    int getAccountNo() const;
    float getBalance() const;
};

void BankAccount::createAccount()
{
    cout << "\nEnter Account Number: ";
    cin >> accountNo;

    cin.ignore();

    cout << "Enter Account Holder Name: ";
    cin.getline(name, 50);

    cout << "Enter Initial Deposit: ";
    cin >> balance;

    cout << "\nAccount Created Successfully!\n";
}

void BankAccount::showAccount() const
{
    cout << "\nAccount Number : " << accountNo;
    cout << "\nAccount Holder : " << name;
    cout << "\nCurrent Balance: Rs. " << balance << endl;
}

void BankAccount::modifyAccount()
{
    cout << "\nModify Account Holder Name: ";
    cin.ignore();
    cin.getline(name, 50);

    cout << "Modify Balance: ";
    cin >> balance;
}

void BankAccount::deposit(float amount)
{
    balance += amount;
}

void BankAccount::withdraw(float amount)
{
    if(amount > balance)
        cout << "\nInsufficient Balance!\n";
    else
    {
        balance -= amount;
        cout << "\nWithdrawal Successful.\n";
    }
}

int BankAccount::getAccountNo() const
{
    return accountNo;
}

float BankAccount::getBalance() const
{
    return balance;
}

//---------------------------------------------------------

void writeAccount()
{
    BankAccount acc;

    ofstream outFile("bank.dat", ios::binary | ios::app);

    acc.createAccount();

    outFile.write(reinterpret_cast<char *>(&acc), sizeof(BankAccount));

    outFile.close();
}

void displayAccount(int accNo)
{
    BankAccount acc;

    bool found = false;

    ifstream inFile("bank.dat", ios::binary);

    while(inFile.read(reinterpret_cast<char *>(&acc), sizeof(BankAccount)))
    {
        if(acc.getAccountNo() == accNo)
        {
            acc.showAccount();
            found = true;
        }
    }

    inFile.close();

    if(!found)
        cout << "\nAccount Not Found.\n";
}

void depositWithdraw(int accNo, int option)
{
    BankAccount acc;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    bool found = false;

    while(file.read(reinterpret_cast<char *>(&acc), sizeof(BankAccount)) && !found)
    {
        if(acc.getAccountNo() == accNo)
        {
            acc.showAccount();

            float amount;

            if(option == 1)
            {
                cout << "\nEnter Deposit Amount: ";
                cin >> amount;
                acc.deposit(amount);
            }
            else
            {
                cout << "\nEnter Withdrawal Amount: ";
                cin >> amount;
                acc.withdraw(amount);
            }

            int pos = (-1) * static_cast<int>(sizeof(BankAccount));

            file.seekp(pos, ios::cur);

            file.write(reinterpret_cast<char *>(&acc), sizeof(BankAccount));

            cout << "\nUpdated Account Details:\n";
            acc.showAccount();

            found = true;
        }
    }

    file.close();

    if(!found)
        cout << "\nAccount Not Found.\n";
}

void displayAll()
{
    BankAccount acc;

    ifstream inFile("bank.dat", ios::binary);

    cout << "\n========== ALL ACCOUNTS ==========\n";

    while(inFile.read(reinterpret_cast<char *>(&acc), sizeof(BankAccount)))
    {
        acc.showAccount();
        cout << "-----------------------------\n";
    }

    inFile.close();
}

//---------------------------------------------------------

int main()
{
    int choice;
    int accNo;

    do
    {
        cout << "\n====================================";
        cout << "\n     BANK MANAGEMENT SYSTEM";
        cout << "\n====================================";

        cout << "\n1. Create Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Balance Inquiry";
        cout << "\n5. Display All Accounts";
        cout << "\n6. Exit";

        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                writeAccount();
                break;

            case 2:
                cout << "\nEnter Account Number: ";
                cin >> accNo;
                depositWithdraw(accNo,1);
                break;

            case 3:
                cout << "\nEnter Account Number: ";
                cin >> accNo;
                depositWithdraw(accNo,2);
                break;

            case 4:
                cout << "\nEnter Account Number: ";
                cin >> accNo;
                displayAccount(accNo);
                break;

            case 5:
                displayAll();
                break;

            case 6:
                cout << "\nThank You for Using the Bank Management System.\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 6);

    return 0;
}
