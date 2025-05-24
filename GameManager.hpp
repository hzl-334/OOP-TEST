#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>

#include "PlayerLevel.hpp"
#include "Customer.hpp"
#include "Order.hpp"
#include "DayManager.hpp"
#include "Topping.hpp"
class GameManager {
private:
    int currentDay = 1;
    int maxDays = 5;
    std::vector<std::string> allFlavors = {"Vanilla", "Chocolate", "Strawberry", "Mint", "Caramel", "Blueberry"};
    std::vector<std::string> unlockedFlavors = {"Vanilla", "Chocolate", "Strawberry"};
    PlayerLevel playerLevel;
    ToppingList toppingList;

//no longer need as level controlled in ingredient classes
    // void unlockNewFlavor() {
    //     for (const auto& flavor : allFlavors) {
    //         if (std::find(unlockedFlavors.begin(), unlockedFlavors.end(), flavor) == unlockedFlavors.end()) {
    //             unlockedFlavors.push_back(flavor);
    //             std::cout << "\n🎉 New flavor unlocked: " << flavor << "!\n";
    //             break;
    //         }
    //     }
    // }

public:
    bool play() {
        srand(time(0));
        std::cout << "Welcome to Papa's Freezeria!\n\n";

        while (currentDay <= maxDays) {
            std::cout << "\n===== Day " << currentDay << " =====\n";

DayManager day(currentDay, unlockedFlavors, toppingList);
bool continuePlaying = day.runDay(playerLevel);  
if (!continuePlaying) {
    return false;  // exit to main if player quit
}
// NO LONGER NEED FOR UNLOCKING
            // if (currentDay % 2 == 0 && unlockedFlavors.size() < allFlavors.size()) {
            //     unlockNewFlavor();
            // }

            currentDay++;
        }

        std::cout << "\nThanks for playing! You reached level " << playerLevel.getLevel() << "!\n";
return true; 
}

// load and save game
    void saveGame(const std::string& filename = "savegame.txt") {
        std::ofstream out(filename);
        if (!out) {
            std::cerr << "❌ Could not open save file.\n";
            return;
        }

        out << currentDay << '\n';
        out << playerLevel.getLevel() << ' ' << playerLevel.getXP() << '\n';
        out << unlockedFlavors.size() << '\n';
        for (const auto& flavor : unlockedFlavors) {
            out << flavor << '\n';
        }

        std::cout << "💾 Game saved to " << filename << "!\n";
    }

    bool loadGame(const std::string& filename = "savegame.txt") {
        std::ifstream in(filename);
        if (!in) {
            std::cerr << "❌ Save file not found. Starting a new game.\n";
            return false;
        }

        int level, xp, flavorCount;
        in >> currentDay >> level >> xp >> flavorCount;
        in.ignore();

        unlockedFlavors.clear();
        for (int i = 0; i < flavorCount; ++i) {
            std::string flavor;
            std::getline(in, flavor);
            unlockedFlavors.push_back(flavor);
        }

        playerLevel = PlayerLevel(level, xp);
        std::cout << "Game loaded from " << filename << "! Resuming from Day " << currentDay << ".\n";

        return true;
    }

void showNewToppingUnlocks(int oldLevel, int newLevel, const ToppingList& toppingList) {
    for (int level = oldLevel + 1; level <= newLevel; ++level) {
        auto unlocked = toppingList.getToppingNamesForLevel(level);
        for (const auto& name : unlocked) {
            std::cout << "🎉 New topping unlocked at level " << level << ": " << name << "\n";
        }
    }
}

};


// // OLD new topping unlocks NO LONGER NEEDED 
// void showNewToppingUnlocks(int oldLevel, int newLevel, const ToppingList& toppingList) {
//     std::set<std::string> alreadyUnlocked;

//     for (int level = oldLevel + 1; level <= newLevel; ++level) {
//         for (int i = 0; i < 50; ++i) {
//             auto topping = toppingList.getRandomToppingForLevel(level);
//             if (topping) {
//                 std::string name = topping->getName();
//                 if (alreadyUnlocked.insert(name).second) {
//                     std::cout << "New topping unlocked at level " << level << ": " << name << "\n";
//                 }
//             }
//         }
//     }
// }

// class GameManager {
// private:
//     int currentDay = 1;
//     int customersServedToday = 0;
//     int customersExpectedToday = 3;
//     int maxDays = 5;
//     vector<string> allFlavors = {"Vanilla", "Chocolate", "Strawberry", "Mint", "Caramel", "Blueberry"};
//     vector<string> unlockedFlavors = {"Vanilla", "Chocolate", "Strawberry"};
//     PlayerLevel playerLevel;

