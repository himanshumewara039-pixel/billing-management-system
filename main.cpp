#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

struct Item
{
    string name;
    int quantity;
    double price;
};

class BillingSystem
{
private:
    string customerName;
    string phoneNumber;
    vector<Item> items;
    const double taxRate = 0.05; // 5% tax

    double calculateSubtotal()
    {
        double subtotal = 0;

        for (const Item& item : items)
        {
            subtotal += item.quantity * item.price;
        }

        return subtotal;
    }

    void printBill(ostream& out)
    {
        double subtotal = calculateSubtotal();
        double tax = subtotal * taxRate;
        double total = subtotal + tax;

        out << fixed << setprecision(2);

        out << "\n===============================================================\n";
        out << "                    SMART BILLING SYSTEM\n";
        out << "===============================================================\n";
        out << "Customer Name : " << customerName << '\n';
        out << "Phone Number  : " << phoneNumber << '\n';
        out << "---------------------------------------------------------------\n";

        out << left << setw(25) << "Item"
            << right << setw(10) << "Quantity"
            << setw(12) << "Price"
            << setw(14) << "Amount" << '\n';

        out << "---------------------------------------------------------------\n";

        for (const Item& item : items)
        {
            double amount = item.quantity * item.price;

            out << left << setw(25) << item.name
                << right << setw(10) << item.quantity
                << setw(12) << item.price
                << setw(14) << amount << '\n';
        }

        out << "---------------------------------------------------------------\n";
        out << right << setw(47) << "Subtotal: " << setw(14) << subtotal << '\n';
        out << right << setw(47) << "Tax (5%): " << setw(14) << tax << '\n';
        out << right << setw(47) << "Total: " << setw(14) << total << '\n';
        out << "===============================================================\n";
        out << "                    Thank you for shopping!\n";
        out << "===============================================================\n\n";
    }

    bool saveBill()
    {
        ofstream file("bills.txt", ios::app);

        if (!file)
        {
            cout << "Error: Could not open bills.txt. The bill was not saved.\n";
            return false;
        }

        printBill(file);
        return true;
    }

    void enterBillDetails()
    {
        cout << "\nEnter customer name: ";
        getline(cin >> ws, customerName);

        cout << "Enter phone number: ";
        getline(cin, phoneNumber);

        int itemCount;
        cout << "How many different items are being purchased? ";
        cin >> itemCount;

        while (itemCount <= 0)
        {
            cout << "Please enter a number greater than 0: ";
            cin >> itemCount;
        }

        items.clear();

        for (int i = 0; i < itemCount; i++)
        {
            Item item;

            cout << "\nItem " << i + 1 << " name: ";
            getline(cin >> ws, item.name);

            cout << "Quantity: ";
            cin >> item.quantity;

            while (item.quantity <= 0)
            {
                cout << "Please enter a quantity greater than 0: ";
                cin >> item.quantity;
            }

            cout << "Price per item: ";
            cin >> item.price;

            while (item.price < 0)
            {
                cout << "Price cannot be negative. Enter the price again: ";
                cin >> item.price;
            }

            items.push_back(item);
        }
    }

public:
    void createBill()
    {
        while (true)
        {
            enterBillDetails();

            cout << "\n---------------- BILL PREVIEW ----------------\n";
            printBill(cout);

            int choice;
            cout << "1. Yes, confirm and save the bill\n";
            cout << "2. No, edit the bill details\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1)
            {
                if (saveBill())
                {
                    cout << "\nBill confirmed and saved to bills.txt.\n";
                }

                break;
            }
            else if (choice == 2)
            {
                cout << "\nPlease enter the bill details again.\n";
            }
            else
            {
                cout << "\nInvalid choice. Please review the bill again.\n";
            }
        }
    }

    void menu()
    {
        int choice;

        while (true)
        {
            cout << "\n========== SMART BILLING SYSTEM ==========\n";
            cout << "1. Create a new bill\n";
            cout << "2. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1)
            {
                createBill();
            }
            else if (choice == 2)
            {
                cout << "\nThank you for using the Smart Billing System.\n";
                break;
            }
            else
            {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }
};

int main()
{
    BillingSystem billingSystem;
    billingSystem.menu();

    return 0;
}