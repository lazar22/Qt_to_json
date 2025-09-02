//
// Created by roki on 2025-09-02.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class app_window final : public QMainWindow {
    int app_width = 1000;
    int app_height = 600;

private:
    QWidget *_central;

    QLabel *_imageLabel;
    QPushButton *_submitBtn;

    QLineEdit *_nameInput;
    QLineEdit *_roleInput;
    QLineEdit *_typeInput;
    QLineEdit *_schoolInput;

    QLineEdit *_weaponInput;

    // Stats
    QLineEdit *_hpInput;
    QLineEdit *_atkInput;
    QLineEdit *_defInput;
    QLineEdit *_critInput;
    QLineEdit *_critDmgInput;
    QLineEdit *_healingInput;

    void loadImage(const QString &path);

public:
    explicit app_window(QWidget *parent = nullptr);

    ~app_window() = default;
};

#endif //WINDOW_H
