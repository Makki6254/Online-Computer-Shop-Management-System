#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
using namespace std;

// Define the product categories and items
const vector<string> categories = {"Case", "RAM", "Main Hard Disk Drive", "Solid State Drive", "Second Hard Disk Drive", "Optical Drive", "Operating System"};
const map<string, vector<string>> items = {
    {"Case", {"A1", "A2"}},
    {"RAM", {"B1", "B2", "B3"}},
    {"Main Hard Disk Drive", {"C1", "C2", "C3"}},
    {"Solid State Drive", {"D1", "D2"}},
    {"Second Hard Disk Drive", {"E1", "E2", "E3"}},
    {"Optical Drive", {"F1", "F2"}},
    {"Operating System", {"G1", "G2"}}
};

// Define the prices of the items
const map<string, double> prices = {
    {"A1", 75.00},
    {"A2", 150.00},
    {"B1", 79.99},
    {"B2", 149.99},
    {"B3", 299.99},
    {"C1", 49.99},
    {"C2", 89.99},
    {"C3", 129.99},
    {"D1", 59.99},
    {"D2", 119.99},
    {"E1", 49.99},
    {"E2", 89.99},
    {"E3", 129.99},
    {"F1", 50.00},
    {"F2", 100.00},
    {"G1", 100.00},
    {"G2", 175.00}
};

// Define the basic set of components cost
const double basic_cost = 200.00;

// Define a structure to store the customer information
struct Customer {
    string name; // Customer name
    int order_id; // Order ID
    map<string, string> selected_items; // Selected items by category
    double total_price; // Total price of the order
    int additional_items; // Number of additional items
    double discount; // Discount amount
    double amount_saved; // Amount saved with discount
};

// Define a function to generate a random order ID
int generate_order_id() {
    return rand() % 10000 + 1000; // Return a random number between 1000 and 9999
}

// Define a function to display the welcome message
void display_welcome() {
    cout << "Welcome to the Online Computer Shop Management System\n";
    cout << "===================================================\n\n";
}

// Define a function to get the customer name
string get_customer_name() {
    string name;
    cout << "Please enter your name: ";
    getline(cin, name); // Get the whole line of input
    return name;
}

// Define a function to display the product categories and items
void display_products() {
    cout << "The available product categories and items are:\n\n";
    cout << left << setw(20) << "Category" << setw(20) << " Item Code " << setw(40) << "Description" << setw(10) << "Price ($)\n";
    cout << "------------------------------------------------------------------------------------------\n";
    for (auto& category : categories) { // For each category
        for (auto& item : items.at(category)) { // For each item in the category
            cout << left << setw(20) << category << setw(20) <<  item << setw(40) <<  item  << setw(10) << fixed << setprecision(2) << prices.at(item) << "\n";
        }
        cout << "\n";
    }
    cout << "------------------------------------------------------------------------------------------\n\n";
}

// Define a function to get the customer choice for a category
string get_customer_choice(string category) {
    string choice;
    bool valid = false;
    do {
        cout << "Please enter the item code for " << category << ": ";
        cin >> choice; // Get the input
        for (auto& item : items.at(category)) { // For each item in the category
            if (choice == item) { // If the choice matches the item code
                valid = true; // The choice is valid
                break; // Break the loop
            }
        }
        if (!valid) { // If the choice is not valid
            cout << "Invalid item code. Please try again.\n";
        }
    } while (!valid); // Repeat until the choice is valid
    return choice; // Return the choice
}

// Define a function to calculate the price of the order
double calculate_price(map<string, string>& selected_items) {
    double price = basic_cost; // Initialize the price with the basic cost
    for (auto& item : selected_items) { // For each item in the selected items
        price += prices.at(item.second); // Add the price of the item
    }
    return price; // Return the price
}

// Define a function to display the order summary
void display_order_summary(Customer& customer) {
    cout << "\nOrder Summary\n";
    cout << "=============\n\n";
    cout << "Customer Name: " << customer.name << "\n";
    cout << "Order ID: " << customer.order_id << "\n";
    cout << "Selected Items:\n\n";
    cout << left << setw(20) << "Category" << setw(20) << " Item Code " << setw(45) << "Description" << setw(10) << "Price ($)\n";
    cout << "------------------------------------------------------------------------------------------\n";
    for (auto& category : categories) { // For each category
        string item = customer.selected_items[category]; // Get the selected item for the category
        if (item != "") {
            cout << left << setw(20) << category << setw(20) <<  item  << setw(40) <<  item  << setw(10) << fixed << setprecision(2) << prices.at(item) << "\n";
        }
    }
    cout << "------------------------------------------------------------------------------------------\n";
    cout << right << setw(80) << "Basic Cost: " << setw(10) << fixed << setprecision(2) << basic_cost << "$\n";
    cout << right << setw(80) << "Discount: " << setw(10) << fixed << setprecision(2) <<(customer.discount * 100) << "%($" << (customer.amount_saved) << ")\n";
    cout << right << setw(80) << "Total Price: " << setw(10) << fixed << setprecision(2) << customer.total_price << "$\n\n";
}

