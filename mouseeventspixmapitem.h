#ifndef MOUSEEVENTSPIXMAPITEM_H
#define MOUSEEVENTSPIXMAPITEM_H
#include<QtWidgets>
//QGraphicsSceneMouseEvent 用于处理图形场景中的鼠标事件
class MouseEventsPixmapItem:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    MouseEventsPixmapItem();
    MouseEventsPixmapItem(const QPixmap &image);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void mouseclicked(QGraphicsSceneMouseEvent *event);
    void hoverentered(QGraphicsSceneHoverEvent *event);
    void hovermoved(QGraphicsSceneHoverEvent *event);
    void hoverleft(QGraphicsSceneHoverEvent *event);
};
//继承上面的类
class HoverChangedPixmapItem: public MouseEventsPixmapItem
{
    Q_OBJECT
public:
    HoverChangedPixmapItem(const QPixmap &image);
private:
    QPixmap originImage;
    QPixmap hoverImage;
};

class MoviePixmapItem: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    MoviePixmapItem();
    MoviePixmapItem(const QString &filename);
    ~MoviePixmapItem();

    void setMovie(const QString &filename);
    void setMovieOnNewLoop(const QString &filename, std::function<void(void)> functor = [] {});

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void click(QGraphicsSceneMouseEvent *event);
    void loopStarted();
    void finished();

public slots:
    void start();
    void stop();
    void reset();

private:
    QMovie *movie;
};



#endif // MOUSEEVENTSPIXMAPITEM_H
