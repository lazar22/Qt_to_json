//
// Created by roki on 2025-09-16.
//
#include "weapon.h"
#include "json_utils.h"
#include "string_handler.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>


void weapon::set_weapon_name(const std::string& connected_ch, const std::string& weapon_name)
{
    connect_character_name = connected_ch;
    name = weapon_name;
}

void weapon::set_upgrade_equipment(const std::string& upgrade_equipment_one, const std::string& upgrade_equipment_two,
                                   const std::string& upgrade_equipment_three,
                                   const std::string& upgrade_equipment_unique)
{
    equipment.equipment_one = upgrade_equipment_one;
    equipment.equipment_two = upgrade_equipment_two;
    equipment.equipment_three = upgrade_equipment_three;
    equipment.unique_equipment = upgrade_equipment_unique;
}

void weapon::set_boost_stats(const int boost_atk, const int boost_hp, const int boost_healing)
{
    _stats.atk = boost_atk;
    _stats.hp = boost_hp;
    _stats.healing = boost_healing;
}

void weapon::create_weapon(const std::string& _path) const
{
    if (!_path.empty())
    {
        std::cout << _path;
        const std::string new_block = to_json();
        std::string err;
        if (json_utils::replace_object_in_file(_path, "Weapon", new_block, &err))
        {
            std::cerr << "[ERROR] " << err << "\n";
        }

        std::cout << "Ability block updated for " << connect_character_name << "\n";
    }
    else
    {
        std::cerr << "[ERROR] Path is empty.\n";
    }
}

void weapon::set_weapon_image(const std::string& src_img_path, const std::string& dest_folder)
{
    std::cout << "Copying weapon image from " << src_img_path << " to: " << dest_folder << std::endl;
    if (!src_img_path.empty() || !dest_folder.empty())
    {
        const std::string new_wp_img_filename = string_handler::to_lower(
                string_handler::remove_file_extension(
                    connect_character_name, ".json"))
            + "_" +
            string_handler::to_lower(string_handler::remove_empty_places(name))
            + ".png";
        const std::filesystem::path new_wp_img_path = std::filesystem::path(dest_folder) / new_wp_img_filename;


        try
        {
            std::filesystem::copy_file(src_img_path, new_wp_img_path,
                                       std::filesystem::copy_options::overwrite_existing);
            image_wp_filename = dest_folder + "/" + new_wp_img_filename;
        }
        catch (std::filesystem::filesystem_error& e)
        {
            std::cerr << "[ERROR] Failed to copy wp image: " << e.what() << std::endl;
        }
    }
}

std::string weapon::to_json() const
{
    std::ostringstream oss;

    oss << "  \"Weapon\": {\n";
    oss << "    \"name\": \"" << name << "\",\n";
    oss << "    \"image\": \"" << image_wp_filename << "\",\n";
    oss << "    \"equipment\": {\n";
    oss << "      \"one\": \"" << equipment.equipment_one << "\",\n";
    oss << "      \"two\": \"" << equipment.equipment_two << "\",\n";
    oss << "      \"three\": \"" << equipment.equipment_three << "\",\n";
    oss << "      \"unique\": \"" << equipment.unique_equipment << "\"\n";
    oss << "    },\n";
    oss << "    \"stats\": {\n";
    oss << "      \"atk\": " << _stats.atk << ",\n";
    oss << "      \"hp\": " << _stats.hp << ",\n";
    oss << "      \"healing\": " << _stats.healing << "\n";
    oss << "    }\n";
    oss << "  }";

    return oss.str();
}
