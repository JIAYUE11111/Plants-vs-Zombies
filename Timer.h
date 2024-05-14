#ifndef PLANTS_VS_ZOMBIES_TIMEER_H
#define PLANTS_VS_ZOMBIES_TIMEER_H
#include <QEasingCurve>
#include <QtCore>

// Just for convenience
//定时器的父对象，超时时间，functor 为定时器超时时需要执行的函数。
class Timer: public QTimer
{
public:
    Timer(QObject *parent, int timeout, std::function<void(void)> functor);
};

class TimeLine: public QTimeLine
{
public:
    TimeLine(QObject *parent, int duration, int interval, std::function<void(qreal)> onChanged, std::function<void(void)> onFinished = [] {}, QEasingCurve shape = QEasingCurve::InOutSine);
};

#endif //PLANTS_VS_ZOMBIES_TIMEER_H
