#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUCTS 100
#define MAX_CUSTOMERS 50
#define MAX_EMPLOYEES 20

// Structures
struct Product {
    int id;
    char name[50];
    float price;
    int quantity;
};

struct Customer {
    char name[50];
    int id;
    float totalSpent;
};

struct Employee {
    char name[50];
    int id;
    float salary;
};

// Globals
struct Product products[MAX_PRODUCTS];
struct Employee employees[MAX_EMPLOYEES] = {
    {"Mehedi", 1, 15000},
    {"Sajid", 2, 18000},
    {"Tanvir", 3, 17000},
    {"Mamun", 4, 16000},
    {"Rabbi", 5, 15500}
};
int productCount = 0;
float totalSales = 0, totalPurchases = 0;

// Prototypes
void initializeProducts();
void displayProducts();
void addProduct();
void manageCustomers();
void manageEmployees();
void salesManagement();
void purchaseManagement();
void paymentManagement(float bill);
void profitLossManagement();
void onlineSalesManagement();
void userPanel();

int main() {
    int role;

    printf("\n========= DHAKKU BAKKU SUPERSHOP =========\n");
    printf("Select Role:\n1. Admin\n2. User\nChoice: ");
    scanf("%d", &role);

    initializeProducts();

    if (role == 1) {
        int choice;
        while (1) {
            printf("\n\n===== ADMIN PANEL =====\n");
            printf("1. Manage Customers\n");
            printf("2. Display Products\n");
            printf("3. Manage Employees\n");
            printf("4. Sales Info\n");
            printf("5. Purchase Info\n");
            printf("6. Payment Info\n");
            printf("7. Profit/Loss Report\n");
            printf("8. Add Product\n");
            printf("9. Online Sales\n");
            printf("0. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1: manageCustomers(); break;
                case 2: displayProducts(); break;
                case 3: manageEmployees(); break;
                case 4: salesManagement(); break;
                case 5: purchaseManagement(); break;
                case 6: paymentManagement(0); break;
                case 7: profitLossManagement(); break;
                case 8: addProduct(); break;
                case 9: onlineSalesManagement(); break;
                case 0: printf("Exiting...\n"); return 0;
                default: printf("Invalid choice!\n");
            }
        }
    } else if (role == 2) {
        userPanel();
    } else {
        printf("Invalid role selected.\n");
    }

    return 0;
}

void initializeProducts() {
    const char *names[50] = {
        "Rice", "Sugar", "Salt", "Milk", "Tea", "Coffee", "Bread", "Butter", "Cheese", "Eggs",
        "Chicken", "Beef", "Fish", "Onion", "Garlic", "Potato", "Tomato", "Carrot", "Cucumber", "Apple",
        "Banana", "Orange", "Grapes", "Mango", "Pineapple", "Watermelon", "Coconut", "Flour", "Lentils", "Beans",
        "Soap", "Shampoo", "Toothpaste", "Toothbrush", "Oil", "Vinegar", "Ketchup", "Jam", "Honey", "Biscuits",
        "Chocolate", "Ice Cream", "Noodles", "Pasta", "Detergent", "Bleach", "Tissue", "Paper Towel", "Handwash", "Sanitizer"
    };
    float prices[50] = {
        60, 80, 30, 70, 150, 200, 40, 120, 300, 100,
        220, 450, 320, 50, 100, 25, 30, 35, 40, 120,
        60, 80, 250, 90, 100, 300, 150, 45, 100, 70,
        20, 90, 75, 35, 160, 85, 110, 180, 250, 50,
        100, 200, 55, 60, 130, 140, 30, 70, 90, 150
    };

    for (int i = 0; i < 50; i++) {
        products[i].id = i + 1;
        strncpy(products[i].name, names[i], sizeof(products[i].name));
        products[i].price = prices[i];
        products[i].quantity = 100;
    }
    productCount = 50;
    printf("Initialized with 50 pre-stocked products.\n");
}

void displayProducts() {
    printf("\n%-5s %-20s %-10s %-10s\n", "ID", "Product Name", "Price", "Stock");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < productCount; i++) {
        printf("%-5d %-20s %-10.2f %-10d\n", products[i].id, products[i].name, products[i].price, products[i].quantity);
    }
}

void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("Cannot add more products.\n");
        return;
    }
    printf("\nEnter product name: ");
    scanf("%s", products[productCount].name);
    printf("Enter price: ");
    scanf("%f", &products[productCount].price);
    printf("Enter quantity: ");
    scanf("%d", &products[productCount].quantity);
    products[productCount].id = productCount + 1;
    productCount++;
    printf("Product added successfully!\n");
}

