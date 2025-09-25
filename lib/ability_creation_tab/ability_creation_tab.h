//
// Created by roki on 2025-09-25.
//

#ifndef ABILITY_CREATION_TAB_H
#define ABILITY_CREATION_TAB_H
#include <QWidget>

class ability_creation_tab final : public QWidget {
    Q_OBJECT

private:
    int width;
    int height;
    const int offset = 80;

    int icon_size = 64;

private:
    QString _file_path;

public:
    ability_creation_tab(QWidget *parent = nullptr, const QString _file_path_ = "")
        : QWidget(parent), _file_path(_file_path_) {
    }

    ~ability_creation_tab() override = default;
};

#endif //ABILITY_CREATION_TAB_H
