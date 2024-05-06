#ifndef MAINSCENE_H
#define MAINSCENE_H
#include <QtWidgets>
#include <QtMultimedia>
//需要用到mouseeventspixmapitem中的类定义
class HoverChangedPixmapItem;
class MoviePixmapItem;
class MouseEventRectItem;


class TextItem: public QGraphicsTextItem
{
    Q_OBJECT

public:
    TextItem(const QString &text, QGraphicsItem *parent = nullptr);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};


class MainScene:public QGraphicsScene
{
    Q_OBJECT
public:
    MainScene();
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

private:
    //用于加载图片
    QGraphicsPixmapItem *background;
    QGraphicsPixmapItem *adventureShadow;
    QGraphicsPixmapItem *survivalShadow;
    QGraphicsPixmapItem *challengeShadow;
    QGraphicsPixmapItem *woodSign1;
    QGraphicsPixmapItem *woodSign2;
    QGraphicsPixmapItem *woodSign3;
    //处理鼠标悬停作用
    HoverChangedPixmapItem *adventureButton;
    HoverChangedPixmapItem *survivalButton;
    HoverChangedPixmapItem *challengeButton;
    //处理用户名
    TextItem *usernameText;
    //处理音乐
    QMediaPlayer *backgroundMusic;
    //处理鼠标音效
    QSoundEffect *effect;
    //处理动图
    MoviePixmapItem *zombieHand;
};

#endif // MAINSCENE_H
