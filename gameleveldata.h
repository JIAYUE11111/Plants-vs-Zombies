#ifndef GAMELEVELDATA_H
#define GAMELEVELDATA_H
#include <QtCore>
class timer;
class GameScene;

class ZombieData
{
public:
    QString eName;
    int num;
    int firstFlag;
    QList<int> flagList;
};


class GameLevelData
{
    Q_DECLARE_TR_FUNCTIONS(GameLevelData)

public:
    GameLevelData();
    virtual ~GameLevelData() {}

    QString backgroundMusic;
    QString backgroundImage;

    QString eName, cName;
    QList<QString> pName, zName;

    int cardKind;
    int dKind;

    int sunNum;
    int flagNum;

    bool canSelectCard, staticCard, showScroll, produceSun, hasShovel;
    int maxSelectedCards;
    int coord;

    QList<int> LF;
    QList<int> largeWaveFlag;
    QPair<QList<int>, QList<int> > flagToSumNum;
    QMap<int, std::function<void(GameScene *)> > flagToMonitor;
    QList<ZombieData> zombiesData;
    virtual void loadAccess(GameScene *gameScene);
    virtual void initLawnMower(GameScene *gameScene);
    virtual void startGame(GameScene *gameScene);
    virtual void endGame(GameScene *gameScene);
};

class GameLevelData1: public GameLevelData
{
    Q_DECLARE_TR_FUNCTIONS(GameLevelData_1)
public:
    GameLevelData1();
};

GameLevelData * Level_settings(const QString &eName);
#endif // GAMELEVELDATA_H
