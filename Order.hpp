#pragma once 

#include <string> 
#include <vector> 
#include <iostream>  
using namespace std; 

#include "Ingredients.hpp"
#include "Toppings.hpp"

class Order {
private:
    vector<string> flavorOptions = {"Vanilla", "Chocolate", "Strawberry"};
    vector<string> sizeOptions = {"Small", "Medium", "Large"};

    string flavor;
    string size;
    unique_ptr<Topping> topping;

public:
    Order(string f, unique_ptr<Topping> t, string s)
        : flavor(f), topping(std::move(t)), size(s) {}

    void show() const {
        cout << " - Flavor: " << flavor << "\n";
        cout << " - Topping: " << topping->getName() << " (" << topping->getType() << ")\n";
        cout << " - Size: " << size << "\n";
    }

    string getFlavor() const { return flavor; }
    string getSize() const { return size; }
    string getToppingName() const { return topping->getName(); }
    string getToppingType() const { return topping->getType(); }
};

class Sundae {
private:
    ToppingList toppingList;

public:
    string flavor;
    string size;
    unique_ptr<Topping> topping;

    void build() {
        cout << "\nBuild the sundae!\n";

        cout << "Choose flavor (Vanilla, Chocolate, Strawberry): ";
        getline(cin, flavor);

        cout << "Choose topping (randomly assigned for now): \n";
        topping = toppingList.getRandomTopping();  // Could be player-picked later
        cout << "  → You got: " << topping->getName() << " (" << topping->getType() << ")\n";

        cout << "Choose size (Small, Medium, Large): ";
        getline(cin, size);
    }

    string getFlavor() const { return flavor; }
    string getSize() const { return size; }
    string getToppingName() const { return topping->getName(); }
    string getToppingType() const { return topping->getType(); }
};
