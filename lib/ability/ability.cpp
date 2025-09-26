//
// Created by Lazar on 9/26/2025.
//

#include "string_handler.h"
#include "ability.h"
#include "json_utils.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>


void ability::set_connected_character_name(const std::string& _connected_character_name)
{
    connected_character_name = _connected_character_name;
}

void ability::set_ability_cost(const int _ex_skill_cost)
{
    ex_skill_cost = _ex_skill_cost;
}

void ability::set_ability_descriptions(const std::string& _ex_skill_description,
                                       const std::string& _normal_skill_description,
                                       const std::string& _passive_skill_description,
                                       const std::string& _sub_skill_description)
{
    ex_skill_description = _ex_skill_description;
    normal_skill_description = _normal_skill_description;
    passive_skill_description = _passive_skill_description;
    sub_skill_description = _sub_skill_description;
}

void ability::set_ability_names(const std::string& _ex_skill_name,
                                const std::string& _normal_skill_name,
                                const std::string& _passive_skill_name,
                                const std::string& _sub_skill_name)
{
    ex_skill_name = _ex_skill_name;
    normal_skill_name = _normal_skill_name;
    passive_skill_name = _passive_skill_name;
    sub_skill_name = _sub_skill_name;
}

void ability::set_ability_image(const std::string& ability_name,
                                const std::string& _src_img_path,
                                const std::string& dest_folder)
{
    std::cout << "Copying ability image from " << _src_img_path << " to: " << dest_folder << std::endl;
    if (!_src_img_path.empty() && !dest_folder.empty())
    {
        const std::string new_ability_img_filename =
            string_handler::to_lower(string_handler::remove_file_extension(connected_character_name, ".json"))
            + "_" + string_handler::to_lower(ability_name) + ".png";
        const std::filesystem::path new_ability_img_path =
            std::filesystem::path(dest_folder) / new_ability_img_filename;

        try
        {
            std::filesystem::copy_file(_src_img_path, new_ability_img_path,
                                       std::filesystem::copy_options::overwrite_existing);
            if (skill_count < static_cast<int>(skill_filename.size()))
            {
                skill_filename[skill_count++] = (dest_folder + new_ability_img_filename);
            }
            else
            {
                std::cerr << "[WARN] Too many skills added; ignoring extra image.\n";
            }
        }
        catch (std::filesystem::filesystem_error& e)
        {
            std::cerr << "[ERROR] Failed to copy ability image: " << e.what() << std::endl;
        }
    }
}

void ability::create_ability(const std::string& _path) const
{
    if (!_path.empty())
    {
        const std::string new_block = to_json();
        std::string err;
        if (json_utils::replace_object_in_file(_path, "Ability", new_block, &err))
        {
            std::cerr << "[ERROR] " << err << "\n";
        }

        std::cout << "Ability block updated for " << connected_character_name << "\n";
    }
    else
    {
        std::cerr << "[ERROR] Path is empty.\n";
    }
}

std::string ability::to_json() const
{
    std::ostringstream oss;

    oss << " \"Ability\": {\n";
    oss << "    \"ex_skill\": {\n";
    oss << "    \"name\": " << "\"" << string_handler::remove_empty_places(ex_skill_name) << "\",\n";
    oss << "    \"description\": " << "\"" << ex_skill_description << "\",\n";
    oss << "    \"cost\": " << ex_skill_cost << ",\n";
    oss << "    \"image\": " << "\"" << skill_filename[0] << "\"" << "\n";
    oss << "    },\n";
    oss << "    \"normal_skill\": {\n";
    oss << "    \"name\": " << "\"" << string_handler::remove_empty_places(normal_skill_name) << "\",\n";
    oss << "    \"description\": " << "\"" << normal_skill_description << "\",\n";
    oss << "    \"image\": " << "\"" << skill_filename[1] << "\"" << "\n";
    oss << "    },\n";
    oss << "    \"passive_skill\": {\n";
    oss << "    \"name\": " << "\"" << string_handler::remove_empty_places(passive_skill_name) << "\",\n";
    oss << "    \"description\": " << "\"" << passive_skill_description << "\",\n";
    oss << "    \"image\": " << "\"" << skill_filename[2] << "\"" << "\n";
    oss << "    },\n";
    oss << "    \"sub_skill\": {\n";
    oss << "    \"name\": " << "\"" << string_handler::remove_empty_places(sub_skill_name) << "\",\n";
    oss << "    \"description\": " << "\"" << sub_skill_description << "\",\n";
    oss << "    \"image\": " << "\"" << skill_filename[3] << "\"" << "\n";
    oss << "    }\n";
    oss << "  }";

    return oss.str();
}
