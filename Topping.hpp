#pragma once

#include <memory>
#include <vector>
#include <functional>
#include <cstdlib> 
#include <string> 
using namespace std; 

#include "Ingredients.hpp"
//topping class
class Topping : public Ingredient {
protected: 
int unlockLevel; 

public:
    Topping(int level) : unlockLevel(level) {}
    // virtual string getType() const = 0;  //in ingredients class

    string getCategory() const override { return "Topping"; }
    int getUnlockLevel() const { return unlockLevel; }
    virtual ~Topping() {}
};

//different toppings subclass 
class FruitTopping : public Topping {
private:
    string name;

public:
    FruitTopping(string n, int level) : Topping(level), name(n) {}
    string getName() const override { return name; }
    string getType() const override{ return "Fruit topping"; }
};

class SweetTopping : public Topping {
private:
    string name;

public:
    SweetTopping(string n, int level) : Topping(level), name(n) {}
    string getName() const override  { return name; }
    string getType() const override  { return "Sweet topping"; }
};

class ToppingList {
private:
    vector<function<unique_ptr<FruitTopping>()>> fruitOptions;
    vector<function<unique_ptr<SweetTopping>()>> sweetOptions;

public:
    ToppingList() {
        fruitOptions.push_back([]() { return make_unique<FruitTopping>("Banana",1); });
        fruitOptions.push_back([]() { return make_unique<FruitTopping>("Cherry",2); });

        sweetOptions.push_back([]() { return make_unique<SweetTopping>("SourPatches",5);}); 
        sweetOptions.push_back([]() { return make_unique<SweetTopping>("Sprinkles",2); });
        sweetOptions.push_back([]() { return make_unique<SweetTopping>("Oreos",1); });
    }

    unique_ptr<Topping> getRandomFruitTopping() const {
        int index = rand() % fruitOptions.size();
        return fruitOptions[index]();
    }

    unique_ptr<Topping> getRandomSweetTopping() const {
        int index = rand() % sweetOptions.size();
        return sweetOptions[index]();
    }

    unique_ptr<Topping> getRandomTopping() const {
        vector<function<unique_ptr<Topping>()>> all;

        for (const auto& f : fruitOptions)
            all.push_back([=]() { return f(); });

        for (const auto& s : sweetOptions)
            all.push_back([=]() { return s(); });

        int index = rand() % all.size();
        return all[index]();
    }
    unique_ptr<Topping> getRandomToppingForLevel(int playerLevel) const {
    vector<function<unique_ptr<Topping>()>> available;

    for (const auto& f : fruitOptions) {
        auto topping = f();  // create one temporarily to check unlockLevel
        if (playerLevel >= topping->getUnlockLevel()) {
            available.push_back([f]() { return f(); });
        }
    }

    for (const auto& s : sweetOptions) {
        auto topping = s();
        if (playerLevel >= topping->getUnlockLevel()) {
            available.push_back([s]() { return s(); });
        }
    }

    if (available.empty()) return nullptr;

    int index = rand() % available.size();
    return available[index]();
}

};
