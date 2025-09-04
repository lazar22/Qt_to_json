#include "window.h"
#include "character.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QPixmap>
#include <QFileDialog>
#include <QDebug>

app_window::app_window(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Character Editor");
    setFixedSize(app_width, app_height);

    _central.setParent(this);
    setCentralWidget(&_central);

    // Must be heap-allocated
    auto *mainLayout = new QHBoxLayout;

    // Left Image
    _imageLabel.setParent(this);
    _imageLabel.setText("Drop image here");
    _imageLabel.setFixedSize(app_width / 2, app_height - 20);
    _imageLabel.setStyleSheet("background-color: white; border: 1px solid gray;");
    _imageLabel.setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(&_imageLabel);

    // === Right Panel ===
    auto *right_panel = new QVBoxLayout;

    _name_input.setParent(this);
    _aftername_input.setParent(this);
    _age_input.setParent(this);
    _height_input.setParent(this);

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
    _combat_class_combo.setParent(this);
    _combat_class_combo.addItems(getCharacterCombatOptions());

    _stars_combo.setParent(this);
    _stars_combo.addItems(getStarsOptions());

    _school_combo.setParent(this);
    _school_combo.addItems(getSchoolOptions());

    auto *class_info_layout = new QGridLayout;
    class_info_layout->addWidget(new QLabel("Stars:"), 0, 0);
    class_info_layout->addWidget(&_stars_combo, 0, 1);
    class_info_layout->addWidget(new QLabel("Combat Class:"), 0, 2);
    class_info_layout->addWidget(&_combat_class_combo, 0, 3);
    right_panel->addLayout(class_info_layout);

    auto *school_layout = new QFormLayout;
    school_layout->addRow("School:", &_school_combo);
    right_panel->addLayout(school_layout);

    // Stats
    create_stats_input_fields();
    auto *stats_grid = new QGridLayout;

    const QStringList buffer = {
        "HP", "ATK", "DEF", "Healing",
        "Accuracy", "Evasion", "Crit",
        "CritRes", "CritDmg", "CritDmgRes",
        "Stability", "NormalAttRange", "CCPower",
        "CCRes", "DefPiercing", "MagCount",
    };

    QLineEdit *_buffer[17] = {
        &_hp_input, &_atk_input, &_def_input, &_healing_input,
        &_accuracy_input, &_evasion_input, &_crit_input,
        &_crit_res_input, &_crit_dmg_input, &_crit_dmg_res_input,
        &_stability_input, &_normal_att_range_input, &_cc_power_input,
        &_cc_res_input, &_def_piercing_input, &_mag_count_input,
    };

    for (int i = 0; i < buffer.size(); i++) {
        int row = i / 2;
        int col = (i % 2) * 2;
        stats_grid->addWidget(new QLabel(buffer[i] + ":"), row, col);
        stats_grid->addWidget(_buffer[i], row, col + 1);
    }
    right_panel->addLayout(stats_grid);

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
        qDebug() << "Name:" << _name_input.text();
        qDebug() << "HP:" << _hp_input.text();
    });
}


void app_window::create_stats_input_fields() {
    _hp_input.setParent(this);
    _atk_input.setParent(this);
    _def_input.setParent(this);
    _crit_input.setParent(this);
    _crit_dmg_input.setParent(this);
    _healing_input.setParent(this);
    _accuracy_input.setParent(this);
    _evasion_input.setParent(this);
    _crit_res_input.setParent(this);
    _crit_dmg_res_input.setParent(this);
    _stability_input.setParent(this);
    _normal_att_range_input.setParent(this);
    _cc_power_input.setParent(this);
    _cc_res_input.setParent(this);
    _def_piercing_input.setParent(this);
    _mag_count_input.setParent(this);
}

void app_window::loadImage(const QString &path) {
    QPixmap pix(path);
    if (!pix.isNull()) {
        _imageLabel.setPixmap(pix.scaled(_imageLabel.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}
