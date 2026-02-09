#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Expense {
public:
    string date, category, note;
    float amount;

    void input() {
        cout << "Enter Date (DD/MM/YYYY): ";
        cin >> date;
        cout << "Enter Category (Food, Travel, etc.): ";
        cin >> category;
        cout << "Enter Amount: ";
        cin >> amount;
        cout << "Enter Note: ";
        cin.ignore();
        getline(cin, note);
    }

    void display() const {
        cout << left << setw(12) << date
             << setw(15) << category
             << setw(10) << amount
             << note << endl;
    }
};

void addExpense() {
    Expense e;
    ofstream fout("expenses.txt", ios::app);

    if (!fout) {
        cout << "Error opening file!\n";
        return;
    }

    e.input();
    fout << e.date << " " << e.category << " " << e.amount << " " << e.note << endl;

    fout.close();
    cout << "\nExpense Added Successfully!\n";
}

void viewExpenses() {
    Expense e;
    ifstream fin("expenses.txt");

    if (!fin) {
        cout << "No expense records found!\n";
        return;
    }

    cout << "\nDate        Category       Amount    Note\n";
    cout << "-----------------------------------------------\n";

    while (fin >> e.date >> e.category >> e.amount) {
        fin.ignore();
        getline(fin, e.note);
        e.display();
    }

    fin.close();
}

void showTotal() {
    ifstream fin("expenses.txt");
    float total = 0, amt;

    if (!fin) {
        cout << "No expense records found!\n";
        return;
    }

    string date, category, note;

    while (fin >> date >> category >> amt) {
        fin.ignore();
        getline(fin, note);
        total += amt;
    }

    fin.close();
    cout << "\nTotal Expense = ₹" << total << endl;
}

int main() {
    int choice;

    do {
        cout << "\n====== Expense Tracker ======\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Show Total\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addExpense(); break;
        case 2: viewExpenses(); break;
        case 3: showTotal(); break;
        case 4: cout << "Exiting Program...\n"; break;
        default: cout << "Invalid Choice!\n";
        }

    } while (choice != 4);

    return 0;
}
