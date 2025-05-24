#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>
using namespace std;

#include "Ingredients.hpp"
#include "Topping.hpp"
#include "Order.hpp"
#include "Customer.hpp"
#include "PlayerLevel.hpp"

int Customer::nextID = 1;

class Game {
public:
    void play() {
        srand(time(0));  // Seed RNG
        cout << "Welcome to Papa's Freezeria!\n\n";

        // Day 1: Tutorial + Starter + Post-Tutorial customers
        vector<Customer> customers = {
            {"Mandi", "Tutorial", "Day 1"},
            {"Tony", "Post-Tutorial", "Day 1"},
            {"Alberto", "Starter", "Day 1"},
            {"Penny", "Starter", "Day 1"},
            {"Lisa", "Starter", "Day 1"},
            {"Matt", "Starter", "Day 1"},
            {"Wally", "Starter", "Day 1"}
        };

        // Generate unique orders for each customer
        for (auto& customer : customers) {
            customer.generateOrder();
        }

        // Simulate taking and building sundae for the first customer
        Customer& currentCustomer = customers[0];
        currentCustomer.getOrder().show();

        Sundae sundae;
        sundae.build();

        int score = calculateScore(currentCustomer, sundae);
        cout << "\nYou scored: " << score << "/3\n";

        PlayerLevel playerlevel;
        playerlevel.addXP(score * 40);
        playerlevel.showStatus();

        if (score == 3) {
            cout << "Perfect sundae! Great job!\n";
        } else if (score == 2) {
            cout << "Almost perfect!\n";
        } else {
            cout << "Better luck next time.\n";
        }

        cout << "\nRemaining customers today:\n";
        for (size_t i = 1; i < customers.size(); ++i) {
            cout << "- " << customers[i].getName() << " (ID: " << customers[i].getID() << ")\n";
        }
    }

private:
   int calculateScore(Customer& customer, Sundae& sundae) {
    int score = 0;
    if (equalIgnoreCase(customer.getOrder().getFlavor(), sundae.getFlavor())) score++;
    if (equalIgnoreCase(customer.getOrder().getToppingName(), sundae.getToppingName())) score++;
    if (equalIgnoreCase(customer.getOrder().getSize(), sundae.getSize())) score++;
    return score;
}

    bool equalIgnoreCase(string a, string b) {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i) {
            if (tolower(a[i]) != tolower(b[i])) return false;
        }
        return true;
    }
};

int main() {
    Game game;
    game.play();
    return 0;
}
