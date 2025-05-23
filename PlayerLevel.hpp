#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std; 

class PlayerLevel {
private:
    int level;
    int xp; 
    int xpToNextLevel; 

public:
// initialise player level as 1 with 0 xp
    PlayerLevel() : level(1), xp(0) {}

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
    int getXPToNext() const { return level*100; }

    void showStatus() const {
        cout << "Level: " << level << " | XP: " << xp << "/" << xpToNextLevel << "\n";
    }

};
