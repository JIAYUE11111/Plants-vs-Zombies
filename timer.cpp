#include "timer.h"

Timer::Timer(QObject *parent, int timeout, std::function<void(void)> functor) : QTimer(parent)
{
    setInterval(timeout);
    if (timeout < 50)
        setTimerType(Qt::PreciseTimer);
    setSingleShot(true);
    connect(this, &Timer::timeout, [this, functor] { functor(); deleteLater(); });
}

//主要是动画效果
TimeLine::TimeLine(QObject *parent, int duration, int interval, std::function<void(qreal)> onChanged, std::function<void(void)> onFinished, QEasingCurve shape)
    : QTimeLine(duration, parent)
{
    /*
    if (duration == 0) {
        int i = 1;
        ++i;
    }*/
    setUpdateInterval(40);//时间线间隔为40ms
    setEasingCurve(shape);
    connect(this, &TimeLine::valueChanged, onChanged);
    connect(this, &TimeLine::finished, [this, onFinished] { onFinished(); deleteLater(); });
}
