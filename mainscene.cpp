#include "mainscene.h"
#include "mainwindow.h"
#include "mouseeventspixmapitem.h"
#include "ImageManager.h"
#include "timer.h"
#include "gamescene.h"
#include "gameleveldata.h"
TextItem::TextItem(const QString &text, QGraphicsItem *parent)
    : QGraphicsTextItem(text, parent)
{}

void TextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QStyleOptionGraphicsItem DesignerOption(*option);
    DesignerOption.state &= ~(QStyle::State_Selected | QStyle::State_HasFocus);
    QGraphicsTextItem::paint(painter, &DesignerOption, widget);
}

MainScene::MainScene():
    QGraphicsScene(0, 0, 900, 600),
    background      (new QGraphicsPixmapItem    (ImageCache->load("interface/SelectorBackground.png"))),
    adventureShadow (new QGraphicsPixmapItem    (ImageCache->load("interface/SelectorAdventureShadow.png"))),
    survivalShadow  (new QGraphicsPixmapItem    (ImageCache->load("interface/SelectorSurvivalShadow.png"))),
    challengeShadow (new QGraphicsPixmapItem    (ImageCache->load("interface/SelectorChallengeShadow.png"))),
    woodSign1       (new QGraphicsPixmapItem    (ImageCache->load("interface/SelectorWoodSign1.png"))),
    woodSign2       (new QGraphicsPixmapItem    (ImageCache->load("interface/SelectorWoodSign2.png"))),
    woodSign3       (new QGraphicsPixmapItem    (ImageCache->load("interface/SelectorWoodSign3.png"))),
    adventureButton (new HoverChangedPixmapItem (ImageCache->load("interface/SelectorAdventureButton.png"))),
    survivalButton  (new HoverChangedPixmapItem (ImageCache->load("interface/SelectorSurvivalButton.png"))),
    challengeButton (new HoverChangedPixmapItem (ImageCache->load("interface/SelectorChallengeButton.png"))),
    usernameText    (new TextItem  (gMainView->getUsername())),
    backgroundMusic (new QMediaPlayer(this)),
    effect          (new QSoundEffect(this)),
    zombieHand      (new MoviePixmapItem        ("interface/SelectorZombieHand.gif"))
{
    addItem(background);
    //设置光标的变化
    adventureButton ->setCursor(Qt::PointingHandCursor);
    survivalButton  ->setCursor(Qt::PointingHandCursor);
    challengeButton ->setCursor(Qt::PointingHandCursor);
    //设置每块图片的位置
    adventureShadow ->setPos(468, 82);  addItem(adventureShadow);
    adventureButton ->setPos(474, 80);  addItem(adventureButton);
    survivalShadow  ->setPos(476, 208); addItem(survivalShadow);
    survivalButton  ->setPos(474, 203); addItem(survivalButton);
    challengeShadow ->setPos(480, 307); addItem(challengeShadow);
    challengeButton ->setPos(478, 303); addItem(challengeButton);
    woodSign1       ->setPos(20, -8);   addItem(woodSign1);
    woodSign2       ->setPos(23, 126);  addItem(woodSign2);
    woodSign3       ->setPos(34, 179);  addItem(woodSign3);
    zombieHand      ->setPos(250, 264); addItem(zombieHand);

    usernameText->setParentItem(woodSign1);
    //设置显示
    usernameText->setPos(35, 91);
    usernameText->setTextWidth(230);
    usernameText->document()->setDocumentMargin(0);
    usernameText->document()->setDefaultTextOption(QTextOption(Qt::AlignCenter));
    usernameText->setDefaultTextColor(QColor::fromRgb(0xf0c060));
    usernameText->setFont(QFont("Comic Sans MS", 14, QFont::Bold));
    //设置交互和事件相应
    usernameText->installEventFilter(this);//在 usernameText 上安装一个事件过滤器。this 通常指向当前类的实例，这意味着事件首先会被当前类的 eventFilter 方法处理。
    usernameText->setTextInteractionFlags(Qt::TextEditorInteraction);
    //设置背景音乐播放条件
    backgroundMusic->setSource(QUrl("qrc:/audio/Faster.mp3"));
    QAudioOutput*audioOutput = new QAudioOutput;
    backgroundMusic->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.8);
    backgroundMusic->play();
    //设置背景音乐循环播放
    connect(backgroundMusic, &QMediaPlayer::mediaStatusChanged, [this](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            backgroundMusic->setPosition(0); // 重置播放位置到开始
            backgroundMusic->play(); // 重新开始播放
        }
    });
    //设置悬停时音效
    effect->setSource(QUrl::fromLocalFile(":/audio/bleep.wav"));
    effect->setLoopCount(1);
    connect(adventureButton, &HoverChangedPixmapItem::hoverentered, [this] {
        effect->play(); });
    connect(survivalButton, &HoverChangedPixmapItem::hoverentered, [this] {
        effect->play();});
    connect(challengeButton, &HoverChangedPixmapItem::hoverentered, [this] {
        effect->play();});
    //设置僵尸手的弹出
    connect(adventureButton, &HoverChangedPixmapItem::mouseclicked, zombieHand, [this] {
    //恢复鼠标设置
    adventureButton->setCursor(Qt::ArrowCursor);
    survivalButton->setCursor(Qt::ArrowCursor);
    challengeButton->setCursor(Qt::ArrowCursor);
    //不再会响应用户的交互
    adventureButton->setEnabled(false);
    survivalButton->setEnabled(false);
    challengeButton->setEnabled(false);

    zombieHand->start();
    //切换背景音乐
    backgroundMusic->blockSignals(true);
    backgroundMusic->stop();
    backgroundMusic->blockSignals(false);
    backgroundMusic->setSource(QUrl("qrc:/audio/losemusic.mp3"));
    backgroundMusic->play();

    });
    //僵尸动画播放完成之后进入新的界面
    connect(zombieHand,&MoviePixmapItem::finished,this,[this]{
        (new Timer(this, 2500, [this](){
            backgroundMusic->blockSignals(true);
            backgroundMusic->stop();
            backgroundMusic->blockSignals(false);
            gMainView->switchToScene(new GameScene(Level_settings(QSettings().value("Global/NextLevel", "1").toString())));//要开始进入游戏了
        }))->start();
    });
}

bool MainScene::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == usernameText) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
                // 保存我新设置的用户名
                gMainView->SetUsername(usernameText->toPlainText());
                setFocusItem(nullptr);
                return true;
            }
            return false;
        }
        return false;
    }
    return QGraphicsScene::eventFilter(watched, event);
}

