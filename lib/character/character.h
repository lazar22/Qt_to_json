//
// Created by roki on 2025-09-02.
//

#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

enum control_power {
    CONTROL_POWER_OUTSTANDING,
    CONTROL_POWER_EXCELLENT,
    CONTROL_POWER_GOOD,
    CONTROL_POWER_NATURAL,
    CONTROL_POWER_BAD,
    CONTROL_POWER_TERRABLE
};

enum character_combat {
    CHARACTER_COMBAT_STRIKER,
    CHARACTER_COMBAT_SPECIAL
};

enum character_type {
    CHARACTER_TYPE_TANK,
    CHARACTER_TYPE_ATTACKER,
    CHARACTER_TYPE_HEALER,
    CHARACTER_TYPE_SUPPORT,
    CHARACTER_TYPE_TACTICAL_SUPPORT,
};

enum stars {
    THREE_STAR,
    TWO_STAR,
    ONE_STAR,
};

enum def_type {
    DEF_NORMAL,
    DEF_LIGHT,
    DEF_HEAVY,
    DEF_SPECIAL,
    DEF_ELASTIC,
    DEF_STRUCTURE
};

enum att_type {
    ATT_NORMAL,
    ATT_EXPLOSION,
    ATT_PENETRATION,
    ATT_MYSTIC,
    ATT_SONIC,
    ATT_SIGE
};

enum school_names {
    ABYDOS_HIGH_SCHOOL,
    GEHENNA_ACADEMY,
    MILLENNIUM_SCIENCE_SCHOOL,
    TRINITY_GENERAL_SCHOOL,
    HYAKKIYAKO_ALLIANCE_ACADEMY,
    SHANHAIJING_SENIOR_SECONDARY_SCHOOL,
    RED_WINTER_FEDERAl_ACADEMY,
    VALKYRIE_POLICE_ACADEMY,
    ARIUS_BRANCH_SCHOOL,
    SRT_SPECIAL_ACADEMY,
    KRONOS_SCHOOL_OF_JOURNALISM,
    HIGHLANDER_RAILROAD_ACADEMY
};

class character {
    int id = 0;

    std::string name;
    std::string aftername;

    int age = 0;
    int height = 0;

    int stars = ONE_STAR;
    int combat_class = CHARACTER_COMBAT_STRIKER;
    int armor_class = DEF_LIGHT;
    int damage_class = ATT_EXPLOSION;

    int school = TRINITY_GENERAL_SCHOOL;

    struct info {
        int max_hp = 0;
        int atk = 0;
        int healing = 0;
        int accuracy = 0;
        int evasion = 0;
        int crit = 0;
        int crit_res = 0;
        int crit_dmg = 0;
        int crit_dmg_res = 0;
        int stability = 0;
        int normal_att_range = 0;
        int cc_power = 0;
        int cc_res = 0;
        int def_piercing = 0;
        int mag_count = 0;
    };

    struct terrain {
        int street = CONTROL_POWER_OUTSTANDING;
        int outdoor = CHARACTER_COMBAT_STRIKER;
        int indoor = CHARACTER_COMBAT_STRIKER;
    };

public:
    void set_basic_info(const std::string _name, const std::string _aftername, const int _age, const int _height);

    void set_class_info(const int _star, const int _combat_class, const int _armor_class, const int _damage_class);

    void set_terrain_compatability(const int _street, const int _outdoor, const int _indoor);

    void set_character_specification_info(const int _max_hp, const int _atk, const int _healing,
                                          const int _accuracy, const int _evasion, const int _crit, const int _crit_res,
                                          const int _crit_dmg, const int _crit_dmg_res, const int _stability,
                                          const int _normal_att_range, const int _cc_power, const int _cc_res,
                                          const int _def_piercing, const int _mag_count);

    void set_school(const int _school);

    void create_character();
};

#endif //CHARACTER_H
