//
// Created by roki on 2025-09-11.
//

#ifndef DRAGDROPIMG_H
#define DRAGDROPIMG_H
#include <QLabel>

class DragDropImgLabel final : public QLabel {
    Q_OBJECT

private:
    QString _img_path;
    QString _default_style;

public:
    explicit DragDropImgLabel(QWidget *parent = nullptr);

signals:
    void image_dropped(const QString &path);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;

    void dragLeaveEvent(QDragLeaveEvent *event) override;

    void dropEvent(QDropEvent *event) override;
};

#endif //DRAGDROPIMG_H
