//
// Created by Lazar on 9/26/2025.
//

#ifndef IMAGE_HANDLER_H
#define IMAGE_HANDLER_H

#include "dragdropimg.h"

#include <QString>
#include <QPixmap>

namespace image_handler
{
    inline bool load_image(DragDropImgLabel* label, const QString& path)
    {
        bool status{false};

        QPixmap pixmap(path);
        if (!pixmap.isNull())
        {
            label->setText("");
            label->setPixmap(pixmap.scaled(
                label->size(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation
            ));

            status = true;
        }

        return status;
    }

    inline bool create_file(const QString& path)
    {
        const QDir dir(path);

        return dir.exists() || dir.mkpath(".");
    }
}

#endif //IMAGE_HANDLER_H
