
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Product {
    string name;
    double costPrice;
    double sellingPrice;
    int quantityBought;
    int quantitySold;

    double totalCost() const {
        return costPrice * quantityBought;
    }

    double totalRevenue() const {
        return sellingPrice * quantitySold;
    }

    double profit() const {
        return totalRevenue() - totalCost();
    }

    int stockLeft() const {
        return quantityBought - quantitySold;
    }
};

class CashRegister {
private:
    vector<Product> inventory;

public:
    void buyProduct() {
        string name;
        double cost, price;
        int quantity;

        cout << "Enter product name: ";
        cin >> name;

        cout << "Enter cost price: $";
        cin >> cost;

        cout << "Enter selling price: $";
        cin >> price;

        cout << "Enter quantity: ";
        cin >> quantity;

        Product p = { name, cost, price, quantity, 0 };
        inventory.push_back(p);
        cout << "Product '" << name << "' bought and added to inventory.
";
    }

    void sellProduct() {
        string name;
        int quantity;

        cout << "Enter product name to sell: ";
        cin >> name;

        cout << "Enter quantity to sell: ";
        cin >> quantity;

        for (auto& p : inventory) {
            if (p.name == name) {
                if (p.stockLeft() >= quantity) {
                    p.quantitySold += quantity;
                    double total = p.sellingPrice * quantity;
                    cout << "Sold " << quantity << " of " << name << " for $" << fixed << setprecision(2) << total << endl;
                } else {
                    cout << "Not enough stock. Available: " << p.stockLeft() << endl;
                }
                return;
            }
        }
        cout << "Product not found.
";
    }

    void showReport() const {
        double totalRevenue = 0.0;
        double totalCost = 0.0;
        double totalProfit = 0.0;

        cout << "\n--- Sales Report ---\n";
        cout << left << setw(15) << "Product"
             << setw(10) << "Bought"
             << setw(10) << "Sold"
             << setw(10) << "Left"
             << setw(12) << "Revenue"
             << setw(10) << "Profit" << endl;

        for (const auto& p : inventory) {
            totalRevenue += p.totalRevenue();
            totalCost += p.totalCost();
            totalProfit += p.profit();

            cout << left << setw(15) << p.name
                 << setw(10) << p.quantityBought
                 << setw(10) << p.quantitySold
                 << setw(10) << p.stockLeft()
                 << "$" << setw(10) << fixed << setprecision(2) << p.totalRevenue()
                 << "$" << fixed << setprecision(2) << p.profit() << endl;
        }

        cout << "\nTotal Revenue: $" << totalRevenue;
        cout << "\nTotal Cost:    $" << totalCost;
        cout << "\nTotal Profit:  $" << totalProfit << endl;
    }

    void menu() {
        int choice;
        while (true) {
            cout << "\n--- Cash Register Menu ---\n";
            cout << "1. Buy Product\n";
            cout << "2. Sell Product\n";
            cout << "3. View Sales Report\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: 
                    buyProduct();
                    break;
                case 2: 
                    sellProduct();
                    break;
                case 3: 
                    showReport();
                    break;
                case 4: 
                    cout << "Exiting program.\n";
                    return;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
    }
};

int main() {
    CashRegister reg;
    reg.menu();
    return 0;
}
