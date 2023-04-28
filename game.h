#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QFileDialog>
#include <QDebug>
#include <QKeyEvent>
#include <QSettings>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QElapsedTimer>
#include <QLabel>
#include <cmath>

#include <level.h>
#include <widget.h>
#include <settingsdialog.h>
#include <direction.h>

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void endGame();
    QPixmap *spriteMap;
    const int spriteSize = 16;
    int frame = 0;
    int animationSpeed = 25;
    QTimer *animationTimer;
    Level level;
    bool error = false;
    int lives;
    int difficulty;
    int p1leftkey;
    int p1downkey;
    int p1rightkey;
    int p1upkey;
    int p2leftkey;
    int p2downkey;
    int p2rightkey;
    int p2upkey;
    int playerSpeed = 1;
    int bonusTime = 3000;
    int untargetTime = 2000;
    int viewSize = 3;
    int** map;
    bool loaded = false;
    QString pl1name;
    QString pl2name;
    QTimer *timer2;
    QTimer *timer1;
    QTimer *untargetTimer1;
    QTimer *untargetTimer2;
    QElapsedTimer gameTimer;
    QVBoxLayout *layout;
    QFrame* endScreen;
    QLabel* title;
    QLabel* stats;
    ~Game();

private slots:
    void nextFrame();
    void endBonusPl1();
    void endBonusPl2();
    void endUntargetPl1();
    void endUntargetPl2();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    void keyPressEvent(QKeyEvent *event) override;
    Ui::Game *ui;
};

#endif // GAME_H
