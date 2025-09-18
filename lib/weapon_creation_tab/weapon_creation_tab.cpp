//
// Created by roki on 2025-09-16.
//

#include "weapon_creation_tab.h"

#include <QCoreApplication>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QFileDialog>
#include <QGroupBox>

weapon_creation_tab::weapon_creation_tab(QWidget *parent, const QString _file_path_)
    : QWidget(parent), _file_path(_file_path_) {
    width = parent->width();
    height = parent->height();

    setup_ui();
    connect_signals();
}


void weapon_creation_tab::setup_ui() {
    auto *main_layout = new QHBoxLayout();

    _image_label.setParent(this);
    _image_label.setText("Drop image here");
    _image_label.setFixedSize((width / 2), ((height / 2) - offset));
    _image_label.setStyleSheet(R"(
    QLabel {
        background-color: #2A2E3D;
        border: 2px dashed #3A3F51;
        border-radius: 10px;
        color: #888;
        font-size: 14px;
    }
)");
    _image_label.setAlignment(Qt::AlignCenter);
    main_layout->addWidget(&_image_label);

    connect(&_image_label, &DragDropImgLabel::image_dropped, this, [this](const QString &path) {
        load_image(path);
    });

    auto *right_panel = new QVBoxLayout();

    _character_selector.setParent(this);
    _character_selector.setMinimumWidth(200);
    _character_selector.setStyleSheet("QComboBox { font-size: 14px; }");
    _weapon_name_input.setParent(this);

    auto *connect_info = new QFormLayout();
    connect_info->addRow("Select Character:", &_character_selector);
    connect_info->addRow("Weapon Name:", &_weapon_name_input);
    right_panel->addLayout(connect_info);

    auto *boost_group = new QGroupBox(_group_name);
    boost_group->setStyleSheet("QGroupBox { font-weight: bold; }");
    auto *boost_form = new QFormLayout();

    boost_form->addRow("HP:", &_hp_boost_input);
    boost_form->addRow("ATK:", &_atk_boost_input);
    boost_form->addRow("HEALING:", &_healing_boost_input);

    boost_group->setLayout(boost_form);
    right_panel->addWidget(boost_group);

    // ADD ICONS
    auto *equipment_group = new QGroupBox("Equipment");
    equipment_group->setStyleSheet("QGroupBox { font-weight: bold; }");
    auto *equipment_layout = new QHBoxLayout();

    _add_equipment_dropdown(&_equipment_one_combo, equipment_layout, "Equipment 1");
    _add_equipment_dropdown(&_equipment_two_combo, equipment_layout, "Equipment 2");
    _add_equipment_dropdown(&_equipment_three_combo, equipment_layout, "Equipment 3");

    _unique_equipment_image.setParent(this);
    _unique_equipment_image.setFixedSize(icon_size, icon_size);
    _unique_equipment_image.setAlignment(Qt::AlignCenter);
    _unique_equipment_image.setStyleSheet(R"(
    QLabel {
        background-color: #2A2E3D;
        border: 2px dashed #3A3F51;
        border-radius: 10px;
        color: #888;
        font-size: 12px;
    }
)");
    _unique_equipment_image.setText("Drop image here");

    equipment_layout->addWidget(&_unique_equipment_image);
    equipment_group->setLayout(equipment_layout);
    right_panel->addWidget(equipment_group);


    _submit_btn.setParent(this);
    _submit_btn.setText("Submit");
    right_panel->addStretch();
    right_panel->addWidget(&_submit_btn, 0, Qt::AlignCenter);

    main_layout->addLayout(right_panel);
    this->setLayout(main_layout);

    QString character_folder_path = _file_path + "/";
    load_character_list(character_folder_path);
}

void weapon_creation_tab::connect_signals() {
    connect(&_unique_equipment_image, &DragDropImgLabel::image_dropped, this, [this](const QString &path) {
        QPixmap pix(path);
        _unique_equipment_image.setPixmap(pix.scaled(
            _unique_equipment_image.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        _unique_equipment_image.setText("");
        _unique_equipment_path = path;
    });

    // when submit btn press
    connect(&_submit_btn, &QPushButton::clicked, this, [this]() {
        qDebug() << "Submit";

        qDebug() << _character_selector.currentData().toString();
        qDebug() << _weapon_name_input.text();

        const QString selected_one = _equipment_one_combo.currentData().toString();
        const QString selected_two = _equipment_two_combo.currentData().toString();
        const QString selected_three = _equipment_three_combo.currentData().toString();


        qDebug() << selected_one;
        qDebug() << selected_two;
        qDebug() << selected_three;
    });
    // QString selected_file = _character_selector.currentData().toString();
    // full_path = _file_path + "/" + selected_file;
}

void weapon_creation_tab::load_character_list(const QString &path) {
    _character_selector.clear();

    const QDir dir(path);
    QStringList filters;
    filters << "*.json";
    QFileInfoList files = dir.entryInfoList(filters, QDir::Files, QDir::Name);

    if (files.isEmpty()) {
        _character_selector.addItem("No characters found");
        _character_selector.setEnabled(false);
    }

    for (const QFileInfo &file_info: files) {
        QFile file(file_info.absoluteFilePath());

        if (!file.open(QIODevice::ReadOnly)) {
            continue;
        }

        QByteArray data = file.readAll();
        file.close();

        QJsonParseError prase_error;
        QJsonDocument doc = QJsonDocument::fromJson(data, &prase_error);

        if (prase_error.error != QJsonParseError::NoError || !doc.isObject()) {
            continue;
        }

        QJsonObject obj = doc.object();
        QString name = obj.value("name").toString();
        QString aftername = obj.value("aftername").toString();

        if (!name.isEmpty() && !aftername.isEmpty()) {
            QString display_name = QString("%1 %2").arg(name).arg(aftername);
            QString key = file_info.fileName();
            _character_selector.addItem(display_name, key);
        }

        _character_selector.setEnabled(true);
    }
}

void weapon_creation_tab::_add_equipment_dropdown(QComboBox *combo, QHBoxLayout *layout, const QString &tooltip) {
    combo->setMinimumWidth(64);
    combo->setIconSize(QSize(48, 48));
    combo->setToolTip(tooltip);

    layout->addWidget(combo);

    // Load icons
    const QString icon_dir = QCoreApplication::applicationDirPath() + "/character_upgrade_equipment";
    const QDir dir(icon_dir);
    const QStringList filters = {"*.png", "*.jpg", "*.jpeg"};
    QFileInfoList icons = dir.entryInfoList(filters, QDir::Files);

    for (const QFileInfo &icon: icons) {
        QIcon icon_img(icon.absoluteFilePath());
        QString name = icon.baseName(); // name without extension
        combo->addItem(icon_img, "", name); // Show only icon, use name as data
        combo->setItemData(combo->count() - 1, name, Qt::ToolTipRole);
    }
}

void weapon_creation_tab::load_image(const QString &path) {
    QPixmap pix(path);
    if (!pix.isNull()) {
        _image_label.setText("");
        _image_label.setPixmap(pix.scaled(
            _image_label.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        _image_path = path;
    }
}

void weapon_creation_tab::refresh_character_list() {
    load_character_list(_file_path);
}
