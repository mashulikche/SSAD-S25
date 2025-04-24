#include <iostream>
#include <vector>
#include <string>

using namespace std;

class IStoreVisitor;

class IStoreItem {
public:
    virtual double accept(IStoreVisitor* visitor) = 0;
    virtual ~IStoreItem() {}
};

class Book;
class Coffee;
class Tea;

class IStoreVisitor {
public:
    virtual double visit(Book &book) = 0;
    virtual double visit(Tea &tea) = 0;
    virtual double visit(Coffee &coffee) = 0;
    virtual ~IStoreVisitor() {}
};

class Book : public IStoreItem {
private:
    string isbn;
    double price;
    double tax;
public:
    Book(const string& isbn, double price, double tax)
            : isbn(isbn), price(price), tax(tax) {}

    const string& getIsbn() const { return isbn; }
    double getPrice() const { return price; }
    double getTax() const { return tax; }

    double accept(IStoreVisitor* visitor) override {
        return visitor->visit(*this);
    }
};

class Coffee : public IStoreItem {
private:
    string brand;
    double price;
    double tax;
    bool discount;
public:
    Coffee(const string& brand, double price, double tax, bool discount)
            : brand(brand), price(price), tax(tax), discount(discount) {}

    const string& getBrand() const { return brand; }
    double getPrice() const { return price; }
    double getTax() const { return tax; }
    bool isDiscount() const { return discount; }

    // Accept method calls the visitor's visit method for a Coffee.
    double accept(IStoreVisitor* visitor) override {
        return visitor->visit(*this);
    }
};

class Tea : public IStoreItem {
private:
    string brand;
    double price;
    double tax;
    bool discount;
public:
    Tea(const string& brand, double price, double tax, bool discount)
            : brand(brand), price(price), tax(tax), discount(discount) {}

    const string& getBrand() const {
        return brand;
    }


    bool isDiscount() const {
        return discount;
    }

    double getTax() const {
        return tax;
    }

    double getPrice() const {
        return price;
    }

    double accept(IStoreVisitor* visitor) override {
        return visitor->visit(*this);
    }
};

class StoreVisitor : public IStoreVisitor {
public:

    double visit(Book &book) override {
        return book.getPrice() + book.getTax() * book.getPrice();
    }

    double visit(Tea &tea) override {
        double cost = tea.getPrice() + tea.getTax() * tea.getPrice();
        if (tea.isDiscount()) {
            cost -= cost * 0.1;
        }
        return cost;
    }

    double visit(Coffee &coffee) override {
        double cost = coffee.getPrice() + coffee.getTax() * coffee.getPrice();
        if (coffee.isDiscount()) {
            cost -= cost * 0.15;
        }
        return cost;
    }
};

int main() {
    vector<IStoreItem*> items;
    items.push_back(new Book("10", 2000.01, 0.05));
    items.push_back(new Book("13", 350, 0.13));
    items.push_back(new Coffee("Latte", 500, 0.090, false));
    items.push_back(new Coffee("SimpleCoffee", 500, 0.087, true));
    items.push_back(new Tea("Lipton", 70, 0.003, true));
    items.push_back(new Tea("Tess", 70, 0.003, true));

    StoreVisitor visitor;
    double totalCost = 0;

    for (auto item : items) {
        totalCost += item->accept(&visitor);
    }

    cout  << totalCost << endl;

    for (auto item : items) {
        delete item;
    }

    return 0;
}