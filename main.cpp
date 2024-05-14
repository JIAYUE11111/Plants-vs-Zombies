#include <QRandomGenerator>
#include <QtCore>
#include <QtWidgets>
#include "MainView.h"
#include "SelectorScene.h"
#include "ImageManager.h"

#include <QDebug>
/*
void crashHandler(int sig) {
    qDebug() << "Program crashed! The signal is: " << sig;
    // 进行一些处理操作
    exit(0); // 退出程序
}*/
int main(int argc, char * *argv)
{
    //signal(SIGSEGV, crashHandler); // 注册SIGSEGV信号的处理函数
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/images/interface/SmallLogo.png"));
    // For QSettings
    QCoreApplication::setOrganizationName("Cao Jiayue");
    QCoreApplication::setOrganizationDomain("Cao Jiayue.com");
    QCoreApplication::setApplicationName("Plants vs Zombies");
    // For Translators
    QTranslator appTranslator;
    // TODO: change translation back after debugging
    //appTranslator.load(QString(":/translations/main.%1.qm").arg(QLocale::system().name()));
    appTranslator.load(QString(":/translations/main.%1.qm").arg("zh_CN"));
    app.installTranslator(&appTranslator);

    InitImageManager();
    //生成随机数种子
    MainWindow mainWindow;
    gMainView->switchToScene(new SelectorScene);
    mainWindow.show();
    int res = app.exec();
    DestoryImageManager();
    return res;
}


