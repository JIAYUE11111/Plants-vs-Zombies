#include "mainwindow.h"
#include "imagemanager.h"
#include "mainscene.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDateTime>
#include <QRandomGenerator>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //QCoreApplication::setApplicationName("Plants VS Zombies");
    app.setWindowIcon(QIcon(":/icons/Cover.png"));
    // For QSettings
    QCoreApplication::setOrganizationName("Cao Jiayue");
    QCoreApplication::setOrganizationDomain("Cao Jiayue.com");
    QCoreApplication::setApplicationName("Plants vs Zombies");
    //设置英文到中文的翻译
    /*
    QTranslator translator;
    if (translator.load(":/translations/Finalwork_zh_CN.qm")) {
        app.installTranslator(&translator);
    } else {
        // 处理加载失败的情况
        printf("no");
    }*/
    //初始一个图片加载管理器
    InitImageManager();
    //设置随机数种子
    // 获取当前时间的毫秒数作为种子
    quint64 seed = static_cast<quint64>(QDateTime::currentMSecsSinceEpoch());
    // 使用种子初始化随机数生成器
    QRandomGenerator randomGenerator(seed);
    MainWindow w;
    w.setWindowTitle(QObject::tr("Plants VS Zombies"));
    gMainView->switchToScene(new MainScene);
    w.show();
    return app.exec();
}
