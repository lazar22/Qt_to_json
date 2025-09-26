//
// Created by Lazar on 9/26/2025.
//

#ifndef ABILITY_H
#define ABILITY_H

#include <string>
#include <array>

class ability
{
    std::string connected_character_name;

    int ex_skill_cost{0};

    std::string ex_skill_description;
    std::string normal_skill_description;
    std::string passive_skill_description;
    std::string sub_skill_description;

    // Names for each skill (needed for JSON output)
    std::string ex_skill_name;
    std::string normal_skill_name;
    std::string passive_skill_name;
    std::string sub_skill_name;

    // Bounded storage for image filenames to avoid OOB writes
    std::array<std::string, 4> skill_filename{}; // ex, normal, passive, sub
    int skill_count = 0;

public:
    ability() = default;

    ~ability() = default;

public:
    void set_connected_character_name(const std::string& _connected_character_name);

    void set_ability_cost(const int _ex_skill_cost);

    void set_ability_names(const std::string& _ex_skill_name,
                           const std::string& _normal_skill_name,
                           const std::string& _passive_skill_name,
                           const std::string& _sub_skill_name);

    void set_ability_descriptions(const std::string& _ex_skill_description,
                                  const std::string& _normal_skill_description,
                                  const std::string& _passive_skill_description,
                                  const std::string& _sub_skill_description);

    void set_ability_image(const std::string& ability_name,
                           const std::string& _src_img_path,
                           const std::string& dest_folder);

    // Create/serialize ability data
    void create_ability(const std::string& _path) const;

private:
    std::string to_json() const;
};

#endif //ABILITY_H
