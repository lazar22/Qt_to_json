#include "window.h"
#include "character.h"

#include <QWidgetAction>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QFileDialog>
#include <QGroupBox>
#include <QMenuBar>
#include <QPixmap>
#include <QDebug>

app_window::app_window(QWidget *parent)
    : QMainWindow(parent), _settings("Blue Archive", "window") {
    setWindowTitle("Blue Archive Character Creator");
    setFixedSize(app_width, app_height);

    // add menus:
    auto *menu_bar = this->menuBar();
    auto *fill_menu = menu_bar->addMenu("File");

    _file_path_combo = new QComboBox(this);
    _file_path_combo->setFixedWidth(300);
    load_path_file();

    QAction *browse_action = new QAction("Browse...", this);
    fill_menu->addAction(browse_action);

    QWidgetAction *combo_action = new QWidgetAction(this);
    combo_action->setDefaultWidget(_file_path_combo);
    fill_menu->addAction(combo_action);

    // Dark Theam
    this->setStyleSheet(R"(
    QWidget {
        background-color: #1A1E2D;
        color: white;
        font-family: 'Segoe UI', 'Arial', sans-serif;
        font-size: 13px;
    }

    QLabel {
        color: white;
    }

    QLineEdit {
        background-color: #2A2E3D;
        color: white;
        border: 1px solid #3A3F51;
        border-radius: 4px;
        padding: 2px 4px;
        min-width: 50px;
    }

    QComboBox {
        background-color: #2A2E3D;
        color: white;
        border: 1px solid #3A3F51;
        border-radius: 4px;
        padding: 2px 4px;
        min-width: 80px;
    }

    QPushButton {
        background-color: #334;
        color: white;
        padding: 6px 12px;
        border-radius: 4px;
    }

    QPushButton:hover {
        background-color: #446;
    }
)");

    _central.setParent(this);
    setCentralWidget(&_central);

    // Must be heap-allocated
    auto *mainLayout = new QHBoxLayout;

    // Left Image
    _image_label.setParent(this);
    _image_label.setText("Drop image here");
    _image_label.setFixedSize(app_width / 2, app_height - 40);
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
    mainLayout->addWidget(&_image_label);

    connect(&_image_label, &DragDropImgLabel::image_dropped, this, [this](const QString &path) {
        load_image(path);
    });

    // === Right Panel ===
    auto *right_panel = new QVBoxLayout;

    _name_input.setParent(this);
    _aftername_input.setParent(this);
    _age_input.setParent(this);
    _height_input.setParent(this);

    _age_input.setFixedWidth(50);
    _height_input.setFixedWidth(50);

    auto *basic_info = new QFormLayout;
    basic_info->addRow("Name:", &_name_input);
    basic_info->addRow("Aftername:", &_aftername_input);
    right_panel->addLayout(basic_info);

    auto *basic_info_grid = new QGridLayout;
    basic_info_grid->addWidget(new QLabel("Age:"), 0, 0);
    basic_info_grid->addWidget(&_age_input, 0, 1);
    basic_info_grid->addWidget(new QLabel("Height:"), 0, 2);
    basic_info_grid->addWidget(&_height_input, 0, 3);
    right_panel->addLayout(basic_info_grid);

    // Dropdowns
    QComboBox *combos[] = {
        &_stars_combo, &_combat_class_combo,
        &_type_combo, &_damage_class_combo, &_armor_class_combo,
    };

    for (auto *combo: combos) {
        combo->setParent(this);
        combo->setFixedWidth(100);
    }

    _combat_class_combo.addItems(getCharacterCombatOptions());
    _stars_combo.addItems(getStarsOptions());
    _school_combo.addItems(getSchoolOptions());
    _type_combo.addItems(getCharacterTypeOptions());
    _damage_class_combo.addItems(get_attack_type_options());
    _armor_class_combo.addItems(getDefenseTypeOptions());

    auto *class_info_layout = new QGridLayout;
    class_info_layout->setSpacing(5);
    class_info_layout->addWidget(new QLabel("Stars:"), 0, 0);
    class_info_layout->addWidget(&_stars_combo, 0, 1);
    class_info_layout->addWidget(new QLabel("Combat Class:"), 0, 2);
    class_info_layout->addWidget(&_combat_class_combo, 0, 3);
    right_panel->addLayout(class_info_layout);

    auto *ch_type_layout = new QGridLayout;
    ch_type_layout->addWidget(new QLabel("Type:"), 0, 0);
    ch_type_layout->addWidget(&_type_combo, 0, 1);
    ch_type_layout->addWidget(new QLabel("Attack:"), 0, 2);
    ch_type_layout->addWidget(&_damage_class_combo, 0, 3);
    ch_type_layout->addWidget(new QLabel("Defense:"), 0, 4);
    ch_type_layout->addWidget(&_armor_class_combo, 0, 5);
    right_panel->addLayout(ch_type_layout);

    auto *school_layout = new QFormLayout;
    school_layout->addRow("School:", &_school_combo);
    right_panel->addLayout(school_layout);

    auto *terrain_layout = new QHBoxLayout;
    QStringList terrain_icons = {"🏙️", "⛰️", "🏠"};
    const QStringList face_options = {"😆", "😁", "😀", "😐", "😣", "😡"};

    QComboBox *terrainCombos[] = {
        &street_combo,
        &outdoor_combo,
        &indoor_combo
    };

    for (int i = 0; i < 3; ++i) {
        auto *vbox = new QVBoxLayout;

        QLabel *terrainIcon = new QLabel(terrain_icons[i]);
        terrainIcon->setAlignment(Qt::AlignCenter);
        terrainIcon->setStyleSheet("font-size: 35px;");
        vbox->addWidget(terrainIcon);

        QComboBox *combo = terrainCombos[i];
        combo->addItems(face_options);
        combo->setStyleSheet(R"(
        QComboBox {
            font-size: 30px;
            padding: 2px;
            border-radius: 6px;
            text-align: center;
            min-width: 50px;
        }
        QComboBox QAbstractItemView {
            font-size: 25px;
            text-align: center;
        }
        QComboBox::drop-down {
            width: 0px;
        }
    )");

        vbox->addWidget(combo, 0, Qt::AlignCenter);
        terrain_layout->addLayout(vbox);
    }

    right_panel->addLayout(terrain_layout);

    // Stats
    auto *stats_group = new QGroupBox("Character Stats");
    auto *stats_grid = new QGridLayout;

    stats_group->setLayout(stats_grid);
    stats_group->setStyleSheet("QGroupBox { font-weight: bold; margin-top: 10px; }");

    const QStringList buffer = {
        "HP", "ATK", "DEF", "Healing",
        "Accuracy", "Evasion", "Crit",
        "CritRes", "CritDmg", "CritDmgRes",
        "Stability", "NormalAttRange", "CCPower",
        "CCRes", "DefPiercing", "MagCount",
    };

    const QStringList icons = {
        "❤️", "⚔️", "🛡️", "✚",
        "🎯", "🕴️", "💥", "❌💥",
        "💣", "❌💣", "🧱", "📏",
        "🌀", "🛡️🌀", "💀🛡️", "🔫"
    };

    QLineEdit *_buffer[17] = {
        &_hp_input, &_atk_input, &_def_input, &_healing_input,
        &_accuracy_input, &_evasion_input, &_crit_input,
        &_crit_res_input, &_crit_dmg_input, &_crit_dmg_res_input,
        &_stability_input, &_normal_att_range_input, &_cc_power_input,
        &_cc_res_input, &_def_piercing_input, &_mag_count_input,
    };

    for (int i = 0; i < buffer.size(); i++) {
        const int row = i / 2;
        const int col = (i % 2) * 2;
        stats_grid->addWidget(new QLabel(icons[i] + " " + buffer[i] + ":"), row, col);
        stats_grid->addWidget(_buffer[i], row, col + 1);
    }

    right_panel->addWidget(stats_group);

    // Submit button
    _submitBtn.setParent(this);
    _submitBtn.setText("Submit");
    right_panel->addStretch();
    right_panel->addWidget(&_submitBtn, 0, Qt::AlignCenter);

    // Add to the main layout
    mainLayout->addLayout(right_panel);
    _central.setLayout(mainLayout);

    // Connect submit
    connect(&_submitBtn, &QPushButton::clicked, this, [this]() {
        character ch;
        ch.set_basic_info(_name_input.text().toStdString(), _aftername_input.text().toStdString(),
                          _age_input.text().toInt(), _height_input.text().toInt());

        ch.set_class_info(_stars_combo.currentIndex(), _combat_class_combo.currentIndex(),
                          _armor_class_combo.currentIndex(), _damage_class_combo.currentIndex());

        ch.set_terrain_compatability(street_combo.currentIndex(),
                                     outdoor_combo.currentIndex(),
                                     indoor_combo.currentIndex());

        ch.set_character_specification_info(_hp_input.text().toInt(), _atk_input.text().toInt(),
                                            _healing_input.text().toInt(), _accuracy_input.text().toInt(),
                                            _evasion_input.text().toInt(), _crit_input.text().toInt(),
                                            _crit_res_input.text().toInt(), _crit_dmg_input.text().toInt(),
                                            _crit_dmg_res_input.text().toInt(), _stability_input.text().toInt(),
                                            _normal_att_range_input.text().toInt(), _cc_power_input.text().toInt(),
                                            _cc_res_input.text().toInt(), _def_piercing_input.text().toInt(),
                                            _mag_count_input.text().toInt());

        ch.set_school(_school_combo.currentIndex());

        const QString images_folder = _file_path + "/Images";
        const QDir dir(images_folder);
        if (!dir.exists()) {
            dir.mkpath(".");
        }

        ch.set_image(_image_path.toStdString(), images_folder.toStdString());

        ch.create_character(_file_path.toStdString());
    });

    // Connect settings
    connect(browse_action, &QAction::triggered, this, [this]() {
        const QString path = QFileDialog::getExistingDirectory(
            this,
            "Select Character Output Folder",
            QString(),
            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );

        if (!path.isEmpty()) {
            if (_file_path_combo->findText(path) == -1) {
                _file_path_combo->addItem(path);
            }

            _file_path_combo->setCurrentText(path);
            _file_path = path;
            save_file_path(path);
        }
    });

    connect(_file_path_combo, &QComboBox::currentTextChanged, this, [this](const QString &text) {
        _file_path = text;
        save_file_path(text);
    });
}


