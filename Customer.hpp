#pragma once 
#include <string> 
#include <iostream> 
#include <vector> 
#include <memory>


#include "Topping.hpp"
#include "Order.hpp"

class Customer {
private:
    string name;
    int id;
    unique_ptr<Order> order;
    vector<string> flavorOptions = {"Vanilla", "Chocolate", "Strawberry"};
    vector<string> sizeOptions = {"Small", "Medium", "Large"};
    ToppingList toppingList;

private:
    string getRandom(const vector<string>& options) {
        return options[rand() % options.size()];
    }

public:
    Customer(string n, int i) : name(n), id(i) {
        string flavor = getRandom(flavorOptions);
        string size = getRandom(sizeOptions);
        auto topping = toppingList.getRandomTopping();

        order = make_unique<Order>(flavor, std::move(topping), size);
    }

    void showOrder() const {
        cout << "\nCustomer #" << id << " - " << name << "'s Order:\n";
        order->show();
    }

    string getFlavor() const { return order->getFlavor(); }
    // string getTopping() const { return order->getToppingName()const; }// this doesnt work as it expects string not pointer
    string getSize() const { return order->getSize(); }
    string getToppingName() const {return order->getToppingName();}


};
