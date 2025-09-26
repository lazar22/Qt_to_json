//
// Created by roki on 2025-09-25.
//

#ifndef ABILITY_CREATION_TAB_H
#define ABILITY_CREATION_TAB_H

#include <qboxlayout.h>

#include "dragdropimg.h"

#include <QPlainTextEdit>
#include <QJsonObject>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QDir>

class ability_creation_tab final : public QWidget
{
    Q_OBJECT

private:
    int width;
    int height;
    const int offset = 80;

    int icon_size = 64;
    int description_box_min_h = 150;

private:
    QString _file_path;
    QString _full_path;

    QString _image_ex_path;
    QString _image_normal_path;
    QString _image_passive_path;
    QString _image_sub_path;


    QComboBox _character_selector;

    DragDropImgLabel ex_skill;
    QLineEdit ex_name;
    QLineEdit ex_cost;
    QPlainTextEdit ex_description;

    DragDropImgLabel normal_skill;
    QLineEdit normal_skill_name;
    QPlainTextEdit normal_skill_description;

    DragDropImgLabel passive_skill;
    QLineEdit passive_skill_name;
    QPlainTextEdit passive_skill_description;

    DragDropImgLabel sub_skill;
    QLineEdit sub_skill_name;
    QPlainTextEdit sub_skill_description;

    QPushButton _submit_btn;

private:
    void setup_ui();

    void connect_signals();

    void load_character_list(const QString& path);

    void setup_skills_gui(QVBoxLayout* main_layout);

public:
    explicit ability_creation_tab(QWidget* parent = nullptr, const QString& _file_path_ = "");

    ~ability_creation_tab() override = default;

public slots :
    void refresh_character_list();
};

#endif //ABILITY_CREATION_TAB_H
