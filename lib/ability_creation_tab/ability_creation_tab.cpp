//
// Created by roki on 2025-09-25.
//
#include "ability_creation_tab.h"
#include "ability.h"

#include "image_handler.h"
#include "file_names.h"

#include <QCoreApplication>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QFileDialog>
#include <QGroupBox>
#include <QTextOption>

ability_creation_tab::ability_creation_tab(QWidget* parent, const QString& _file_path_)
    : QWidget(parent), _file_path(_file_path_)
{
    width = parent->width();
    height = parent->height();

    setup_ui();
    connect_signals();
}

void ability_creation_tab::setup_ui()
{
    auto* main_layout = new QVBoxLayout();

    // Apply common input style (matches rest of GUI)
    this->setStyleSheet(R"(
        QComboBox { font-size: 14px; }
        QLineEdit, QPlainTextEdit {
            background-color: #1F2432;
            border: 1px solid #3A3F51;
            border-radius: 6px;
            color: #EEE;
            font-size: 14px;
            padding: 6px;
        }
        QLineEdit:focus, QPlainTextEdit:focus {
            border: 1px solid #66ccff;
        }
        QGroupBox { font-weight: bold; }
    )");

    auto* connect_info = new QFormLayout;
    connect_info->addRow("Select Character:", &_character_selector);
    main_layout->addLayout(connect_info);

    setup_skills_gui(main_layout);

    _submit_btn.setParent(this);
    _submit_btn.setText("Submit");
    main_layout->addWidget(&_submit_btn);

    setLayout(main_layout);

    const QString character_folder_path = _file_path + CHARACTER_FOLDER + "/";
    load_character_list(character_folder_path);
}

void ability_creation_tab::setup_skills_gui(QVBoxLayout* main_layout)
{
    auto* skill_group = new QGroupBox("Skills");
    skill_group->setStyleSheet("QGroupBox { font-weight: bold; }");
    auto* skills_layout = new QHBoxLayout();

    // EX SKILL
    {
        auto* vbox = new QVBoxLayout();

        ex_skill.setParent(this);
        ex_skill.setText("Drop image here");
        ex_skill.setAlignment(Qt::AlignCenter);
        ex_skill.setFixedSize(icon_size * 2, icon_size * 2); // make icon bigger
        ex_skill.setStyleSheet(R"(
            QLabel {
                background-color: #2A2E3D;
                border: 2px dashed #3A3F51;
                border-radius: 10px;
                color: #888;
                font-size: 14px;
            }
        )");
        vbox->addWidget(&ex_skill, 0, Qt::AlignCenter);

        ex_name.setParent(this);
        ex_name.setPlaceholderText("EX Skill Name");
        vbox->addWidget(&ex_name);

        ex_cost.setParent(this);
        ex_cost.setPlaceholderText("Cost");
        vbox->addWidget(&ex_cost);

        ex_description.setParent(this);
        ex_description.setPlaceholderText("Description");
        ex_description.setMinimumHeight(description_box_min_h);
        ex_description.setLineWrapMode(QPlainTextEdit::WidgetWidth);
        ex_description.setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        vbox->addWidget(&ex_description);

        skills_layout->addLayout(vbox);
    }


    // NORMAL, PASSIVE, SUB SKILLS
    for (auto [skill_img, skill_name, skill_desc] : {
             std::tuple<DragDropImgLabel*, QLineEdit*, QPlainTextEdit*>(
                 &normal_skill, &normal_skill_name, &normal_skill_description),
             std::tuple<DragDropImgLabel*, QLineEdit*, QPlainTextEdit*>(
                 &passive_skill, &passive_skill_name, &passive_skill_description),
             std::tuple<DragDropImgLabel*, QLineEdit*, QPlainTextEdit*>(
                 &sub_skill, &sub_skill_name, &sub_skill_description)
         })
    {
        auto* vbox = new QVBoxLayout();

        skill_img->setParent(this);
        skill_img->setText("Drop image here");
        skill_img->setAlignment(Qt::AlignCenter);
        skill_img->setFixedSize(icon_size * 2, icon_size * 2);
        skill_img->setStyleSheet(R"(
            QLabel {
                background-color: #2A2E3D;
                border: 2px dashed #3A3F51;
                border-radius: 10px;
                color: #888;
                font-size: 14px;
                margin: 0px;
                padding: 0px;
            }
        )");
        vbox->addWidget(skill_img, 0, Qt::AlignCenter);

        skill_name->setParent(this);
        skill_name->setPlaceholderText("Skill Name");
        vbox->addWidget(skill_name);

        skill_desc->setParent(this);
        skill_desc->setPlaceholderText("Description");
        skill_desc->setMinimumHeight(description_box_min_h);
        skill_desc->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        skill_desc->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        vbox->addWidget(skill_desc);

        skills_layout->addLayout(vbox);
    }

    skill_group->setLayout(skills_layout);
    main_layout->addWidget(skill_group);
}

