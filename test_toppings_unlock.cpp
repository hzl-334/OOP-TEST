#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include "PlayerLevel.hpp"
#include "Topping.hpp"
#include <sstream>
#include <iostream>
#include <set>
#include <map>

// Utility function that simulates the topping unlock logic
std::map<int, std::set<std::string>> showNewToppingUnlocks(int oldLevel, int newLevel, const ToppingList& toppingList) {
    std::map<int, std::set<std::string>> unlockedPerLevel;

    for (int level = oldLevel + 1; level <= newLevel; ++level) {
        auto unlocked = toppingList.getToppingNamesForLevel(level);
        for (const auto& name : unlocked) {
            std::cout << "🎉 New topping unlocked at level " << level << ": " << name << "\n";
            unlockedPerLevel[level].insert(name);
        }
    }

    return unlockedPerLevel;
}

TEST_CASE("Toppings are correctly unlocked at each level") {
    ToppingList list;
    PlayerLevel player(1, 90);  // Start near level 2

    int oldLevel = player.getLevel();
    player.addXP(1000);  // Should reach level 5
    int newLevel = player.getLevel();
    REQUIRE(newLevel == 5);

    // Redirect std::cout
    std::stringstream buffer;
    std::streambuf* originalCout = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());

    std::map<int, std::set<std::string>> expectedUnlocks = showNewToppingUnlocks(oldLevel, newLevel, list);

    // Restore std::cout
    std::cout.rdbuf(originalCout);

    std::string output = buffer.str();

    std::cout << "=== Unlock Summary ===\n";
    for (const auto& [level, toppings] : expectedUnlocks) {
        std::cout << "Level " << level << " unlocked: ";
        for (const auto& topping : toppings) {
            std::cout << topping << " ";
        }
        std::cout << "\n";
    }

    // Assertions: ensure all expected lines are in output
    for (const auto& [level, toppings] : expectedUnlocks) {
        for (const std::string& topping : toppings) {
            std::string expectedLine = "🎉 New topping unlocked at level " + std::to_string(level) + ": " + topping;
            INFO("Checking printed message for level " << level << ": " << topping);
            REQUIRE(output.find(expectedLine) != std::string::npos);
        }
    }

    // Verify no extra unlock lines are printed
    std::istringstream lines(output);
    std::string line;
    int printedCount = 0;
    while (std::getline(lines, line)) {
        if (line.find("🎉 New topping unlocked at level") != std::string::npos)
            printedCount++;
    }

    size_t expectedCount = 0;
    for (const auto& [_, toppings] : expectedUnlocks)
        expectedCount += toppings.size();

    REQUIRE(printedCount == expectedCount);
}
