//
// Created by roki on 2025-09-16.
//

#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class weapon {
    std::string connect_character_name;
    std::string name;

    struct upgrade_equipment {
        std::string equipment_one;
        std::string equipment_two;
        std::string equipment_three;
        std::string unique_equipment = "";
    } equipment;

    struct bonus_stats {
        int atk;
        int hp;
        int healing;
    };

public:
    weapon() = default;

    ~weapon() = default;
};

#endif //WEAPON_H
