#include "mouseeventspixmapitem.h"

//有两种构造函数的方式方法
MouseEventsPixmapItem::MouseEventsPixmapItem()
{
    setAcceptHoverEvents(true);
}

MouseEventsPixmapItem::MouseEventsPixmapItem(const QPixmap &image) : QGraphicsPixmapItem(image)
{
    setAcceptHoverEvents(true);
}
//emit发送信号
void MouseEventsPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit mouseclicked(event);
}

void MouseEventsPixmapItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit hoverentered(event);
}

void MouseEventsPixmapItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    emit hovermoved(event);
}

void MouseEventsPixmapItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    emit hoverleft(event);
}

//对于悬停进行更为特别的处理
HoverChangedPixmapItem::HoverChangedPixmapItem(const QPixmap &image) :MouseEventsPixmapItem(), originImage(image.copy(0, 0, image.width(), image.height() / 2)),
    hoverImage(image.copy(0, image.height() / 2, image.width(), image.height() / 2))
{
    setPixmap(originImage);
    //setAcceptHoverEvents(true);
    connect(this, &HoverChangedPixmapItem::hoverentered,this,[this] { setPixmap(hoverImage); });
    connect(this, &HoverChangedPixmapItem::hoverleft,this,[this] { setPixmap(originImage); });
}

//处理gif
MoviePixmapItem::MoviePixmapItem(const QString &filename)
    : movie(nullptr)
{
    setMovie(filename);
}

MoviePixmapItem::MoviePixmapItem()
    : movie(nullptr)
{}

MoviePixmapItem::~MoviePixmapItem()
{
    if (movie) {
        if (movie->state() == QMovie::Running)
            movie->stop();
        delete movie;
    }
}

void MoviePixmapItem::setMovie(const QString &filename)
{
    if (movie) {
        movie->stop();
        delete movie;
    }
    movie = new QMovie(":/images/" + filename);
    movie->jumpToFrame(0);
    setPixmap(movie->currentPixmap());
    connect(movie, &QMovie::frameChanged,this,[this](int i){
        setPixmap(movie->currentPixmap());
        if (i == 0)
            emit loopStarted();
    });
    connect(movie, &QMovie::finished,this,[this]{ emit finished(); });
}

void MoviePixmapItem::start()
{
    movie->start();
}

void MoviePixmapItem::stop()
{
    movie->stop();
}

void MoviePixmapItem::reset()
{
    movie->jumpToFrame(0);
}

void MoviePixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit click(event);
}

void MoviePixmapItem::setMovieOnNewLoop(const QString &filename, std::function<void(void)> functor)
{
    QSharedPointer<QMetaObject::Connection> connection(new QMetaObject::Connection);
    *connection = QObject::connect(this, &MoviePixmapItem::loopStarted, [this, connection, filename, functor] {
        setMovie(filename);
        QObject::disconnect(*connection);
        start();
        functor();
    });
}
