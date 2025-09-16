
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUCTS 100
#define MAX_CUSTOMERS 50
#define MAX_EMPLOYEES 20
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"
#define USER_USERNAME "user"
#define USER_PASSWORD "user123"

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

// Global variables
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

// Function declarations
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
int login();

int main() {
    int role = login();
    if (role == 0) return 0;

    int choice;
    initializeProducts();

    while (1) {
        if (role == 1) {
            printf("\n\n============= ADMIN DASHBOARD =============\n");
            printf("1. Customer Information\n");
            printf("2. Product Information\n");
            printf("3. Employee Information\n");
            printf("4. Sales (On-Shop) Information\n");
            printf("5. Purchase Information\n");
            printf("6. Payment Information\n");
            printf("7. Profit/Loss Information\n");
            printf("8. Add Product\n");
            printf("9. Online Sales Information\n");
            printf("0. Logout\n");
        } else if (role == 2) {
            printf("\n\n============= CUSTOMER DASHBOARD =============\n");
            printf("1. View Products\n");
            printf("2. Buy Products (Payment Info)\n");
            printf("0. Logout\n");
        }

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (role == 1) {
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
                case 0: printf("Logging out...\n"); return 0;
                default: printf("Invalid choice!\n");
            }
        } else if (role == 2) {
            switch (choice) {
                case 1: displayProducts(); break;
                case 2: manageCustomers(); break;
                case 0: printf("Logging out...\n"); return 0;
                default: printf("Invalid choice!\n");
            }
        }
    }
}

int login() {
    char username[50], password[50];
    printf("====== Login ======\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        printf("Login successful! Welcome Admin.\n");
        return 1;
    } else if (strcmp(username, USER_USERNAME) == 0 && strcmp(password, USER_PASSWORD) == 0) {
        printf("Login successful! Welcome User.\n");
        return 2;
    } else {
        printf("Invalid credentials!\n");
        return 0;
    }
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
        printf("\nEnter payment for bill %.2f: ", bill);
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
