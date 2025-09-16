#include "window.h"

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

    _tabs.setParent(this);
    setCentralWidget(&_tabs);

    _character_creation_tab = new character_creation_tab(this, _file_path);

    _tabs.addTab(_character_creation_tab, "Character Creation");

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
