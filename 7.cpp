#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Placeholder for external classes
class Order {
public:
    string getFlavor() const { return "Vanilla"; }
    string getToppingName() const { return "Sprinkles"; }
    string getSize() const { return "Small"; }
    void show() const { cout << "Order: Vanilla + Sprinkles (Small)\n"; }
};

class Sundae {
public:
    string getFlavor() const { return "Vanilla"; }
    string getToppingName() const { return "Sprinkles"; }
    string getSize() const { return "Small"; }
    void build() { cout << "Building sundae...\n"; }
};

class PlayerLevel {
private:
    int level;
    int xp;

public:
    PlayerLevel() : level(1), xp(0) {}
    PlayerLevel(int lvl, int experience) : level(lvl), xp(experience) {}

    void addXP(int amount) {
        xp += amount;
        while (xp >= level * 100) {
            xp -= level * 100;
            level++;
            cout << "🎉 You leveled up! Now level " << level << "!\n";
        }
    }

    int getLevel() const { return level; }
    int getXP() const { return xp; }
    void showStatus() const {
        cout << "Level: " << level << " | XP: " << xp << "/" << level * 100 << "\n";
    }
};

class Customer {
private:
    static int nextID;
    int id;
    string name;
    string debutType;
    string debutCondition;
    Order order;

public:
    Customer(string name, string debutType, string debutCondition)
        : name(name), debutType(debutType), debutCondition(debutCondition), id(nextID++) {}

    void overrideFlavorOptions(const vector<string>& flavors) {
        // placeholder: use only unlocked flavors
    }

    void generateOrder() {
        // placeholder
    }

    string getName() const { return name; }
    int getID() const { return id; }
    const Order& getOrder() const { return order; }
};
int Customer::nextID = 1;

// ===== DayManager Class =====
class DayManager {
private:
    int dayNumber;
    vector<Customer> customers;
    vector<string> unlockedFlavors;

    int getExpectedCustomers(int level) {
        if (level == 1) return 3;
        else if (level == 2) return 4;
        else return 5 + (level - 2);
    }

    Customer generateCustomer(const string& name, const string& debutType) {
        Customer customer(name, debutType, "Day " + to_string(dayNumber));
        customer.overrideFlavorOptions(unlockedFlavors);
        customer.generateOrder();
        return customer;
    }

public:
    DayManager(int day, const vector<string>& unlocked) 
        : dayNumber(day), unlockedFlavors(unlocked) {}

    void runDay(PlayerLevel& playerLevel) {
        int expected = getExpectedCustomers(playerLevel.getLevel());
        for (int i = 0; i < expected; ++i) {
            string name = "Customer" + to_string(i + 1);
            string debutType = (i == 0 && dayNumber == 1) ? "Tutorial" : "Standard";
            customers.push_back(generateCustomer(name, debutType));
        }

        for (Customer& customer : customers) {
            cout << "\nServing " << customer.getName() << " (ID: " << customer.getID() << ")\n";
            customer.getOrder().show();

            Sundae sundae;
            sundae.build();

            int score = 0;
            if (customer.getOrder().getFlavor() == sundae.getFlavor()) score++;
            if (customer.getOrder().getToppingName() == sundae.getToppingName()) score++;
            if (customer.getOrder().getSize() == sundae.getSize()) score++;

            cout << "You scored: " << score << "/3\n";
            playerLevel.addXP(score * 40);
            playerLevel.showStatus();

            if (score == 3) cout << "Perfect sundae!\n";
            else if (score == 2) cout << "Almost perfect!\n";
            else cout << "Better luck next time.\n";
        }
    }
};

// ===== GameManager Class =====
class GameManager {
private:
    int currentDay = 1;
    int maxDays = 5;
    vector<string> allFlavors = {"Vanilla", "Chocolate", "Strawberry", "Mint", "Caramel", "Blueberry"};
    vector<string> unlockedFlavors = {"Vanilla", "Chocolate", "Strawberry"};
    PlayerLevel playerLevel;

    void unlockNewFlavor() {
        for (const auto& flavor : allFlavors) {
            if (find(unlockedFlavors.begin(), unlockedFlavors.end(), flavor) == unlockedFlavors.end()) {
                unlockedFlavors.push_back(flavor);
                cout << "\n🎉 New flavor unlocked: " << flavor << "!\n";
                break;
            }
        }
    }

public:
    void play() {
        srand(time(0));
        cout << "Welcome to Papa's Freezeria!\n\n";

        while (currentDay <= maxDays) {
            cout << "\n===== Day " << currentDay << " =====\n";

            DayManager day(currentDay, unlockedFlavors);
            day.runDay(playerLevel);

            if (currentDay % 2 == 0 && unlockedFlavors.size() < allFlavors.size()) {
                unlockNewFlavor();
            }

            currentDay++;
        }

        cout << "\nThanks for playing! You reached level " << playerLevel.getLevel() << "!\n";
    }

    void saveGame(const string& filename = "savegame.txt") {
        ofstream out(filename);
        if (!out) {
            cerr << "❌ Could not open save file.\n";
            return;
        }

        out << currentDay << '\n';
        out << playerLevel.getLevel() << ' ' << playerLevel.getXP() << '\n';
        out << unlockedFlavors.size() << '\n';
        for (const auto& flavor : unlockedFlavors) {
            out << flavor << '\n';
        }

        cout << "💾 Game saved to " << filename << "!\n";
    }

    bool loadGame(const string& filename = "savegame.txt") {
        ifstream in(filename);
        if (!in) {
            cerr << "❌ Save file not found. Starting new game.\n";
            return false;
        }

        int level, xp, flavorCount;
        in >> currentDay >> level >> xp >> flavorCount;
        in.ignore();

        unlockedFlavors.clear();
        for (int i = 0; i < flavorCount; ++i) {
            string flavor;
            getline(in, flavor);
            unlockedFlavors.push_back(flavor);
        }

        playerLevel = PlayerLevel(level, xp);
        cout << "📂 Game loaded from " << filename << "!\n";
        return true;
    }
};

int main() {
    GameManager game;

    int choice = 0;
    while (true) {
        cout << "1. New Game\n2. Load Game\n> ";
        string input;
        getline(cin, input);

        if (input == "1") {
            break; // new game, do nothing
        } else if (input == "2") {
            game.loadGame();
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    game.play();

    cout << "Save your game? (y/n): ";
    string saveChoice;
    getline(cin, saveChoice);
    if (saveChoice == "y" || saveChoice == "Y") {
        game.saveGame();
    }

    return 0;
}
