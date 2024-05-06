#include "aspectratiolayout.h"

//设置初值时，没有给item赋值
//item同时只可以有一个
AspectRatioLayout::AspectRatioLayout(QWidget *parent)
    : QLayout(parent), item(nullptr)
{}

AspectRatioLayout::~AspectRatioLayout()
{
    if (item)
        delete item;
}
//不会显示的调用
void AspectRatioLayout::addItem(QLayoutItem *item)
{

    qDebug()<<"additem used";
    if (this->item)
        qWarning("AspectRatioLayout: Attempting to add more items.");
    this->item = item;
}

QLayoutItem *AspectRatioLayout::itemAt(int index) const
{
    if (index == 0)
        return item;
    return nullptr;
}

//item拿走后清空为nullptr
QLayoutItem *AspectRatioLayout::takeAt(int index)
{
    if (index == 0) {
        QLayoutItem *temp = item;
        item = nullptr;
        return temp;
    }
    return nullptr;
}

int AspectRatioLayout::count() const
{
    if (item)
        return 1;
    return 0;
}

QSize AspectRatioLayout::minimumSize() const
{
    if (item)
        return item->minimumSize();
    return QSize();
}

QSize AspectRatioLayout::sizeHint() const
{
    if (item)
        return item->sizeHint();
    return QSize();
}

//父容器里更好的显示组件
void AspectRatioLayout::setGeometry(const QRect &rect) {

    QLayout::setGeometry(rect);
    qDebug()<<"setGeometry used!"<<rect.width()<<rect.height();
    if (!item) return;

    auto height = rect.height();

    QSize hint = item->sizeHint();
    qDebug()<<"hint:"<<hint.width()<<hint.height();
    qreal aspectRatio = 0;
    if (hint.width() && hint.height())
        aspectRatio = static_cast<qreal>(hint.width()) / hint.height();
    //计算最佳比例，并在希望设置的大小下最佳化
    auto currentWidth = qRound(rect.height() * aspectRatio);
    //考虑居中的方式
    if (currentWidth <= rect.width()) {
        int offset = (rect.width() - currentWidth) / 2;
        qDebug()<<"new item:"<<currentWidth<<rect.height();
        item->setGeometry(QRect(rect.x() + offset, rect.y(), currentWidth, rect.height()));
    } else {
        int currentHeight = qRound(rect.width() / aspectRatio);
        int offset = (height - currentHeight) / 2;
        item->setGeometry(QRect(rect.x(), rect.y() + offset, rect.width(), currentHeight));
        qDebug()<<"new item:"<<rect.width()<<currentHeight;
    }
}

Qt::Orientations AspectRatioLayout::expandingDirections() const
{
    return Qt::Orientations(0);
}

