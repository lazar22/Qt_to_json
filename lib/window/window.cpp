#include "window.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPixmap>
#include <QFileDialog>
#include <QDebug>

app_window::app_window(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Character Editor");
    setFixedSize(app_width, app_height);

    _central = new QWidget(this);
    setCentralWidget(_central);

    auto *mainLayout = new QHBoxLayout;

    // === Left: Character Image ===
    _imageLabel = new QLabel("Drop image here");
    _imageLabel->setFixedSize(app_width / 2, app_height - 20);
    _imageLabel->setStyleSheet("background-color: white; border: 1px solid gray;");
    _imageLabel->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(_imageLabel);

    // === Right: Character Info ===
    QVBoxLayout *rightPanel = new QVBoxLayout;

    _nameInput = new QLineEdit;
    _roleInput = new QLineEdit;
    _typeInput = new QLineEdit;
    _schoolInput = new QLineEdit;
    _weaponInput = new QLineEdit;

    QFormLayout *basicInfo = new QFormLayout;
    basicInfo->addRow("Name:", _nameInput);
    basicInfo->addRow("Role:", _roleInput);
    basicInfo->addRow("Type:", _typeInput);
    basicInfo->addRow("School:", _schoolInput);
    basicInfo->addRow("Weapon:", _weaponInput);

    rightPanel->addLayout(basicInfo);

    // === Stats Grid ===
    QGridLayout *statsGrid = new QGridLayout;

    _hpInput = new QLineEdit;
    _atkInput = new QLineEdit;
    _defInput = new QLineEdit;
    _critInput = new QLineEdit;
    _critDmgInput = new QLineEdit;
    _healingInput = new QLineEdit;

    const QStringList buffer = {"HP", "ATK", "DEF", "Crit", "CritDmg", "Healing"};
    QLineEdit *_buffer[6] = {_hpInput, _atkInput, _defInput, _critInput, _critDmgInput, _healingInput};
    for (int i = 0; i < buffer.size(); i++) {
        statsGrid->addWidget(new QLabel(buffer[i] + ":"), i, 0);
        statsGrid->addWidget(_buffer[i], i, 1);
    }

    rightPanel->addLayout(statsGrid);

    // === Submit Button ===
    _submitBtn = new QPushButton("Submit");
    rightPanel->addStretch();
    rightPanel->addWidget(_submitBtn, 0, Qt::AlignCenter);

    mainLayout->addLayout(rightPanel);
    _central->setLayout(mainLayout);

    // === Image Selection (temporary) ===
    // connect(_imageLabel, &QLabel::mousePressEvent, [this](QMouseEvent *) {
    //     QString file = QFileDialog::getOpenFileName(this, "Choose Character Image", "", "Images (*.png *.jpg *.jpeg)");
    //     if (!file.isEmpty()) {
    //         loadImage(file);
    //     }
    // });

    // === Debug Submit ===
    connect(_submitBtn, &QPushButton::clicked, this, [this]() {
        qDebug() << "Name:" << _nameInput->text();
        qDebug() << "HP:" << _hpInput->text();
        // etc...
    });
}

void app_window::loadImage(const QString &path) {
    QPixmap pix(path);
    if (!pix.isNull()) {
        _imageLabel->setPixmap(pix.scaled(_imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}
