//
// Created by roki on 2025-09-16.
//

#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class weapon {
    std::string connect_character_name;
    std::string name;

    std::string image_wp_filename;

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
    } _stats;

public:
    weapon() = default;

    ~weapon() = default;

public:
    void set_weapon_name(const std::string &connected_ch, const std::string &weapon_name);

    void set_upgrade_equipment(const std::string &upgrade_equipment_one,
                               const std::string &upgrade_equipment_two,
                               const std::string &upgrade_equipment_three,
                               const std::string &upgrade_equipment_unique = "");

    void set_boost_stats(const int boost_atk, const int boost_hp, const int boost_healing);

    void create_weapon(const std::string &_path) const;

    void set_weapon_image(const std::string &src_img_path, const std::string &dest_folder);

    std::string to_json() const;
};

#endif //WEAPON_H
