//
// Created by roki on 2025-09-16.
//

#ifndef WEAPON_CREATION_TAB_H
#define WEAPON_CREATION_TAB_H

#pragma once

#include "dragdropimg.h"
#include "weapon.h"

#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QBoxLayout>
#include <QFile>

#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QWidget>

class weapon_creation_tab final : public QWidget {
    Q_OBJECT

private:
    int width;
    int height;
    int offset = 80;

    int icon_size = 64;

    QString _file_path;
    QString _image_path;
    QString _unique_equipment_path;

private:
    DragDropImgLabel _image_label;

    QPushButton _submit_btn;

    QComboBox _character_selector;

    QLineEdit _weapon_name_input;

    QString _group_name = "Weapon Stats(lvl 50)";
    QLineEdit _hp_boost_input;
    QLineEdit _atk_boost_input;
    QLineEdit _healing_boost_input;

    QComboBox _equipment_one_combo;
    QComboBox _equipment_two_combo;
    QComboBox _equipment_three_combo;

    DragDropImgLabel _unique_equipment_image;

public:
    explicit weapon_creation_tab(QWidget *parent = nullptr, const QString _file_path_ = "");

private:
    void setup_ui();

    void connect_signals();

    void load_character_list(const QString &path);

    static void _add_equipment_dropdown(QComboBox *combo, QHBoxLayout *layout, const QString &tooltip);

    void load_image(const QString &path);

public slots:
    void refresh_character_list();
};

#endif //WEAPON_CREATION_TAB_H
