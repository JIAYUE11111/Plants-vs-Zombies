#ifndef ANIMATE_H
#define ANIMATE_H

#include <QtWidgets>

class Animate
{
public:
    Animate(QGraphicsItem *item, QGraphicsScene *scene);

    Animate &move(QPointF toPos);
    Animate &scale(qreal toScale);
    Animate &fade(qreal toOpacity);

    Animate &replace();
    Animate &shape(QEasingCurve shape);
    Animate &speed(qreal speed);
    Animate &duration(int duration);

    Animate &finish(std::function<void(void)> functor);
    Animate &finish(std::function<void(bool)> functor = [](bool) {});

protected:
    enum KeyFrameType { MOVE = 0x01, SCALE = 0x02, FADE = 0x04, REPLACE = 0x08};
    struct KeyFrame {
        int type;
        int duration;
        qreal speed; // if duration == 0, speed is used
        QPointF toPos;
        qreal toScale, toOpacity;
        std::function<void(bool)> finished;
        QEasingCurve  shape;
    };
    struct Animation {
        QTimeLine *anim;
        QGraphicsScene *scene;
        QList<KeyFrame> frames;
    };
    static Animation *getAnimation(QGraphicsItem *item);
    static void setAnimation(QGraphicsItem *item, Animation *animation);
    static void generateAnimation(QGraphicsItem *item);

private:
    static const int AnimationKey;

    int type;
    int m_duration;
    qreal m_speed;
    QPointF toPos;
    qreal toScale, toOpacity;
    QEasingCurve m_shape;

    QGraphicsItem *item;
    QGraphicsScene *scene;
};


#endif // ANIMATE_H