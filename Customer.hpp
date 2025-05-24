#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "Topping.hpp"
#include "Order.hpp"

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::cout;

class Customer {
private:
    static int nextID;
    int customerID;
    std::string name;
    std::string debutType;
    std::string debutCondition;
    std::unique_ptr<Order> order;
    std::vector<std::string> flavorOptions = {"Vanilla", "Chocolate", "Strawberry"};
    std::vector<std::string> sizeOptions = {"Small", "Medium", "Large"};
    ToppingList toppingList;

    std::string getRandom(const std::vector<std::string>& options) {
        return options[rand() % options.size()];
    }

public:
    Customer(std::string name, std::string debutType, std::string debutCondition)
        : name(std::move(name)), debutType(std::move(debutType)), debutCondition(std::move(debutCondition)) {
        customerID = nextID++;
    }

    int getID() const { return customerID; }
    const std::string& getName() const { return name; }
    const std::string& getDebutType() const { return debutType; }
    const std::string& getDebutCondition() const { return debutCondition; }
    const Order& getOrder() const { return *order; }

    void generateOrder() {
        std::string flavor = getRandom(flavorOptions);
        std::string size = getRandom(sizeOptions);
        auto topping = toppingList.getRandomTopping();
        order = std::make_unique<Order>(flavor, std::move(topping), size);
    }
};
