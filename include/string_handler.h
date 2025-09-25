//
// Created by roki on 2025-09-25.
//

#ifndef STRING_HANDLER_H
#define STRING_HANDLER_H

#include <string>
#include <algorithm>

namespace string_handler {
    inline std::string to_lower(const std::string &str) {
        std::string lower_str = str;
        std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
        return lower_str;
    }

    inline std::string remove_empty_places(const std::string &str) {
        std::string remove_str = str;
        std::replace(remove_str.begin(), remove_str.end(), ' ', '_');
        return remove_str;
    }

    inline std::string remove_file_extension(const std::string &str, const std::string &ext) {
        std::string remove_str = str;
        size_t pos = remove_str.rfind(ext);

        if (pos != std::string::npos && pos == remove_str.length() - ext.length()) {
            remove_str.erase(pos, ext.length());
        }

        return remove_str;
    }
};

#endif //STRING_HANDLER_H
