#ifndef DIRECTION_H
#define DIRECTION_H

class Direction { // класс показывающий направление
public:
    short horizontal; // горизонтальное напр.
    short vertical; // вертикальное напр.
    Direction(int h, int v) {
        this->horizontal = h;
        this->vertical = v;
    }
    Direction() {
        this->horizontal = 0;
        this->vertical = 0;
    }
};

#endif // DIRECTION_H
