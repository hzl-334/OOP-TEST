#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std; 

#include "Ingredients.hpp"
#include "Topping.hpp"
#include "Order.hpp"
#include "Customer.hpp"
#include "PlayerLevel.hpp"

class Game {
    //add functionality to save/upload game
public:
    void play() {
        srand(time(0));  // Seed RNG
        cout << "Welcome to Papa's Freezeria!\n";

        Customer customer("Ben",1);
        customer.showOrder();

        Sundae sundae;
        sundae.build();
 
//score calc so far out of 3
        int score = calculateScore(customer, sundae);
        cout << "\nYou scored: " << score << "/3\n";

        PlayerLevel playerlevel; 

        playerlevel.addXP(score * 40);  // so far have 40 for score
        playerlevel.showStatus();       // show level and the xp

        if (score == 3) {
            cout << "Perfect sundae! Great job!\n";
        } else if (score == 2) {
            cout << "Almost perfect!\n";
        } else {
            cout << "Better luck next time.\n";
        }
    }

private:
    int calculateScore(Customer& customer, Sundae& sundae) {
        int score = 0;
        if (equalIgnoreCase(customer.getFlavor(), sundae.flavor)) score++;
        if (equalIgnoreCase(customer.getToppingName(), sundae.getToppingName())) score++;
        if (equalIgnoreCase(customer.getSize(), sundae.size)) score++;
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

int main(){
    Game game;
    game.play();
    return 0;

}
