#ifndef MOVABLE_H
#define MOVABLE_H

#include <direction.h>
#include <cstdlib>

class Movable // класс для движущегося объекта
{
protected:
    int x; // x координата
    int y; // y координата
    int memAnim; // сохранение анимации
    Direction direction; // направление движения

public:
    float speed; // скорость
    float movePhase; // степень сдвига
    void move(int h, int w) { // движение
        this->x += direction.horizontal;
        this->y += direction.vertical;

        if (this->x <= 0) {
            this->x = w-1;
        } else if (this->x >= w-1) {
            this->x = 0;
        }

        if (this->y <= 0) {
            this->y = h-1;
        } else if (this->y >= h-1) {
            this->y = 0;
        }
    };
    int getX() {return x;};
    int getY() {return y;};
    void setDir(int h, int v) {
        this->direction.horizontal = h;
        this->direction.vertical = v;
    };
    void setDir(Direction dir) {
        this->direction = dir;
    };
    int getH() {return this->direction.horizontal;};
    int getV() {return this->direction.vertical;};
    Direction getDir() {return this->direction;};
    int getAnimDir() {
        if (direction.horizontal == -1) {
            memAnim = 2;
            return 2;
        }
        else if (direction.horizontal == 1) {
            memAnim = 0;
            return 0;
        }
        else if (direction.vertical == -1) {
            memAnim = 3;
            return 3;
        }
        else if (direction.vertical == 1) {
            memAnim = 1;
            return 1;
        }
        else { return memAnim; };
    }
    Movable() {direction.horizontal = 0; direction.vertical = 0; memAnim = 0;};
    Movable(int x, int y)  {
        this->x = x;
        this->y = y;
        direction.horizontal = 0;
        direction.vertical = 0;
        memAnim = 0;
    };
};

class Player: public Movable { // игрок
private:
    Direction memoryDirection; // запоминание направления движения
    int spawnX; // изначальные координаты появления иргока
    int spawnY;
public:
    int lives; // жизни
    bool targetable; // может ли враг навредить игроку
    void setMDir(int h, int v) {
        this->memoryDirection.horizontal = h;
        this->memoryDirection.vertical = v;
    };
    void setMDir(Direction dir) {
        this->memoryDirection = dir;
    };
    int getMH() {return this->memoryDirection.horizontal;};
    int getMV() {return this->memoryDirection.vertical;};
    Direction getMDir() {return this->memoryDirection;};
    void toSpawn() { // перемещение в изначальную позицию
        targetable = false;
        x = spawnX;
        y = spawnY;
        setDir(0, 0);
        lives--;
        movePhase = 0;
    }

    Player() {
        direction.horizontal = 0;
        direction.vertical = 0;
        memoryDirection.horizontal = 0;
        memoryDirection.vertical = 0;
        x = 0;
        y = 0;
        movePhase = 0;
        speed = 1.0;
        lives = 3;
        spawnX = x;
        spawnY = y;
        targetable = true;
    }

    Player(int lives): Player() {
        this->lives = lives;
    }

    Player(int lives, int x, int y): Player(lives) {
        this->x = x;
        this->y = y;
        spawnX = x;
        spawnY = y;
    }

    Player(int lives, int x, int y, int h, int v): Player(lives, x, y) {
        this->setDir(h, v);
    }

    Player(int lives, int x, int y, Direction dir): Player(lives, x, y) {
        this->setDir(dir);
    }

};

class Enemy: public Movable { // враг
public:
    int color; // цвет
    Enemy() {
        this->color = rand()%4;
        this->movePhase = 0;
        this->speed = 0.8;
        direction.horizontal = 0;
        direction.vertical = 0;
    };
    Enemy(int x, int y, float spd): Enemy() {
        this->x = x;
        this->y = y;
        this->speed = spd;
    };

};



#endif // MOVABLE_H
