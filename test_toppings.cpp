#include <iostream>
#include <vector>

using namespace std;

#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"


#include <memory>
#include <set>
#include <string>

#include "Ingredients.cpp"  // Include your ToppingList and Topping classes

TEST_CASE("FruitTopping instance behaves as expected", "[FruitTopping]") {
    FruitTopping banana("Banana");
    REQUIRE(banana.getName() == "Banana");
    REQUIRE(banana.getCategory() == "Topping");
    REQUIRE(banana.getType() == "Fruit topping");
}

TEST_CASE("SweetTopping instance behaves as expected", "[SweetTopping]") {
    SweetTopping sprinkles("Sprinkles");
    REQUIRE(sprinkles.getName() == "Sprinkles");
    REQUIRE(sprinkles.getCategory() == "Topping");
    REQUIRE(sprinkles.getType() == "Sweet topping");
}

TEST_CASE("ToppingList returns valid random toppings", "[ToppingList]") {
    ToppingList list;

    for (int i = 0; i < 20; ++i) {
        auto topping = list.getRandomTopping();
        REQUIRE(topping != nullptr);
        REQUIRE(topping->getCategory() == "Topping");
        REQUIRE(!topping->getName().empty());

        string name = topping->getName();
        bool validName =
            name == "Banana" ||
            name == "Cherry" ||
            name == "Sprinkles" ||
            name == "Oreos";

        REQUIRE(validName);
    }
}

TEST_CASE("ToppingList includes both fruit and sweet toppings", "[ToppingList]") {
    ToppingList list;
    set<string> typesSeen;

    for (int i = 0; i < 50; ++i) {
        auto topping = list.getRandomTopping();
        REQUIRE(topping != nullptr);
        typesSeen.insert(topping->getType());
    }

    REQUIRE(typesSeen.count("Fruit topping") > 0);
    REQUIRE(typesSeen.count("Sweet topping") > 0);
}
