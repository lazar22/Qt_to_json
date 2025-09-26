#pragma once

#include <string>
#include <fstream>
#include <sstream>

#include <QJsonObject>
#include <QComboBox>
#include <QDir>

namespace json_utils
{
    inline size_t find_matching_closing_brace(const std::string& s, size_t open_pos)
    {
        int depth = 0;
        bool in_string = false;
        bool escape = false;

        for (size_t i = open_pos; i < s.size(); ++i)
        {
            char c = s[i];

            if (in_string)
            {
                if (escape)
                {
                    escape = false;
                }
                else if (c == '\\')
                {
                    escape = true;
                }
                else if (c == '"')
                {
                    in_string = false;
                }
                continue;
            }

            if (c == '"')
            {
                in_string = true;
                continue;
            }
            if (c == '{')
            {
                depth++;
            }
            else if (c == '}')
            {
                depth--;
                if (depth == 0)
                {
                    return i;
                }
            }
        }
        return std::string::npos;
    }

    inline bool replace_object_in_file(const std::string& file_path,
                                       const std::string& key_name,
                                       const std::string& new_object_block,
                                       std::string* error = nullptr)
    {
        std::ifstream in(file_path);
        if (!in.is_open())
        {
            if (error) *error = "Failed to open file for reading: " + file_path;
            return false;
        }
        std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        in.close();

        const std::string key = "\"" + key_name + "\":";
        const size_t key_pos = content.find(key);
        if (key_pos == std::string::npos)
        {
            if (error) *error = "Key not found: " + key_name;
            return false;
        }

        const size_t open_brace = content.find('{', key_pos + key.size());
        if (open_brace == std::string::npos)
        {
            if (error) *error = "Opening brace not found for key: " + key_name;
            return false;
        }

        const size_t close_brace = find_matching_closing_brace(content, open_brace);
        if (close_brace == std::string::npos)
        {
            if (error) *error = "Matching closing brace not found for key: " + key_name;
            return false;
        }

        const std::string before = content.substr(0, key_pos);
        const std::string after = content.substr(close_brace + 1);
        const std::string updated = before + new_object_block + after;

        std::ofstream out(file_path);
        if (!out.is_open())
        {
            if (error) *error = "Failed to open file for writing: " + file_path;
            return false;
        }
        out << updated;
        out.close();
        return true;
    }

    static std::string json_escape(const std::string& in)
    {
        std::string out;
        out.reserve(in.size() + 16);
        for (unsigned char c : in)
        {
            switch (c)
            {
            case '\"': out += "\\\"";
                break;
            case '\\': out += "\\\\";
                break;
            case '\b': out += "\\b";
                break;
            case '\f': out += "\\f";
                break;
            case '\n': out += "\\n";
                break;
            case '\r': out += "\\r";
                break;
            case '\t': out += "\\t";
                break;
            default:
                if (c < 0x20)
                {
                    char buf[7];
                    std::snprintf(buf, sizeof(buf), "\\u%04X", c);
                    out += buf;
                }
                else
                {
                    out += static_cast<char>(c);
                }
            }
        }
        return out;
    }

    inline void populate_character_combo(QComboBox* combo, const QString& dirPath)
    {
        if (!combo) return;

        combo->clear();

        const QDir dir(dirPath);
        const QStringList filters = {"*.json"};
        const QFileInfoList files = dir.entryInfoList(filters, QDir::Files, QDir::Name);

        if (files.isEmpty())
        {
            combo->addItem("No characters found");
            combo->setEnabled(false);
            return;
        }

        for (const QFileInfo& file_info : files)
        {
            QFile file(file_info.absoluteFilePath());
            if (!file.open(QIODevice::ReadOnly))
            {
                continue;
            }

            const QByteArray data = file.readAll();
            file.close();

            QJsonParseError parse_error;
            const QJsonDocument doc = QJsonDocument::fromJson(data, &parse_error);

            if (parse_error.error != QJsonParseError::NoError || !doc.isObject())
            {
                continue;
            }

            const QJsonObject obj = doc.object();
            const QString name = obj.value("name").toString();
            const QString aftername = obj.value("aftername").toString();

            if (!name.isEmpty() && !aftername.isEmpty())
            {
                const QString display_name = QString("%1 %2").arg(name, aftername);
                const QString key = file_info.fileName();
                combo->addItem(display_name, key);
            }
        }

        combo->setEnabled(combo->count() > 0);
    }
}
