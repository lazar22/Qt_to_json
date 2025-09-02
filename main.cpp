//
// Created by roki on 2025-09-02.
//
#include <QApplication>
#include "window.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    window w;
    w.show();

    return app.exec();
}