// Define a function to ask the customer if they want to purchase any additional items
bool purchase_additional_items() {
    char choice;
    bool valid = false;
    do {
        cout << "Do you want to purchase any additional items? (Y/N): ";
        cin >> choice; // Get the input
        choice = toupper(choice); // Convert to uppercase
        if (choice == 'Y' || choice == 'N') { // If the choice is valid
            valid = true; // The choice is valid
        } else { // If the choice is not valid
            cout << "Invalid choice. Please try again.\n";
        }
    } while (!valid); // Repeat until the choice is valid
    return choice == 'Y'; // Return true if the choice is yes, false otherwise
}

// Define a function to display the additional items
void display_additional_items() {
    cout << "The available additional items are:\n\n";
    cout << left << setw(20) << "Category" << setw(20) << "Item Code" << setw(40) << "Description" << setw(10) << "Price ($)\n";
    cout << "------------------------------------------------------------------------------------------\n";
    for (int i = 3; i < categories.size(); i++) { // For each category except the first three
        string category = categories[i];
        for (auto& item : items.at(category)) { // For each item in the category
            cout << left << setw(20) << category << setw(20) << item << setw(40) << item << setw(10) << fixed << setprecision(2) << prices.at(item) << "\n";
        }
        cout << "\n";
    }
    cout << "------------------------------------------------------------------------------------------\n\n";
}

// Define a function to get the customer choice for an additional item
string get_additional_item_choice() {
    string choice;
    bool valid = false;
    do {
        cout << "Please enter the item code for the additional item: ";
        cin >> choice; // Get the input
        for (int i = 3; i < categories.size(); i++) { // For each category except the first three
            string category = categories[i];
            for (auto& item : items.at(category)) { // For each item in the category
                if (choice == item) { // If the choice matches the item code
                    valid = true; // The choice is valid
                    break; // Break the loop
                }
            }
        }
        if (!valid) { // If the choice is not valid
            cout << "Invalid item code. Please try again.\n";
        }
    } while (!valid); // Repeat until the choice is valid
    return choice; // Return the choice
}

// Define a function to update the price and the number of additional items
void update_price_and_items(Customer& customer, string choice) {
    for (int i = 3; i < categories.size(); i++) { // For each category except the first three
        string category = categories[i];
        for (auto& item : items.at(category)) { // For each item in the category
            if (choice == item) { // If the choice matches the item code
                customer.selected_items[category] = item; // Add the item to the selected items
                customer.total_price += prices.at(item); // Add the price of the item to the total price
                customer.additional_items++; // Increment the number of additional items
                break; // Break the loop
            }
        }
    }
}

// Define a function to apply the discount
void apply_discount(Customer& customer) {
    double discount = 0.0; // Initialize the discount
    if (customer.additional_items == 1) { // If the customer has bought only one additional item
        discount = 0.05; // The discount is 5%
    } else if (customer.additional_items >= 2) { // If the customer has bought two or more additional items
        discount = 0.10; // The discount is 10%
    }
    customer.discount = discount; // Set the discount in the customer object
    if (discount > 0.0) { // If there is a discount
        double amount_saved = customer.total_price * discount; // Calculate the amount saved
        customer.amount_saved = amount_saved; // Set the amount saved in the customer object
        customer.total_price -= amount_saved; // Deduct the amount saved from the total price
    }
}

// Define a function to display the farewell message
void display_farewell() {
    cout << "Thank you for shopping with us. Have a nice day!\n";
}

// Define the main function
int main() {
    srand(time(NULL)); // Seed the random number generator
    display_welcome(); // Display the welcome message
    string customer_name = get_customer_name(); // Get the customer name
    Customer customer; // Create a customer object
    customer.name = customer_name; // Set the customer name
    customer.order_id = generate_order_id(); // Set the order ID
    display_products(); // Display the products
    for (int i = 0; i < 3; i++) { // For the first three categories
        string category = categories[i];
        string choice = get_customer_choice(category); // Get the customer choice for the category
        customer.selected_items[category] = choice; // Add the item to the selected items
        customer.total_price += prices.at(choice); // Add the price of the item to the total price
    }
    display_order_summary(customer); // Display the order summary
    if (purchase_additional_items()) { // If the customer wants to purchase additional items
        display_additional_items(); // Display the additional items
        char choice;
        do {
            string item = get_additional_item_choice(); // Get the customer choice for the additional item
            update_price_and_items(customer, item); // Update the price and the number of additional items
            cout << "Do you want to purchase another additional item? (Y/N): ";
            cin >> choice; // Get the input
        } while (choice == 'Y' || choice == 'y'); // Repeat until the choice is not 'Y' or 'y'
        apply_discount(customer); // Apply the discount
        display_order_summary(customer); // Display the order summary with discount info
    }
    display_farewell(); // Display the farewell message
    return 0; // Exit the program
}
