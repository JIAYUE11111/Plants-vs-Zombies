#include "mainwindow.h"
#include "AspectRatioLayout.h"

#include <QSettings>
MainView *gMainView;
//初始化列表的方式用于构造函数
/*    const int wid,high;
    const QString usernameSettingEntry;
    MainWindow *mainWindow;*/
MainView::MainView(MainWindow *mainWindow)
    :wid(900),high(600),usernameSettingEntry("Global/Username"),
    mainWindow(mainWindow)
{
    gMainView=this;
    setMouseTracking(true);//即使没有按下鼠标也会进行鼠标跟踪

    setRenderHint(QPainter::Antialiasing, true);//启用抗锯齿渲染。这影响绘制在控件上的图形和文本的质量，使边缘看起来更平
    setRenderHint(QPainter::TextAntialiasing, true);//启用文本抗锯齿渲染，以改善文本的显示质量
    setRenderHint(QPainter::SmoothPixmapTransform, true);//启用平滑的像素图转换。当对图像进行缩放或旋转等操作时，这会提高图像的渲染质量。
    setFrameStyle(0);//设置控件的框架样式。数字0通常表示没有框架。
    //没有滚动条的存在
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setMinimumSize(wid, high);
    //设置用户姓名
    if (getUsername().isEmpty()) {
        QString username = qgetenv("USER"); // Linux or Mac
        if (username.isEmpty())
            username = qgetenv("USERNAME"); // Windows
        if (username.isEmpty())
            username = tr("Guest");
        SetUsername(username);

    }
    qDebug()<<getUsername();
}

//如果场景还在则消除
MainView::~MainView()
{
    if (scene())
        scene()->deleteLater();
}
//获得键值对
QString MainView::getUsername() const
{
    return QSettings().value(usernameSettingEntry, "").toString();
}

void MainView::SetUsername(const QString &username)
{
    return QSettings().setValue(usernameSettingEntry, username);
}

MainWindow *MainView::getMainWindow() const
{
    return mainWindow;
}
//用于实现场景切换，如果当前mainview有场景，我们则把现在场景设成旧场景
//把新的场景设置成需要使用的场景
//如果确实有旧场景，则把旧的清楚释放资源
void MainView::switchToScene(QGraphicsScene *scene)
{
    QGraphicsScene *oldScene = nullptr;
    if (this->scene())
        oldScene = this->scene();
    setScene(scene);

    if (oldScene)
        oldScene->deleteLater();
}

//这是一个虚函数
void MainView::resizeEvent(QResizeEvent *event)
{
    QRectF viewRect = frameRect();//获得一个矩形
    qDebug() << "Width:" << viewRect.width() << "Height:" << viewRect.height();
    QTransform trans;
    trans.scale(viewRect.width() / wid, viewRect.height() / high);
    setTransform(trans);
}


MainWindow::MainWindow()
    : fullScreenSettingEntry("UI/FullScreen"),
    mainView(new MainView(this)),
    fullScreenAction(new QAction)
{

    QWidget *centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    QLayout *layout = new AspectRatioLayout;//布局管理器用于自动管理窗口或容器内部组件的位置和大小
    layout->addWidget(mainView);//以特定于布局的方式将小部件mainView添加到此布局。
    //mainView的位置和大小将由AspectRatioLayout控制，以保持设定的长宽比。
    centralWidget->setLayout(layout);
    //全屏
    fullScreenAction->setCheckable(true);//可检查
    fullScreenAction->setShortcut(Qt::Key_F1);
    addAction(fullScreenAction);
    connect(fullScreenAction, &QAction::toggled,this,[this] (bool checked) {
        if (checked)
            setWindowState(Qt::WindowFullScreen);
        else
            setWindowState(Qt::WindowNoState);
        QSettings().setValue(fullScreenSettingEntry, checked);
    });
    //设置背景自动填充
    setPalette(Qt::black);
    setAutoFillBackground(true);
    qDebug()<<"adjustSize";
    //感觉这里用处不大，先放一下...
    adjustSize();
}

QAction *MainWindow::getFullScreenAction() const
{
    return fullScreenAction;
}




