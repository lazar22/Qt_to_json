//
// Created by roki on 2025-09-16.
//

#ifndef CHARACTER_CREATION_TAB_H
#define CHARACTER_CREATION_TAB_H

#pragma once

#include "dragdropimg.h"

#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QWidget>

#include "character.h"

class character_creation_tab final : public QWidget
{
    Q_OBJECT

    int width;
    int height;
    const int offset = 80;

private:
    QString _file_path;
    QString _image_path;

    DragDropImgLabel _image_label;

    QPushButton _submitBtn;

    QLineEdit _name_input;
    QLineEdit _aftername_input;

    QLineEdit _age_input;
    QLineEdit _height_input;

    // Stats
    QLineEdit _hp_input;
    QLineEdit _atk_input;
    QLineEdit _def_input;
    QLineEdit _healing_input;
    QLineEdit _accuracy_input;
    QLineEdit _evasion_input;
    QLineEdit _crit_input;
    QLineEdit _crit_res_input;
    QLineEdit _crit_dmg_input;
    QLineEdit _crit_dmg_res_input;
    QLineEdit _stability_input;
    QLineEdit _normal_att_range_input;
    QLineEdit _cc_power_input;
    QLineEdit _cc_res_input;
    QLineEdit _def_piercing_input;
    QLineEdit _mag_count_input;

    QComboBox _stars_combo;
    QComboBox _combat_class_combo;
    QComboBox _armor_class_combo;
    QComboBox _damage_class_combo;

    QComboBox _role_combo;
    QComboBox _type_combo;

    QComboBox street_combo;
    QComboBox outdoor_combo;
    QComboBox indoor_combo;

    QComboBox _school_combo;

public:
    explicit character_creation_tab(QWidget* parent = nullptr, const QString _file_path_ = "");

    ~character_creation_tab() override = default;

private:
    void setup_ui();

    void connect_signals();

    void create_stats_input_fields();

protected:
    static QStringList getCharacterCombatOptions()
    {
        return {"Striker", "Special"};
    }

    static QStringList getStarsOptions()
    {
        return {"★", "★★", "★★★"};
    }

    static QStringList getCharacterTypeOptions()
    {
        return {
            "Tank", "Attacker", "Healer",
            "Support", "Tactical Support"
        };
    }

    static QStringList getDefenseTypeOptions()
    {
        return {
            "Normal", "Light", "Heavy",
            "Special", "Elastic", "Structure"
        };
    }

    static QStringList get_attack_type_options()
    {
        return {
            "Normal", "Explosion", "Penetration",
            "Mystic", "Sonic", "Siege"
        };
    }

    static QStringList getSchoolOptions()
    {
        return {
            "Abydos High School",
            "Gehenna Academy",
            "Millennium Science School",
            "Trinity General School",
            "Hyakkikayo Alliance Academy",
            "Shanhaijing Senior Secondary School",
            "Red Winter Federal Academy",
            "Valkyrie Police Academy",
            "Arius Branch School",
            "SRT Special Academy",
            "Kronos School of Journalism",
            "Highlander Railroad Academy"
        };
    }

signals:
    void character_created();
};

#endif //CHARACTER_CREATION_TAB_H
