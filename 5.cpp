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

int Customer::nextID = 1;

class Game {
private:
    int currentDay = 1;
    int customersServedToday = 0;
    int customersExpectedToday = 3;
    int maxDays = 5;
    vector<string> allFlavors = {"Vanilla", "Chocolate", "Strawberry", "Mint", "Caramel", "Blueberry"};
    vector<string> unlockedFlavors = {"Vanilla", "Chocolate", "Strawberry"};
    PlayerLevel playerLevel;

    int calculateScore(Customer& customer, Sundae& sundae) {
        int score = 0;
        if (equalIgnoreCase(customer.getOrder().getFlavor(), sundae.getFlavor())) score++;
        if (equalIgnoreCase(customer.getOrder().getToppingName(), sundae.getToppingName())) score++;
        if (equalIgnoreCase(customer.getOrder().getSize(), sundae.getSize())) score++;
        return score;
    }

    bool equalIgnoreCase(const string& a, const string& b) {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i) {
            if (tolower(a[i]) != tolower(b[i])) return false;
        }
        return true;
    }

    void unlockNewFlavor() {
        for (const auto& flavor : allFlavors) {
            if (find(unlockedFlavors.begin(), unlockedFlavors.end(), flavor) == unlockedFlavors.end()) {
                unlockedFlavors.push_back(flavor);
                cout << "\n🎉 New flavor unlocked: " << flavor << "!\n";
                break;
            }
        }
    }

    string getRandom(const vector<string>& options) {
        return options[rand() % options.size()];
    }

    Customer generateCustomer(const string& name, const string& debutType, const string& debutCondition) {
        Customer customer(name, debutType, debutCondition);
        customer.overrideFlavorOptions(unlockedFlavors);  // Allow using current unlocked flavors
        customer.generateOrder();
        return customer;
    }

    int getExpectedCustomers(int level) {
        if (level == 1) return 3;
        else if (level == 2) return 4;
        else return 5 + (level - 2);  // Example: increase by 1 each level after 2
    }

    void endDay() {
        cout << "\n✅ Day " << currentDay << " completed!\n";

        // Flavor unlock every 2 days
        if (currentDay % 2 == 0 && unlockedFlavors.size() < allFlavors.size()) {
            unlockNewFlavor();
        }

        currentDay++;
    }

public:
    void play() {
        srand(time(0));
        cout << "Welcome to Papa's Freezeria!\n\n";

        while (currentDay <= maxDays) {
            cout << "\n===== Day " << currentDay << " =====\n";
            customersServedToday = 0;
            customersExpectedToday = getExpectedCustomers(playerLevel.getLevel());

            vector<Customer> customers;

            for (int i = 0; i < customersExpectedToday; ++i) {
                string name = "Customer" + to_string(i + 1);
                string debutType = (i == 0 && currentDay == 1) ? "Tutorial" : "Standard";
                customers.push_back(generateCustomer(name, debutType, "Day " + to_string(currentDay)));
            }

            for (Customer& customer : customers) {
                cout << "\nServing " << customer.getName() << " (ID: " << customer.getID() << ")\n";
                customer.getOrder().show();

                Sundae sundae;
                sundae.build();

                int score = calculateScore(customer, sundae);
                cout << "\nYou scored: " << score << "/3\n";

                playerLevel.addXP(score * 40);
                playerLevel.showStatus();

                if (score == 3) cout << "Perfect sundae! Great job!\n";
                else if (score == 2) cout << "Almost perfect!\n";
                else cout << "Better luck next time.\n";

                customersServedToday++;
            }

            endDay();  // Ends the day after all customers are served
        }

        cout << "\nThanks for playing! You reached level " << playerLevel.getLevel() << "!\n";
    }
};

int main() {
    Game game;
    game.play();
    return 0;
}