void ability_creation_tab::connect_signals()
{
    connect(&ex_skill, &DragDropImgLabel::image_dropped, this, [this](const QString& path)
    {
        if (image_handler::load_image(&ex_skill, path))
        {
            _image_ex_path = path;
        }
    });

    connect(&normal_skill, &DragDropImgLabel::image_dropped, this, [this](const QString& path)
    {
        if (image_handler::load_image(&normal_skill, path))
        {
            _image_normal_path = path;
        }
    });

    connect(&passive_skill, &DragDropImgLabel::image_dropped, this, [this](const QString& path)
    {
        if (image_handler::load_image(&passive_skill, path))
        {
            _image_passive_path = path;
        }
    });

    connect(&sub_skill, &DragDropImgLabel::image_dropped, this, [this](const QString& path)
    {
        if (image_handler::load_image(&sub_skill, path))
        {
            _image_sub_path = path;
        }
    });

    connect(&_submit_btn, &QPushButton::clicked, this, [this]()
    {
        qDebug() << "Submit";

        const QString selected_file = _character_selector.currentData().toString();
        _full_path = _file_path + CHARACTER_FOLDER + "/" + selected_file;

        ability ab;

        ab.set_connected_character_name(selected_file.toStdString());
        ab.set_ability_cost(ex_cost.text().toInt());

        ab.set_ability_names(ex_name.text().toStdString(),
                             normal_skill_name.text().toStdString(),
                             passive_skill_name.text().toStdString(),
                             sub_skill_name.text().toStdString());

        ab.set_ability_descriptions(ex_description.toPlainText().toStdString(),
                                    normal_skill_description.toPlainText().toStdString(),
                                    passive_skill_description.toPlainText().toStdString(),
                                    sub_skill_description.toPlainText().toStdString());

        const QString ability_image_folder = _file_path + IMAGE_FOLDER + ABILITY_FOLDER + "/";
        image_handler::create_file(ability_image_folder);

        ab.set_ability_image(ex_name.text().toStdString(),
                             _image_ex_path.toStdString(),
                             ability_image_folder.toStdString());

        ab.set_ability_image(normal_skill_name.text().toStdString(),
                             _image_normal_path.toStdString(),
                             ability_image_folder.toStdString());

        ab.set_ability_image(passive_skill_name.text().toStdString(),
                             _image_passive_path.toStdString(),
                             ability_image_folder.toStdString());

        ab.set_ability_image(sub_skill_name.text().toStdString(),
                             _image_sub_path.toStdString(),
                             ability_image_folder.toStdString());

        ab.create_ability(_full_path.toStdString());
        qDebug() << _full_path;
    });
}

void ability_creation_tab::load_character_list(const QString& path)
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

void ability_creation_tab::refresh_character_list()
{
    const QString character_folder_path = _file_path + CHARACTER_FOLDER + "/";
    load_character_list(character_folder_path);
}
