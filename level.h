#ifndef LEVEL_H
#define LEVEL_H

#include <QString>
#include <QDebug>
#include <QFile>
#include <movable.h>
#include <queue>
#include <QMessageBox>

class LevelLoadException : public std::exception {
    std::string msg;
public:
    const char * what() const noexcept override {
        return msg.c_str();
    }
    LevelLoadException(std::string msg) {this->msg = msg;};
};

struct navCell {
    Direction dir;
    int length;
};

struct coord {
    int x;
    int y;
    coord(int xx, int yy) {
        x = xx;
        y = yy;
    };
};

class Level
{
private:
    int h;
    int w;
    int** map;

public:
    Player p1;
    Player p2;
    QString p1name;
    QString p2name;
    QString mapName;
    Enemy* enemies;
    int difficulty;
    int enemiesCount;
    int coinsCount;
    bool p2enabled;
    int p1Score;
    int p2Score;
    int score;
    int maxLives;
    int getWidth() {return w;};
    int getHeight() {return h;};
    navCell** navMap;
    int** getMap() {return map;};
    navCell** getNavMap() {return navMap;};
    void recreateNavMap() {
        this->restoreNavMap();
        std::queue <coord> q;
        if (p1.targetable) {
            navMap[p1.getX()][p1.getY()].length = 0;
            q.push(coord{p1.getX(), p1.getY()});
        }

        if (p2enabled && p2.targetable) {
            navMap[p2.getX()][p2.getY()].length = 0;
            q.push(coord{p2.getX(), p2.getY()});
        }

        while (!q.empty()) {
            coord cell = q.front();
            q.pop();
            if (cell.x > 0 && navMap[cell.x-1][cell.y].length == -1) {
                q.push(coord{cell.x-1, cell.y});
                navMap[cell.x-1][cell.y].dir = Direction(1, 0);
                navMap[cell.x-1][cell.y].length = navMap[cell.x][cell.y].length+1;
            }
            if (cell.x < w-1 && navMap[cell.x+1][cell.y].length == -1) {
                q.push(coord{cell.x+1, cell.y});
                navMap[cell.x+1][cell.y].dir = Direction(-1, 0);
                navMap[cell.x+1][cell.y].length = navMap[cell.x][cell.y].length+1;
            }
            if (cell.y > 0 && navMap[cell.x][cell.y-1].length == -1) {
                q.push(coord(cell.x, cell.y-1));
                navMap[cell.x][cell.y-1].dir = Direction(0, 1);
                navMap[cell.x][cell.y-1].length = navMap[cell.x][cell.y].length+1;
            }
            if (cell.y < h-1 && navMap[cell.x][cell.y+1].length == -1) {
                q.push(coord(cell.x, cell.y+1));
                navMap[cell.x][cell.y+1].dir = Direction(0, -1);
                navMap[cell.x][cell.y+1].length = navMap[cell.x][cell.y].length+1;
            }
        }


    }

    void printNavMap() {
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                qDebug() << "(" <<navMap[i][j].dir.horizontal << " " << navMap[i][j].dir.vertical << ") ";
            }
            qDebug() << '\n';
        }
    }

    void restoreNavMap() {
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                if (navMap[i][j].length > -1) {
                    navMap[i][j] = navCell{Direction(0, 0), -1};
                }
            }
        }
    }

    Level(QString filename, bool mode, QString p1, QString p2, int difficulty, int lives) {
        this->maxLives = lives;
        this->difficulty = difficulty;
        this->coinsCount = 0;
        this->p2enabled = mode;
        this->p1name = p1;
        this->p2name = p2;
        this->mapName = filename.mid(filename.lastIndexOf('/')+1, filename.lastIndexOf('.')-filename.lastIndexOf('/')-1);
        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        QString data;
        data = file.readAll();
        QStringList splited = data.split('|');
        QRegExp re("\\D*");
        if (splited.size() < 8 ||
            re.exactMatch(splited.at(0))||
            re.exactMatch(splited.at(1))||
            re.exactMatch(splited.at(2))||
            re.exactMatch(splited.at(3))||
            re.exactMatch(splited.at(4))) {
            throw LevelLoadException("Level file corrupted");
        }
        this->w = QString(splited.at(0)).toInt();
        this->h = QString(splited.at(1)).toInt();
        switch (difficulty) {
        case 1:
            this->enemiesCount = QString(splited.at(2)).toInt();
            break;
        case 2:
            this->enemiesCount = QString(splited.at(3)).toInt();
            break;
        case 3:
            this->enemiesCount = QString(splited.at(4)).toInt();
            break;
        default:
            this->enemiesCount = QString(splited.at(2)).toInt();
            this->difficulty = 1;
            break;
        }
        this->enemies = new Enemy[enemiesCount];
        QString lvlMap = splited.at(4+difficulty);
        lvlMap.remove('\r');
        lvlMap.remove('\n');
        map = new int*[w];
        navMap = new navCell*[w];
        int x = 0;
        bool pl1created = false;
        bool pl2created = false;
        for (int i = 0; i < this->w; i++) {
            this->map[i] = new int[h];
            this->navMap[i] = new navCell[h];
            for (int j = 0; j < this->h; j++) {
                if (i+j*w > lvlMap.length()) {
                    throw LevelLoadException("Level file corrupted");
                }
                if (!lvlMap.at(i+j*w).isNumber()) {
                    throw LevelLoadException("Level file contains illegal characters");
                }
                this->map[i][j] = QString(lvlMap.at(i+j*w)).toInt();

                if (this->map[i][j] == 4) {
                    this->p1 = Player(lives, i, j);
                    this->map[i][j] = 0;
                    pl1created = true;
                } else if (this->map[i][j] == 5 && x < enemiesCount) {
                    this->enemies[x] = Enemy(i, j);
                    this->map[i][j] = 0;
                    x++;
                } else if (this->map[i][j] == 6 && p2enabled) {
                    this->p2 = Player(lives, i, j);
                    this->map[i][j] = 0;
                    pl2created = true;
                } else if (this->map[i][j] == 6 && !p2enabled){
                    this->map[i][j] = 0;
                    pl2created = true;
                } else if (this->map[i][j] == 2 || this->map[i][j] == 3) {
                    this->coinsCount++;
                } else if (this->map[i][j] == 1) {
                    navMap[i][j] = navCell{Direction(0, 0), -2};
                } else if (this->map[i][j] == 0) {
                    navMap[i][j] = navCell{Direction(0, 0), -1};
                } else {
                    throw LevelLoadException("Level file contains illegal characters");
                }
            }
        }
        score = 0;
        p1Score = 0;
        p2Score = 0;

        if (!pl1created || !pl2created) {
            throw LevelLoadException("Level file doesn't contains player position");
        }
    }


    Level() {h = 0; w = 0;};
};

#endif // LEVEL_H
