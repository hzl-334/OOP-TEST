//version for saving and uploading game 
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
#include "DayManager.hpp"
int Customer::nextID = 1;

int main() {
    GameManager game;

    std::cout << "Welcome to Papa's Freezeria!\n";

    int choice = 0;
    while (true) {
        std::cout << "1. Start New Game\n2. Load Game\n> ";
        std::string input;
        std::getline(std::cin, input);

        if (input == "1") {
            break;
        } else if (input == "2") {
            game.loadGame();
            break;
        } else {
            std::cout << "Invalid input. Please enter 1 or 2.\n";
        }
    }

    bool completed = game.play();  // this now tells us if game finished or was quit

    std::cout << "\nWould you like to save your progress? (y/n): ";
    std::string saveChoice;
    std::getline(std::cin, saveChoice);
    if (saveChoice == "y" || saveChoice == "Y") {
        game.saveGame();
    } else {
        std::cout << "Game progress not saved.\n";
    }

    std::cout << "\nThanks for playing!\n";
    return 0;
}