void manageCustomers() {
    char name[50];
    int productID, quantity;
    float total = 0;
    displayProducts();
    printf("\nEnter your name: ");
    scanf("%s", name);

    while (1) {
        printf("Enter product ID to buy (0 to finish): ");
        scanf("%d", &productID);
        if (productID == 0) break;
        if (productID > 0 && productID <= productCount) {
            printf("Enter quantity: ");
            scanf("%d", &quantity);
            if (quantity <= products[productID - 1].quantity) {
                float price = quantity * products[productID - 1].price;
                total += price;
                products[productID - 1].quantity -= quantity;
                printf("Added to cart: %s x%d = %.2f\n", products[productID - 1].name, quantity, price);
            } else {
                printf("Insufficient stock.\n");
            }
        } else {
            printf("Invalid product ID.\n");
        }
    }
    printf("\nTotal bill for %s: %.2f\n", name, total);
    totalSales += total;
    paymentManagement(total);
    printf("\nTHANK YOU Dear Customer\n");
}

void manageEmployees() {
    printf("\n%-5s %-20s %-10s\n", "ID", "Employee Name", "Salary");
    printf("--------------------------------------------\n");
    for (int i = 0; i < 5; i++) {
        printf("%-5d %-20s %-10.2f\n", employees[i].id, employees[i].name, employees[i].salary);
    }
}

void salesManagement() {
    printf("\nTotal Sales Today: %.2f\n", totalSales);
}

void purchaseManagement() {
    float amount;
    printf("\nEnter total purchase amount (stock purchase): ");
    scanf("%f", &amount);
    totalPurchases += amount;
    printf("Recorded purchase amount: %.2f\n", amount);
}

void paymentManagement(float bill) {
    float amount;
    if (bill == 0) {
        printf("\nEnter amount received from customer: ");
        scanf("%f", &amount);
        printf("Payment of %.2f received successfully.\n", amount);
    } else {
        printf("\nCustomer needs to pay %.2f. Enter payment: ", bill);
        scanf("%f", &amount);
        if (amount < bill) {
            printf("\nInsufficient payment. %.2f more required.\n", bill - amount);
        } else {
            printf("\nPayment successful. Change returned: %.2f\n", amount - bill);
        }
    }
}

void profitLossManagement() {
    float profit = totalSales - totalPurchases;
    printf("\nTotal Sales: %.2f\n", totalSales);
    printf("Total Purchase Cost: %.2f\n", totalPurchases);
    if (profit >= 0) {
        printf("Net Profit: %.2f\n", profit);
    } else {
        printf("Net Loss: %.2f\n", -profit);
    }
}

void onlineSalesManagement() {
    char name[50];
    int productID, quantity;
    float total = 0;
    printf("\n--- Online Sales System ---\n");
    displayProducts();
    printf("\nEnter Customer Name: ");
    scanf("%s", name);

    while (1) {
        printf("Enter product ID to order online (0 to finish): ");
        scanf("%d", &productID);
        if (productID == 0) break;
        if (productID > 0 && productID <= productCount) {
            printf("Enter quantity: ");
            scanf("%d", &quantity);
            if (quantity <= products[productID - 1].quantity) {
                float price = quantity * products[productID - 1].price;
                total += price;
                products[productID - 1].quantity -= quantity;
                printf("Ordered Online: %s x%d = %.2f\n", products[productID - 1].name, quantity, price);
            } else {
                printf("Out of stock for online order.\n");
            }
        } else {
            printf("Invalid product ID.\n");
        }
    }
    printf("\nOnline Bill for %s: %.2f\n", name, total);
    totalSales += total;
    paymentManagement(total);
    printf("\nTHANK YOU Dear Customer\n");
}

void userPanel() {
    char name[50];
    int productID, quantity;
    float total = 0;
    printf("\n=== USER PANEL ===\n");
    displayProducts();
    printf("\nEnter your name: ");
    scanf("%s", name);

    while (1) {
        printf("Enter product ID to buy (0 to finish): ");
        scanf("%d", &productID);
        if (productID == 0) break;
        if (productID > 0 && productID <= productCount) {
            printf("Enter quantity: ");
            scanf("%d", &quantity);
            if (quantity <= products[productID - 1].quantity) {
                float price = quantity * products[productID - 1].price;
                total += price;
                products[productID - 1].quantity -= quantity;
                printf("Added to cart: %s x%d = %.2f\n", products[productID - 1].name, quantity, price);
            } else {
                printf("Insufficient stock.\n");
            }
        } else {
            printf("Invalid product ID.\n");
        }
    }
    printf("\nTotal bill for %s: %.2f\n", name, total);
    totalSales += total;
    paymentManagement(total);
    printf("\nTHANK YOU Dear Customer\n");
}
