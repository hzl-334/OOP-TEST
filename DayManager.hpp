#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>

#include "PlayerLevel.hpp"
#include "Customer.hpp"
#include "Order.hpp"
#include "GameManager.hpp"
#include "Unlock.hpp"

class DayManager {
private:
    int dayNumber;
    std::vector<Customer> customers;
    std::vector<std::string> unlockedFlavors;
    const ToppingList& toppingList; //CAN SEE TOPPINGS UNLOCK

    int getExpectedCustomers(int level) {
        if (level == 1) return 3;
        else if (level == 2) return 4;
        else return 5 + (level - 2);
    }

    Customer generateCustomer(const std::string& name, const std::string& debutType) {
        Customer customer(name, debutType, "Day " + std::to_string(dayNumber));
        customer.overrideFlavorOptions(unlockedFlavors);
        customer.generateOrder();
        return customer;
    }

//this toppings unlcok not working :
//  void showNewToppingUnlocks(int oldLevel, int newLevel) {
//     for (int level = oldLevel + 1; level <= newLevel; ++level) {
//         auto unlocked = toppingList.getToppingNamesForLevel(level);
//         for (const auto& name : unlocked) {
//             std::cout << " New topping unlocked at level " << level << ": " << name << "\n";
//         }
//     }
// }



public:
DayManager(int day, const std::vector<std::string>& unlocked, const ToppingList& toppings)
    : dayNumber(day), unlockedFlavors(unlocked), toppingList(toppings) {}

    bool runDay(PlayerLevel& playerLevel) {
        int expected = getExpectedCustomers(playerLevel.getLevel());
        for (int i = 0; i < expected; ++i) {
            std::string name = "Customer" + std::to_string(i + 1);
            std::string debutType = (i == 0 && dayNumber == 1) ? "Tutorial" : "Standard";
            customers.push_back(generateCustomer(name, debutType));
        }
int oldLevel = playerLevel.getLevel();

 for (Customer& customer : customers) {
    std::cout << "\nServing " << customer.getName() << " (ID: " << customer.getID() << ")\n";
    customer.getOrder().show();

    std::string response;
    std::cout << "Type 'quit' to exit the game or press Enter to continue: ";
    std::getline(std::cin, response);
    if (response == "quit") {
        std::cout << "Exiting game early...\n";
        return false;
    }

    Sundae sundae;
    sundae.build();

    int score = 0;
    if (customer.getOrder().getFlavor() == sundae.getFlavor()) score++;
    if (customer.getOrder().getToppingName() == sundae.getToppingName()) score++;
    if (customer.getOrder().getSize() == sundae.getSize()) score++;

    std::cout << "You scored: " << score << "/3\n";

    int previousLevel = playerLevel.getLevel();
    playerLevel.addXP(score * 40);
    int currentLevel = playerLevel.getLevel();
    playerLevel.showStatus();
    if (currentLevel > previousLevel) {
        showNewToppingUnlocks(previousLevel, currentLevel,toppingList);
    }

    if (score == 3) std::cout << "Perfect sundae!\n";
    else if (score == 2) std::cout << "Almost perfect!\n";
    else std::cout << "Better luck next time.\n";
}
        // moved this into game manager
        // int newLevel = playerLevel.getLevel();
        // if (newLevel > oldLevel) {
        //         showNewToppingUnlocks(oldLevel, newLevel);
        //     }

        return true; 
    }
};

// class GameManager {
// private:
//     int currentDay = 1;
//     int maxDays = 5;
//     std::vector<std::string> allFlavors = {"Vanilla", "Chocolate", "Strawberry", "Mint", "Caramel", "Blueberry"};
//     std::vector<std::string> unlockedFlavors = {"Vanilla", "Chocolate", "Strawberry"};
//     PlayerLevel playerLevel;

//     void unlockNewFlavor() {
//         for (const auto& flavor : allFlavors) {
//             if (std::find(unlockedFlavors.begin(), unlockedFlavors.end(), flavor) == unlockedFlavors.end()) {
//                 unlockedFlavors.push_back(flavor);
//                 std::cout << "\n🎉 New flavor unlocked: " << flavor << "!\n";
//                 break;
//             }
//         }
//     }

// public:
//     void play() {
//         srand(time(0));
//         std::cout << "Welcome to Papa's Freezeria!\n\n";

//         while (currentDay <= maxDays) {
//             std::cout << "\n===== Day " << currentDay << " =====\n";

//             DayManager day(currentDay, unlockedFlavors);
//             day.runDay(playerLevel);

//             if (currentDay % 2 == 0 && unlockedFlavors.size() < allFlavors.size()) {
//                 unlockNewFlavor();
//             }

//             currentDay++;
//         }

//         std::cout << "\nThanks for playing! You reached level " << playerLevel.getLevel() << "!\n";
//     }

//     void saveGame(const std::string& filename = "savegame.txt") {
//         std::ofstream out(filename);
//         if (!out) {
//             std::cerr << "❌ Could not open save file.\n";
//             return;
//         }

//         out << currentDay << '\n';
//         out << playerLevel.getLevel() << ' ' << playerLevel.getXP() << '\n';
//         out << unlockedFlavors.size() << '\n';
//         for (const auto& flavor : unlockedFlavors) {
//             out << flavor << '\n';
//         }

//         std::cout << "💾 Game saved to " << filename << "!\n";
//     }

//     bool loadGame(const std::string& filename = "savegame.txt") {
//         std::ifstream in(filename);
//         if (!in) {
//             std::cerr << "❌ Save file not found. Starting a new game.\n";
//             return false;
//         }

//         int level, xp, flavorCount;
//         in >> currentDay >> level >> xp >> flavorCount;
//         in.ignore();

//         unlockedFlavors.clear();
//         for (int i = 0; i < flavorCount; ++i) {
//             std::string flavor;
//             std::getline(in, flavor);
//             unlockedFlavors.push_back(flavor);
//         }

//         playerLevel = PlayerLevel(level, xp);
//         std::cout << "📂 Game loaded from " << filename << "!\n";
//         return true;
//     }
// };
