#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>

class BankAccount
{
private:
    float balance;
public:
    BankAccount() : balance(0) {}
    
    explicit BankAccount(const BankAccount& other) : balance(other.balance)
    {
        if (balance >= 0){
            balance = other.balance;
        }
    }
    BankAccount(BankAccount&& other) noexcept : balance(other.balance){
        other.balance = 0;
    }

    int get_balance() const
    {
        return balance;
    }
    
    void setBalance(float NewBalance){
        if (NewBalance > 0)
        {
            balance += NewBalance;

        }
    }
    
    void withdraw(float NewBalance){
        if (NewBalance <= balance){
            balance -= NewBalance;
        }
    }    
};

class Customer{
    
private:
    char name[20];
    char surname[20];
    BankAccount account;
    
public:
    Customer() : name("Unknown"), surname("Unknown"){}

    Customer(const char* NewName, const char* NewSurname, BankAccount NewAccount) : account(NewAccount)
    {
        strcpy(name, NewName );
        strcpy(surname, NewSurname);
        
    }
    
    Customer(const Customer& other) : account(other.account)
    {
        strcpy(name, other.name);
        strcpy(surname, other.surname);

    }
    
    explicit Customer(const char* NewName, BankAccount NewAccount) : account(NewAccount)
    {
        strcpy(name, NewName);
        strcpy(surname, "Unknown");
    }

    void RecordToFile(int operation ,float NewBalance)
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        FILE *file = fopen("Operation.txt", "a");

        fprintf(file, "Balance: %d\n", account.get_balance());
        fprintf(file, "Date: %02d-%02d-%d %02d:%02d\n", ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900, ltm->tm_hour, ltm->tm_min);
        switch (operation)
        {
        case 1:
            fprintf(file, "Type: Transfer\n" );
        case 2:
            fprintf(file, "Type: SetBalance\n");
        case 3:
            fprintf(file, "Type: withdraw\n");
        }
        fprintf(file, "Transfer sum: %f\n", NewBalance);
        fprintf(file, "\n");
        fclose(file);
    }

    void SetBalance(float NewBalance)
    {
        account.setBalance(NewBalance);
        RecordToFile(2, NewBalance);
        
    }
    void withdraw(float NewBalance)
    {
        account.withdraw(NewBalance);
        RecordToFile(3, NewBalance);
    }
    
    
    void DisplayBalance()
    {
        std::cout << "Balance: " << account.get_balance() << '\n';
    }
    void DisplayInfo()
    {
        std::cout << "Name: " << name << '\n';
        std::cout << "Surname: " << surname << '\n';
    }
    void SetName(const char* NewName)
    {
        strcpy(name, NewName);
    }
    void SetSurname(const char* NewSurname)
    {
        strcpy(surname, NewSurname);
    }
    void transfer(Customer& other, float NewBalance)
    {
        withdraw(NewBalance);
        other.SetBalance(NewBalance);
        RecordToFile(1, NewBalance);
        
    }
    
    
        
};

void DisplayBalance(const BankAccount& other)
{
    std::cout << other.get_balance() << std::endl;
}

int main(){

    Customer customer1, customer2;
    customer1.SetBalance(50);
    customer1.transfer(customer2, 50);
    customer1.DisplayBalance();
    customer2.DisplayBalance();
    
    
    return 0;
}