//
// Created by roki on 2025-09-02.
//

#ifndef WINDOW_H
#define WINDOW_H

#include "character_creation_tab.h"

#include <QMainWindow>
#include <QTabWidget>
#include <QSettings>

class app_window final : public QMainWindow {
    int app_width = 950;
    int app_height = 600;

private:
    QSettings _settings;
    QString _file_path;
    QComboBox *_file_path_combo;

    QTabWidget _tabs;
    character_creation_tab *_character_creation_tab;

private:
    void load_image(const QString &path);

    void save_file_path(const QString &path);

    void load_path_file();

public:
    explicit app_window(QWidget *parent = nullptr);

    ~app_window() = default;
};

#endif //WINDOW_H
