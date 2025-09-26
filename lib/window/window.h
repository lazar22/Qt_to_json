//
// Created by roki on 2025-09-02.
//

#ifndef WINDOW_H
#define WINDOW_H

#include "character_creation_tab.h"
#include "event_character_creation_tab.h"
#include "ability_creation_tab.h"
#include "weapon_creation_tab.h"

#include <QMainWindow>
#include <QTabWidget>
#include <QSettings>


class app_window final : public QMainWindow
{
    int app_width = 1050;
    int app_height = 650;

private:
    QSettings _settings;
    QString _file_path;
    QComboBox* _file_path_combo;

    QTabWidget _tabs;

    character_creation_tab* _character_creation_tab;
    weapon_creation_tab* _weapon_creation_tab_;
    ability_creation_tab* _ability_creation_tab;

    event_character_creation_tab* _event_character_creation_tab;

private:
    void load_image(const QString& path);

    void save_file_path(const QString& path);

    void load_path_file();

public:
    void initialize_tabs();

    explicit app_window(QWidget* parent = nullptr);

    ~app_window() = default;
};

#endif //WINDOW_H
