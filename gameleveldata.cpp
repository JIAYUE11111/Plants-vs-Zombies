#include "gameleveldata.h"
#include "gamescene.h"
#include "timer.h"

/*    QString backgroundMusic;
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
    QList<ZombieData> zombiesData;*/
GameLevelData::GameLevelData() :
    backgroundMusic("qrc:/audio/UraniwaNi.mp3"),
    backgroundImage("interface/background1.jpg"),

    cardKind(0),dKind(1),sunNum(50), flagNum(0),

    canSelectCard(true),
    staticCard(true),
    showScroll(true),
    produceSun(true),
    hasShovel(true),
    maxSelectedCards(8),coord(0),
    LF{ 0, 1, 1, 1, 1, 1 }
{
    ;
}

GameLevelData1::GameLevelData1()
{
    eName = "1";
    cName = tr("Level 1-1");
    //可以选择的植物的名字
    pName = { "oPeashooter", "oSnowPea", "oSunflower", "oWallNut", "oPumpkinHead", "oTorchwood", "oTallNut" };
    zombiesData = { { "oZombie", 3, 1, {} }, { "oZombie2", 3, 1, {} }, { "oZombie3", 3, 1, {} },
                  { "oConeheadZombie", 5, 3, {} }, { "oPoleVaultingZombie", 5, 5, {} }, { "oBucketheadZombie", 5, 9, {} } };
    flagNum = 20;
    largeWaveFlag = { 9, 19 };
    flagToSumNum = QPair<QList<int>, QList<int> >({ 3, 4, 8, 9, 10, 13, 15, 19 }, { 1, 2, 3, 5, 15, 6, 8, 10, 20 });
}

//拥有一个新关卡1
GameLevelData *Level_settings(const QString &eName)
{

    if (eName == "1")
        return new GameLevelData1;
    return nullptr;
}

void  GameLevelData::loadAccess(GameScene *gameScene)
{

    gameScene->loadAcessFinished();
}

void GameLevelData::startGame(GameScene *gameScene)
{

    initLawnMower(gameScene);
    gameScene->prepareGrowPlants( [gameScene] {
        gameScene->beginBGM();
        gameScene->beginMonitor();
        gameScene->beginCool();
        gameScene->beginSun(25);
        (new Timer(gameScene, 15000, [gameScene] {
            gameScene->beginZombies();
        }))->start();
    });
}

void GameLevelData::initLawnMower(GameScene *gameScene)
{
    for (int i = 0; i < LF.size(); ++i) {
        if (LF[i] == 1)
            gameScene->customSpecial("oLawnCleaner", -1, i);
        else if (LF[i] == 2)
            gameScene->customSpecial("oPoolCleaner", -1, i);
    }
}

void GameLevelData::endGame(GameScene *gameScene)
{

}
