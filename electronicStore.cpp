#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Base class representing a product
class Product {
protected:
    string name;
    double price;

public:
    // Constructor
    Product(const string& name, double price) : name(name), price(price) {}

    // Pure virtual function to calculate the discount
    virtual double calculateDiscount() const = 0;

    // Virtual function to display product information
    virtual void display() const {
        cout << "Name: " << name << endl;
        cout << "Price: $" << price << endl;
    }

    // Overloading << operator to write product information to a file
    friend ofstream& operator<<(ofstream& ofs, const Product& product) {
        ofs << "Name: " << product.name << endl;
        ofs << "Price: $" << product.price << endl;
        return ofs;
    }
};

// Derived class representing a laptop
class Laptop : public Product {
private:
    string brand;

public:
    // Constructor
    Laptop(const string& name, double price, const string& brand)
        : Product(name, price), brand(brand) {}

    // Override calculateDiscount() to provide specific discount calculation for laptops
    double calculateDiscount() const override {
        return price * 0.1;
    }

    // Override display() to include brand information
    void display() const override {
        Product::display();
        cout << "Brand: " << brand << endl;
    }

    // Overloading << operator to write laptop information to a file
    friend ofstream& operator<<(ofstream& ofs, const Laptop& laptop) {
        ofs << static_cast<const Product&>(laptop);
        ofs << "Brand: " << laptop.brand << endl;
        return ofs;
    }
};

// Derived class representing a mobile
class Mobile : public Product {
private:
    string manufacturer;

public:
    // Constructor
    Mobile(const string& name, double price, const string& manufacturer)
        : Product(name, price), manufacturer(manufacturer) {}

    // Override calculateDiscount() to provide specific discount calculation for mobiles
    double calculateDiscount() const override {
        return price * 0.05;
    }

    // Override display() to include manufacturer information
    void display() const override {
        Product::display();
        cout << "Manufacturer: " << manufacturer << endl;
    }

    // Overloading << operator to write mobile information to a file
    friend ofstream& operator<<(ofstream& ofs, const Mobile& mobile) {
        ofs << static_cast<const Product&>(mobile);
        ofs << "Manufacturer: " << mobile.manufacturer << endl;
        return ofs;
    }
};

// Class representing a shopping cart
class Cart {
private:
    vector<Product*> products;

public:
    // Add a product to the cart
    void addProduct(Product* product) {
        products.push_back(product);
    }

    // Display the contents of the cart
    void displayCart() const {
        for (const Product* product : products) {
            product->display();
            cout << "Discounted Price: $" << product->calculateDiscount() << endl;
            cout << endl;
        }
    }

    // Overloading << operator to write cart contents to a file
    friend ofstream& operator<<(ofstream& ofs, const Cart& cart) {
        for (const Product* product : cart.products) {
            ofs << *product;
            ofs << "Discounted Price: $" << product->calculateDiscount() << endl;
            ofs << endl;
        }
        return ofs;
    }
};

// Base class representing a customer
class Customer {
protected:
    string name;

public:
    // Constructor
    Customer(const string& name) : name(name) {}

    // Virtual function to display customer information
    virtual void display() const {
        cout << "Name: " << name << endl;
    }

    // Pure virtual function representing the purchase behavior
    virtual void purchase(Cart& cart) const = 0;
};

// Derived class representing a regular customer
class RegularCustomer : public Customer {
private:
    string address;

public:
    // Constructor
    RegularCustomer(const string& name, const string& address)
        : Customer(name), address(address) {}

    // Override display() to include address information
    void display() const override {
        Customer::display();
        cout << "Address: " << address << endl;
    }

    // Override purchase() to display purchased products
    void purchase(Cart& cart) const override {
        cout << "Regular Customer: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Purchased Products:" << endl;
        cart.displayCart();
    }
};

// Derived class representing a corporate customer
class CorporateCustomer : public Customer {
private:
    string companyName;

public:
    // Constructor
    CorporateCustomer(const string& name, const string& companyName)
        : Customer(name), companyName(companyName) {}

    // Override display() to include company name information
    void display() const override {
        Customer::display();
        cout << "Company Name: " << companyName << endl;
    }

    // Override purchase() to display purchased products
    void purchase(Cart& cart) const override {
        cout << "Corporate Customer: " << name << endl;
        cout << "Company Name: " << companyName << endl;
        cout << "Purchased Products:" << endl;
        cart.displayCart();
    }
};

int main() 
{
    // Creating products
    string laptopName, laptopBrand, mobileName, mobileManufacturer;
    double laptopPrice, mobilePrice;

    cout << "Enter laptop name: ";
    getline(cin, laptopName);

    cout << "Enter laptop price: ";
    cin >> laptopPrice;
    cin.ignore(); // Ignore the newline character left in the input buffer

    cout << "Enter laptop brand: ";
    getline(cin, laptopBrand);

    cout << "Enter mobile name: ";
    getline(cin, mobileName);

    cout << "Enter mobile price: ";
    cin >> mobilePrice;
    cin.ignore(); // Ignore the newline character left in the input buffer

    cout << "Enter mobile manufacturer: ";
    getline(cin, mobileManufacturer);

    Laptop laptop(laptopName, laptopPrice, laptopBrand);
    Mobile mobile(mobileName, mobilePrice, mobileManufacturer);

    // Creating cart
    Cart cart;
    cart.addProduct(&laptop);
    cart.addProduct(&mobile);

    // Creating customers
    string regularCustomerName, regularCustomerAddress;
    string corporateCustomerName, corporateCustomerCompanyName;

    cout << "Enter regular customer name: ";
    getline(cin, regularCustomerName);

    cout << "Enter regular customer address: ";
    getline(cin, regularCustomerAddress);

    cout << "Enter corporate customer name: ";
    getline(cin, corporateCustomerName);

    cout << "Enter corporate customer company name: ";
    getline(cin, corporateCustomerCompanyName);

    RegularCustomer regularCustomer(regularCustomerName, regularCustomerAddress);
    CorporateCustomer corporateCustomer(corporateCustomerName, corporateCustomerCompanyName);

    // Purchasing products
    regularCustomer.purchase(cart);
    cout << endl;
    corporateCustomer.purchase(cart);

    // Writing cart contents to a file
    ofstream outFile("cart.txt");
    if (outFile.is_open()) {
        outFile << cart;
        outFile.close();
        cout <<"Cart data stored into cart.txt"<< endl;
    } else {
        cout <<"Failed to open file for writing"<< endl;
    }

    return 0;
}

