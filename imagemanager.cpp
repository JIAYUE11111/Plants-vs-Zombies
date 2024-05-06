#include "imagemanager.h"

//QPixmap(const char *const[] xpm)
//将路径和加载图片的Qpixmap对应

ImageManager *ImageCache;

QPixmap ImageManager::load(const QString &path)
{
    if(pixmaps.find(path)==pixmaps.end())
    {
        pixmaps.insert(path,QPixmap(":/images/"+path));
    }
    return pixmaps[path];
}



void InitImageManager()
{
    ImageCache=new ImageManager;
}

void DestoryImageManager()
{
    delete ImageCache;
}
