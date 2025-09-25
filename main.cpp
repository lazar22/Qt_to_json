//
// Created by roki on 2025-09-02.
//
#include <QApplication>
#include "window.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Configure QSettings defaults globally
    QCoreApplication::setOrganizationName("Blue Dragons");
    QCoreApplication::setOrganizationDomain("devlazar.com");
    QCoreApplication::setApplicationName("CharacterCreator");
    app_window w;
    w.show();

    return app.exec();
}
