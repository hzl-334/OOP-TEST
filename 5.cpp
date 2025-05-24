#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <set>
using namespace std;

#include "Ingredients.hpp"
#include "Topping.hpp"
#include "Order.hpp"
#include "Customer.hpp"
#include "PlayerLevel.hpp"
#include "GameManager.hpp"
int Customer::nextID = 1;


int main() {
    Game game;
    game.play();
    return 0;
}
