#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include "PlayerLevel.hpp"

TEST_CASE("Player starts at level 1 with 0 XP") {
    PlayerLevel player;
    REQUIRE(player.getLevel() == 1);
    REQUIRE(player.getXP() == 0);
    REQUIRE(player.getXPToNext() == 100);  // 1 * 100
}

TEST_CASE("Player gains XP without leveling up") {
    PlayerLevel player;
    player.addXP(30);
    REQUIRE(player.getXP() == 30);
    REQUIRE(player.getLevel() == 1);
    REQUIRE(player.getXPToNext() == 100);  // still level 1
}

TEST_CASE("Player levels up correctly at 100 XP") {
    PlayerLevel player;
    player.addXP(100);  // hits 100 XP
    REQUIRE(player.getLevel() == 2);       // levels up
    REQUIRE(player.getXP() == 0);          // XP reset
    REQUIRE(player.getXPToNext() == 200);  // 2 * 100
}

TEST_CASE("Player can level up multiple times at once") {
    PlayerLevel player;
    player.addXP(450); 

    REQUIRE(player.getLevel() == 3);
    REQUIRE(player.getXP() == 150);        
    REQUIRE(player.getXPToNext() == 300); 
}
