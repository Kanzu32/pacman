#ifndef DIRECTION_H
#define DIRECTION_H

class Direction {
public:
    short horizontal;
    short vertical;
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
