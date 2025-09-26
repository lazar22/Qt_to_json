//
// Created by roki on 2025-09-16.
//

#include "weapon_creation_tab.h"
#include <image_handler.h>
#include "file_names.h"
#include "weapon.h"

#include <QCoreApplication>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QFileDialog>
#include <QGroupBox>

weapon_creation_tab::weapon_creation_tab(QWidget* parent, const QString _file_path_)
    : QWidget(parent), _file_path(_file_path_)
{
    width = parent->width();
    height = parent->height();

    setup_ui();
    connect_signals();
}


void weapon_creation_tab::setup_ui()
{
    auto* main_layout = new QHBoxLayout();

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

    auto* right_panel = new QVBoxLayout();

    _character_selector.setParent(this);
    _character_selector.setMinimumWidth(200);
    _character_selector.setStyleSheet("QComboBox { font-size: 14px; }");
    _weapon_name_input.setParent(this);

    auto* connect_info = new QFormLayout();
    connect_info->addRow("Select Character:", &_character_selector);
    connect_info->addRow("Weapon Name:", &_weapon_name_input);
    right_panel->addLayout(connect_info);

    auto* boost_group = new QGroupBox(_group_name);
    boost_group->setStyleSheet("QGroupBox { font-weight: bold; }");
    auto* boost_form = new QFormLayout();

    boost_form->addRow("HP:", &_hp_boost_input);
    boost_form->addRow("ATK:", &_atk_boost_input);
    boost_form->addRow("HEALING:", &_healing_boost_input);

    boost_group->setLayout(boost_form);
    right_panel->addWidget(boost_group);

    // ADD ICONS
    auto* equipment_group = new QGroupBox("Equipment");
    equipment_group->setStyleSheet("QGroupBox { font-weight: bold; }");
    auto* equipment_layout = new QHBoxLayout();

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

    const QString character_folder_path = _file_path + CHARACTER_FOLDER + "/";
    load_character_list(character_folder_path);
}

void weapon_creation_tab::connect_signals()
{
    connect(&_image_label, &DragDropImgLabel::image_dropped, this, [this](const QString& path)
    {
        if (image_handler::load_image(&_image_label, path))
        {
            _image_path = path;
        }
    });

    connect(&_unique_equipment_image, &DragDropImgLabel::image_dropped, this, [this](const QString& path)
    {
        if (image_handler::load_image(&_unique_equipment_image, path))
        {
            _unique_equipment_path = path;
        }
    });

    // when submit btn press
    connect(&_submit_btn, &QPushButton::clicked, this, [this]()
    {
        qDebug() << "Submit";

        const QString selected_file = _character_selector.currentData().toString();
        full_path = _file_path + CHARACTER_FOLDER + "/" + selected_file;

        const int stats_hp_boost = _hp_boost_input.text().toInt();
        const int stats_atk_boost = _atk_boost_input.text().toInt();
        const int stats_healing = _healing_boost_input.text().toInt();

        const QString selected_one = _equipment_one_combo.currentData().toString();
        const QString selected_two = _equipment_two_combo.currentData().toString();
        const QString selected_three = _equipment_three_combo.currentData().toString();

        const QString wp_image_folder = _file_path + IMAGE_FOLDER + WEAPON_FOLDER;
        const QString equipment_image_folder = _file_path + IMAGE_FOLDER + EQUIPMENT_FOLDER;

        image_handler::create_file(wp_image_folder);

        weapon wp;
        wp.set_weapon_name(selected_file.toStdString(), _weapon_name_input.text().toStdString());
        wp.set_boost_stats(stats_hp_boost, stats_healing, stats_atk_boost);

        QString unique_equipment_dest_path;
        if (!_unique_equipment_path.isEmpty())
        {
            image_handler::create_file(equipment_image_folder);
            const QFileInfo use_info(_unique_equipment_path);
            const QString dest_path = equipment_image_folder + "/" + use_info.fileName();
            if (QFile::exists(dest_path))
            {
                QFile::remove(dest_path);
            }
            if (QFile::copy(_unique_equipment_path, dest_path))
            {
                unique_equipment_dest_path = dest_path;
            }
        }

        wp.set_upgrade_equipment(
            selected_one.toStdString(),
            selected_two.toStdString(),
            selected_three.toStdString(),
            unique_equipment_dest_path.toStdString());

        wp.set_weapon_image(_image_path.toStdString(), wp_image_folder.toStdString());

        wp.create_weapon(full_path.toStdString());
    });
}

void weapon_creation_tab::load_character_list(const QString& path)
{
    _character_selector.clear();

    const QDir dir(path);
    QStringList filters;
    filters << "*.json";
    QFileInfoList files = dir.entryInfoList(filters, QDir::Files, QDir::Name);

    if (files.isEmpty())
    {
        _character_selector.addItem("No characters found");
        _character_selector.setEnabled(false);
    }

    for (const QFileInfo& file_info : files)
    {
        QFile file(file_info.absoluteFilePath());

        if (!file.open(QIODevice::ReadOnly))
        {
            continue;
        }

        QByteArray data = file.readAll();
        file.close();

        QJsonParseError prase_error;
        QJsonDocument doc = QJsonDocument::fromJson(data, &prase_error);

        if (prase_error.error != QJsonParseError::NoError || !doc.isObject())
        {
            continue;
        }

        QJsonObject obj = doc.object();
        QString name = obj.value("name").toString();
        QString aftername = obj.value("aftername").toString();

        if (!name.isEmpty() && !aftername.isEmpty())
        {
            QString display_name = QString("%1 %2").arg(name).arg(aftername);
            QString key = file_info.fileName();
            _character_selector.addItem(display_name, key);
        }

        _character_selector.setEnabled(true);
    }
}

void weapon_creation_tab::_add_equipment_dropdown(QComboBox* combo, QHBoxLayout* layout, const QString& tooltip)
{
    combo->setMinimumWidth(64);
    combo->setIconSize(QSize(48, 48));
    combo->setToolTip(tooltip);

    layout->addWidget(combo);

    // Load icons
    const QString icon_dir = QCoreApplication::applicationDirPath() + "/character_upgrade_equipment";
    const QDir dir(icon_dir);
    const QStringList filters = {"*.png", "*.jpg", "*.jpeg"};
    QFileInfoList icons = dir.entryInfoList(filters, QDir::Files);

    for (const QFileInfo& icon : icons)
    {
        QIcon icon_img(icon.absoluteFilePath());
        QString name = icon.baseName(); // name without extension
        combo->addItem(icon_img, "", name); // Show only icon, use name as data
        combo->setItemData(combo->count() - 1, name, Qt::ToolTipRole);
    }
}

void weapon_creation_tab::refresh_character_list()
{
    const QString character_folder_path = _file_path + CHARACTER_FOLDER + "/";
    load_character_list(character_folder_path);
}

