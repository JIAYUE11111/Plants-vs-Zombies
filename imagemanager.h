#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QtGui>

class ImageManager
{
private:
    QMap<QString,QPixmap> pixmaps;
public:
    QPixmap load(const QString &path);
};

extern ImageManager *ImageCache;

void InitImageManager();
void DestoryImageManager();
#endif // IMAGEMANAGER_H