void app_window::create_stats_input_fields() {
    QLineEdit *inputs[] = {
        &_hp_input, &_atk_input, &_def_input, &_healing_input,
        &_accuracy_input, &_evasion_input, &_crit_input,
        &_crit_res_input, &_crit_dmg_input, &_crit_dmg_res_input,
        &_stability_input, &_normal_att_range_input, &_cc_power_input,
        &_cc_res_input, &_def_piercing_input, &_mag_count_input,
    };

    const auto *validator = new QIntValidator(0, 999999, this);

    for (auto *input: inputs) {
        input->setParent(this);
        input->setValidator(validator);
        input->setAlignment(Qt::AlignRight);
    }
}

void app_window::load_image(const QString &path) {
    QPixmap pix(path);
    if (!pix.isNull()) {
        _image_label.setText("");
        _image_label.setPixmap(pix.scaled(
            _image_label.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        _image_path = path;
    }
}

void app_window::save_file_path(const QString &path) {
    _settings.setValue("lastFilePath", path);
}

void app_window::load_path_file() {
    QString last_path = _settings.value("lastFilePath").toString();
    if (!last_path.isEmpty()) {
        if (_file_path_combo->findText(last_path) == -1) {
            _file_path_combo->addItem(last_path);
        }
        _file_path_combo->setCurrentText(last_path);
        _file_path = last_path;
    }
}
