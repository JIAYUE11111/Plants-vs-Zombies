#ifndef TIMER_H
#define TIMER_H
#include <QtCore>
#include <QEasingCurve>
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

#endif // TIMER_H
