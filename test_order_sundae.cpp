#include <string> 
#include <vector> 
#include <iostream>  
#include <memory>    

using namespace std; 

#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include "Order.hpp"
#include "Ingredients.hpp"
#include "Topping.hpp"

TEST_CASE("Order correctly stores data", "[Order]") {
    ToppingList toppingList;
    auto topping = toppingList.getRandomTopping();

    Order order("Vanilla", std::move(topping), "Medium");

    REQUIRE(order.getFlavor() == "Vanilla");
    REQUIRE(order.getSize() == "Medium");

    REQUIRE_FALSE(order.getToppingName().empty());
    REQUIRE_FALSE(order.getToppingType().empty());

    // check name of topping
    std::string name = order.getToppingName();
    REQUIRE((
        name == "Banana" ||
        name == "Cherry" ||
        name == "Sprinkles" ||
        name == "Oreos"
    ));

    //check type of topping
    std::string type = order.getToppingType();
    REQUIRE((
        type == "Fruit topping" ||
        type == "Sweet topping"
    ));

}

TEST_CASE("Sundae build with manual values", "[Sundae]") {
    Sundae sundae;
    sundae.flavor = "Strawberry";
    sundae.size = "Large";
    sundae.topping = std::make_unique<FruitTopping>("Cherry");

    REQUIRE(sundae.getFlavor() == "Strawberry");
    REQUIRE(sundae.getSize() == "Large");
    REQUIRE(sundae.getToppingName() == "Cherry");
    REQUIRE(sundae.getToppingType() == "Fruit topping");
}

TEST_CASE("Matching logic between Order and Sundae", "[Matching]") {
    auto topping1 = std::make_unique<SweetTopping>("Oreos");
    Order order("Chocolate", std::move(topping1), "Small");

    Sundae sundae;
    sundae.flavor = "Chocolate";
    sundae.size = "Small";
    sundae.topping = std::make_unique<SweetTopping>("Oreos");

    REQUIRE(order.getFlavor() == sundae.getFlavor());
    REQUIRE(order.getSize() == sundae.getSize());
    REQUIRE((order.getToppingType() == "Fruit topping" || order.getToppingType() == "Sweet topping"));

}
