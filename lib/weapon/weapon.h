//
// Created by roki on 2025-09-16.
//

#ifndef WEAPON_H
#define WEAPON_H
#include <string>

enum item_one_list {
    HAT = 0,
    BOOTS,
    TALISMAN
};

enum item_two_list {
    GLOVES = 0,
    HAIRPIN,
    CLOCK
};

enum unique_item {
    NONE = 0,
};

class weapon {
    std::string connect_character_name;
    std::string name;

    struct upgrade_items {
        int item_one;
        int item_two;
        int item_three;
        int unique_item = NONE;
    };

    struct bonus_stats {
        int atk;
        int hp;
        int healing;
    };
};

#endif //WEAPON_H
