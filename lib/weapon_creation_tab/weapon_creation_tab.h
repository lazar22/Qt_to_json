//
// Created by roki on 2025-09-16.
//

#ifndef WEAPON_CREATION_TAB_H
#define WEAPON_CREATION_TAB_H

#pragma once

#include "dragdropimg.h"

#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
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

    QString _file_path;
    QString _image_path;

private:
    DragDropImgLabel _image_label;

    QPushButton _submit_btn;

    QComboBox _character_selector;

    QLineEdit _weapon_name_input;

public:
    explicit weapon_creation_tab(QWidget *parent = nullptr, const QString _file_path_ = "");

private:
    void setup_ui();

    void connect_signals();

    void load_character_list(const QString &path);

    void load_image(const QString &path);

public slots:
    void refresh_character_list();
};

#endif //WEAPON_CREATION_TAB_H
