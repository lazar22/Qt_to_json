//
// Created by roki on 2025-09-02.
//

#include "character.h"

#include <iostream>
#include <ostream>

void character::set_basic_info(const std::string _name, const std::string _aftername, const int _age,
                               const int _height) {
    name = _name;
    aftername = _aftername;
    age = _age;
    height = _height;

    // Debug
    std::cout << "-=Basic Info=-" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Aftername: " << aftername << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << std::endl;
}

void character::set_class_info(const int _star, const int _combat_class, const int _armor_class,
                               const int _damage_class) {
    stars = _star;
    combat_class = _combat_class;
    armor_class = _armor_class;
    damage_class = _damage_class;

    // Debug
    std::cout << "-=Class Info=-" << std::endl;
    std::cout << "Stars: " << stars_to_string(_star) << std::endl;
    std::cout << "Combat Class: " << character_combat_to_string(combat_class) << std::endl;
    std::cout << "Armor Class: " << armor_type_to_string(armor_class) << std::endl;
    std::cout << "Damage Class: " << attack_type_to_string(damage_class) << std::endl;
    std::cout << std::endl;
}

void character::set_terrain_compatability(const int _street, const int _outdoor, const int _indoor) {
    terrain_ = {
        .street = _street,
        .outdoor = _outdoor,
        .indoor = _indoor
    };

    // Debug
    std::cout << "-=Terrain=-" << std::endl;
    std::cout << "Street: " << control_power_to_string(terrain_.street) << std::endl;
    std::cout << "Outdoor: " << control_power_to_string(terrain_.outdoor) << std::endl;
    std::cout << "Indoor: " << control_power_to_string(terrain_.indoor) << std::endl;
    std::cout << std::endl;
}

void character::set_character_specification_info(const int _max_hp, const int _atk, const int _healing,
                                                 const int _accuracy, const int _evasion, const int _crit,
                                                 const int _crit_res, const int _crit_dmg, const int _crit_dmg_res,
                                                 const int _stability, const int _normal_att_range, const int _cc_power,
                                                 const int _cc_res, const int _def_piercing, const int _mag_count) {
    specification_ = {
        .max_hp = _max_hp,
        .atk = _atk,
        .healing = _healing,
        .accuracy = _accuracy,
        .evasion = _evasion,
        .crit = _crit,
        .crit_res = _crit_res,
        .crit_dmg = _crit_dmg,
        .crit_dmg_res = _crit_dmg_res,
        .stability = _stability,
        .normal_att_range = _normal_att_range,
        .cc_power = _cc_power,
        .cc_res = _cc_res,
        .def_piercing = _def_piercing,
        .mag_count = _mag_count
    };

    // Debug
    std::cout << "-=Character Sped=-" << std::endl;
    std::cout << "HP: " << specification_.max_hp << std::endl;
    std::cout << "ATK: " << specification_.atk << std::endl;
    std::cout << "Healing: " << specification_.healing << std::endl;
    std::cout << "Accuracy: " << specification_.accuracy << std::endl;
    std::cout << "Evasion: " << specification_.evasion << std::endl;
    std::cout << "Crit: " << specification_.crit << std::endl;
    std::cout << "Crit Res: " << specification_.crit_res << std::endl;
    std::cout << "Crit Dmg: " << specification_.crit_dmg << std::endl;
    std::cout << "Crit Dmg Res: " << specification_.crit_dmg_res << std::endl;
    std::cout << "Stability: " << specification_.stability << std::endl;
    std::cout << "Normal Att Range: " << specification_.normal_att_range << std::endl;
    std::cout << "CC Power: " << specification_.cc_power << std::endl;
    std::cout << "CC Res: " << specification_.cc_res << std::endl;
    std::cout << "Def Piercing: " << specification_.def_piercing << std::endl;
    std::cout << "Mag Count: " << specification_.mag_count << std::endl;
    std::cout << std::endl;
}

void character::set_school(const int _school) {
    school = _school;

    // Debug
    std::cout << "-=School=-" << std::endl;
    std::cout << "School: " << school_to_string(school) << std::endl;
    std::cout << std::endl;
}

// Helpers
const char *character::control_power_to_string(const int value) {
    const char *return_value;

    switch (value) {
        case CONTROL_POWER_OUTSTANDING:
            return_value = "Outstanding 😆";
            break;
        case CONTROL_POWER_EXCELLENT:
            return_value = "Excellent 😁";
            break;
        case CONTROL_POWER_GOOD:
            return_value = "Good 😀";
            break;
        case CONTROL_POWER_NATURAL:
            return_value = "Natural 😐";
            break;
        case CONTROL_POWER_BAD: return_value = "Bad 😣";
            break;
        case CONTROL_POWER_TERRABLE:
            return_value = "Terrible 😡";
            break;
        default:
            return_value = "Unknown";
            break;
    }

    return return_value;
}

