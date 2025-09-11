//
// Created by roki on 2025-09-11.
//
#include "dragdropimg.h"

#include <QDropEvent>
#include <QFileInfo>
#include <QMimeData>
#include <QUrl>
#include <QLabel>

DragDropImgLabel::DragDropImgLabel(QWidget *parent) : QLabel(parent) {
    setAcceptDrops(true);
    _default_style = styleSheet();
}

void DragDropImgLabel::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        const QUrl url = event->mimeData()->urls().first();
        const QString filePath = url.toLocalFile();
        QFileInfo info(filePath);
        if (info.exists() && info.isFile()) {
            const QString ext = info.suffix().toLower();
            if (ext == "png" || ext == "jpg" || ext == "jpeg" || ext == "bmp") {
                setStyleSheet("border: 2px dashed #66ccff;");
                event->acceptProposedAction();
                return;
            }
        }
    }
    event->ignore();
}

void DragDropImgLabel::dragLeaveEvent(QDragLeaveEvent *event) {
    Q_UNUSED(event)
    setStyleSheet(_default_style);
}

void DragDropImgLabel::dropEvent(QDropEvent *event) {
    setStyleSheet(_default_style);
    if (event->mimeData()->hasUrls()) {
        const QString img_path = event->mimeData()->urls().first().toLocalFile();
        emit image_dropped(img_path);
        _img_path = img_path;
    }
}
