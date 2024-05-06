#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

//游戏共有两个场景
class MainScene;
class GameScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    QAction *getFullScreenAction() const;

private:
    const QString fullScreenSettingEntry;
    QGraphicsView *mainView;
    QAction *fullScreenAction;
};

class MainView:public QGraphicsView
{
    Q_OBJECT
public:
    MainView(MainWindow *mainwindow);
    ~MainView();

    QString getUsername()const;
    void SetUsername(const QString &username);

    MainWindow *getMainWindow() const;

    void switchToScene(QGraphicsScene *scene);

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    const int wid,high;
    const QString usernameSettingEntry;
    MainWindow *mainWindow;
};

extern MainView *gMainView;

#endif // MAINWINDOW_H