const char *character::stars_to_string(const int value) {
    const char *return_value;
    switch (value) {
        case THREE_STAR:
            return_value = "⭐⭐⭐";
            break;
        case TWO_STAR:
            return_value = "⭐⭐";
            break;
        case ONE_STAR:
            return_value = "⭐";
            break;
        default:
            return_value = "Unknown";
            break;
    }

    return return_value;
}

const char *character::armor_type_to_string(const int value) {
    const char *return_value;
    switch (value) {
        case DEF_NORMAL:
            return_value = "Normal";
            break;
        case DEF_LIGHT:
            return_value = "Light";
            break;
        case DEF_HEAVY:
            return_value = "Heavy";
            break;
        case DEF_SPECIAL:
            return_value = "Special";
            break;
        case DEF_ELASTIC:
            return_value = "Elastic";
            break;
        case DEF_STRUCTURE:
            return_value = "Structure";
            break;
        default:
            return_value = "Unknown";
            break;
    }

    return return_value;
}

const char *character::attack_type_to_string(const int value) {
    const char *return_value;
    switch (value) {
        case ATT_NORMAL:
            return_value = "Normal";
            break;
        case ATT_EXPLOSION:
            return_value = "Explosion";
            break;
        case ATT_PENETRATION:
            return_value = "Penetration";
            break;
        case ATT_MYSTIC:
            return_value = "Mystic";
            break;
        case ATT_SONIC:
            return_value = "Sonic";
            break;
        case ATT_SIGE:
            return_value = "Sige";
            break;
        default:
            return_value = "Unknown";
            break;
    }

    return return_value;
}

const char *character::character_type_to_string(const int value) {
    const char *return_value;
    switch (value) {
        case CHARACTER_TYPE_TANK:
            return_value = "Tank";
            break;
        case CHARACTER_TYPE_ATTACKER:
            return_value = "Attacker";
            break;
        case CHARACTER_TYPE_HEALER:
            return_value = "Healer";
            break;
        case CHARACTER_TYPE_SUPPORT:
            return_value = "Support";
            break;
        case CHARACTER_TYPE_TACTICAL_SUPPORT:
            return_value = "Tactical Support";
            break;
        default:
            return_value = "Unknown";
            break;
    }

    return return_value;
}

const char *character::character_combat_to_string(const int value) {
    const char *return_value;
    switch (value) {
        case CHARACTER_COMBAT_STRIKER:
            return_value = "Striker";
            break;
        case CHARACTER_COMBAT_SPECIAL:
            return_value = "Special";
            break;
        default:
            return_value = "Unknown";
            break;
    }

    return return_value;
}

const char *character::school_to_string(const int value) {
    const char *return_value;
    switch (value) {
        case ABYDOS_HIGH_SCHOOL:
            return_value = "Abydos High School";
            break;
        case GEHENNA_ACADEMY:
            return_value = "Gehenna Academy";
            break;
        case MILLENNIUM_SCIENCE_SCHOOL:
            return_value = "Millennium Science School";
            break;
        case TRINITY_GENERAL_SCHOOL:
            return_value = "Trinity General School";
            break;
        case HYAKKIYAKO_ALLIANCE_ACADEMY:
            return_value = "Hyakkikayo Alliance Academy";
            break;
        case SHANHAIJING_SENIOR_SECONDARY_SCHOOL:
            return_value = "Shanhaijing Senior Secondary School";
            break;
        case RED_WINTER_FEDERAl_ACADEMY:
            return_value = "Red Winter Federal Academy";
            break;
        case VALKYRIE_POLICE_ACADEMY:
            return_value = "Valkyrie Police Academy";
            break;
        case ARIUS_BRANCH_SCHOOL:
            return_value = "Arius Branch School";
            break;
        case SRT_SPECIAL_ACADEMY:
            return_value = "SRT Special Academy";
            break;
        case KRONOS_SCHOOL_OF_JOURNALISM:
            return_value = "Kronos School of Journalism";
            break;
        case HIGHLANDER_RAILROAD_ACADEMY:
            return_value = "Highlander Railroad Academy";
            break;
        default:
            return_value = "Unknown";
            break;
    }

    return return_value;
}

