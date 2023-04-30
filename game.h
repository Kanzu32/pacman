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

class Game : public QWidget // окно игры
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void endGame(); // завершение игры
    QPixmap *spriteMap; // графические ресурсы игры
    const int spriteSize = 16; // размер 1 клетки
    int frame = 0; // текущий кадр. необходим для анимации
    int animationSpeed = 25; // скорость анимации
    QTimer *animationTimer; // таймер анимации
    Level level; // объект уровня
    bool error = false; // выявлена ошибка
    int lives; // кол-во жизней
    int difficulty; // сложность
    int p1leftkey; // клавиши управления
    int p1downkey;
    int p1rightkey;
    int p1upkey;
    int p2leftkey;
    int p2downkey;
    int p2rightkey;
    int p2upkey;
    int playerSpeed = 1; // скорость игрока
    int bonusTime = 3000; // время ускорения при поднятии бонуса
    int untargetTime = 2000; // время невосприимчивости к урону после его получаения
    int viewSize = 3; // масштабирование камеры
    int** map; // карта
    bool loaded = false; // все ресурсы загружены и всё готово к игре
    QString pl1name; // имена игроков
    QString pl2name;
    QTimer *timer2; // таймеры для ускорения после бонуса
    QTimer *timer1;
    QTimer *untargetTimer1; // таймеры невосприимчивости к урону
    QTimer *untargetTimer2;
    QElapsedTimer gameTimer; // время прохождения уровня
    //QVBoxLayout *layout;
    QFrame* endScreen; // экран завершения игры
    QLabel* title; // победа/порожение на экране завершения
    QLabel* stats; // статистика на экране завершения
    ~Game();

private slots:
    void nextFrame();
    void endBonusPl1(); // окончиние бонусов
    void endBonusPl2();
    void endUntargetPl1(); // окончание невосприимчивости
    void endUntargetPl2();

    void on_recordsButton_clicked();

    void on_againButton_clicked();

    void on_menuButton_clicked();

private:
    void keyPressEvent(QKeyEvent *event) override;
    Ui::Game *ui;
};

#endif // GAME_H