//     int calculateScore(Customer& customer, Sundae& sundae) {
//         int score = 0;
//         if (equalIgnoreCase(customer.getOrder().getFlavor(), sundae.getFlavor())) score++;
//         if (equalIgnoreCase(customer.getOrder().getToppingName(), sundae.getToppingName())) score++;
//         if (equalIgnoreCase(customer.getOrder().getSize(), sundae.getSize())) score++;
//         return score;
//     }

//     bool equalIgnoreCase(const string& a, const string& b) {
//         if (a.size() != b.size()) return false;
//         for (size_t i = 0; i < a.size(); ++i) {
//             if (tolower(a[i]) != tolower(b[i])) return false;
//         }
//         return true;
//     }

//     void unlockNewFlavor() {
//         for (const auto& flavor : allFlavors) {
//             if (find(unlockedFlavors.begin(), unlockedFlavors.end(), flavor) == unlockedFlavors.end()) {
//                 unlockedFlavors.push_back(flavor);
//                 cout << "\n🎉 New flavor unlocked: " << flavor << "!\n";
//                 break;
//             }
//         }
//     }

//     string getRandom(const vector<string>& options) {
//         return options[rand() % options.size()];
//     }

//     Customer generateCustomer(const string& name, const string& debutType, const string& debutCondition) {
//         Customer customer(name, debutType, debutCondition);
//         customer.overrideFlavorOptions(unlockedFlavors);  // Allow using current unlocked flavors
//         customer.generateOrder();
//         return customer;
//     }

//     int getExpectedCustomers(int level) {
//         if (level == 1) return 3;
//         else if (level == 2) return 4;
//         else return 5 + (level - 2);  // Example: increase by 1 each level after 2
//     }

//     void endDay() {
//         cout << "\n✅ Day " << currentDay << " completed!\n";

//         // Flavor unlock every 2 days
//         if (currentDay % 2 == 0 && unlockedFlavors.size() < allFlavors.size()) {
//             unlockNewFlavor();
//         }

//         currentDay++;
//     }

// public:
//     void play() {
//         srand(time(0));
//         cout << "Welcome to Papa's Freezeria!\n\n";

//         while (currentDay <= maxDays) {
//             cout << "\n===== Day " << currentDay << " =====\n";
//             customersServedToday = 0;
//             customersExpectedToday = getExpectedCustomers(playerLevel.getLevel());

//             vector<Customer> customers;

//             for (int i = 0; i < customersExpectedToday; ++i) {
//                 string name = "Customer" + to_string(i + 1);
//                 string debutType = (i == 0 && currentDay == 1) ? "Tutorial" : "Standard";
//                 customers.push_back(generateCustomer(name, debutType, "Day " + to_string(currentDay)));
//             }

//             for (Customer& customer : customers) {
//                 cout << "\nServing " << customer.getName() << " (ID: " << customer.getID() << ")\n";
//                 customer.getOrder().show();

//                 Sundae sundae;
//                 sundae.build();

//                 int score = calculateScore(customer, sundae);
//                 cout << "\nYou scored: " << score << "/3\n";

//                 playerLevel.addXP(score * 40);
//                 playerLevel.showStatus();

//                 if (score == 3) cout << "Perfect sundae! Great job!\n";
//                 else if (score == 2) cout << "Almost perfect!\n";
//                 else cout << "Better luck next time.\n";

//                 customersServedToday++;
//             }

//             endDay();  // Ends the day after all customers are served
//         }

//         cout << "\nThanks for playing! You reached level " << playerLevel.getLevel() << "!\n";
//     }


//     // save and upload game 
//     void saveGame(const string& filename = "savegame.txt") {
//     ofstream out(filename);
//     if (!out) {
//         cerr << "❌ Could not open save file.\n";
//         return;
//     }

//     out << currentDay << '\n';
//     out << playerLevel.getLevel() << ' ' << playerLevel.getXP() << '\n';
//     out << unlockedFlavors.size() << '\n';
//     for (const auto& flavor : unlockedFlavors) {
//         out << flavor << '\n';
//     }

//     cout << "💾 Game saved to " << filename << "!\n";
// }

// bool loadGame(const string& filename = "savegame.txt") {
//     ifstream in(filename);
//     if (!in) {
//         cerr << "❌ Save file not found. Starting a new game.\n";
//         return false;
//     }

//     int level, xp, flavorCount;
//     in >> currentDay >> level >> xp >> flavorCount;
//     in.ignore(); // skip newline

//     unlockedFlavors.clear();
//     for (int i = 0; i < flavorCount; ++i) {
//         string flavor;
//         getline(in, flavor);
//         unlockedFlavors.push_back(flavor);
//     }

//     playerLevel = PlayerLevel(level, xp);  // Needs custom constructor

//     cout << "📂 Game loaded from " << filename << "!\n";
//     return true;
// }

// };