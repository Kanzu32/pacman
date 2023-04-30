#ifndef RECORDS_H
#define RECORDS_H

#include <QWidget>
#include <QTableWidget>
#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>
#include <widget.h>
#include <map>

class Entry1 { // одна запись в таблице для 1 игрока
public:
    QString map; // название карты
    QString pl1name; // имя
    int difficulty; // сложность
    int lives; // кол-во жизней
    int pl1score; // очки 1 игррока
    float time; // время прохождения уровня
    Entry1(QStringList arr) {
        map = arr.at(0);
        difficulty = arr.at(1).toInt();
        lives = arr.at(2).toInt();
        pl1name = arr.at(3);
        pl1score = arr.at(4).toInt();
        time = arr.at(5).toFloat();
    }
    Entry1 () {pl1score = -1;};
    virtual void addTo(QTableWidget* table) { // добавление в таблицу
        int count = table->rowCount();
        table->setRowCount(count+1);
        table->setItem(count, 0, new QTableWidgetItem(map));
        switch (difficulty) {
        case 1:
            table->setItem(count, 1, new QTableWidgetItem("Easy"));
            break;
        case 2:
            table->setItem(count, 1, new QTableWidgetItem("Medium"));
            break;
        case 3:
            table->setItem(count, 1, new QTableWidgetItem("Hard"));
            break;
        default:
            break;
        }
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, lives);
        table->setItem(count, 2, item);
        item = new QTableWidgetItem();
        table->setItem(count, 3, new QTableWidgetItem(pl1name));
        item->setData(Qt::DisplayRole, pl1score);
        table->setItem(count, 4, item);
        item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, time);
        table->setItem(count, 5, item);
    }
};

class Entry2: public Entry1 { // одна запись в таблице для 2 игроков
public:
    QString pl2name; // имя 2 игрока
    int pl2score; // очки 2 игрока
    Entry2 (QStringList arr) {
        map = arr.at(0);
        difficulty = arr.at(1).toInt();
        lives = arr.at(2).toInt();
        pl1name = arr.at(3);
        pl2name = arr.at(4);
        pl1score = arr.at(5).toInt();
        pl2score = arr.at(6).toInt();
        time = arr.at(7).toFloat();
    }

    Entry2 () {pl1score = -1;};

    void addTo(QTableWidget* table) { // добавление в таблицу
        int count = table->rowCount();
        table->setRowCount(count+1);
        table->setItem(count, 0, new QTableWidgetItem(map));
        switch (difficulty) {
        case 1:
            table->setItem(count, 1, new QTableWidgetItem("Easy"));
            break;
        case 2:
            table->setItem(count, 1, new QTableWidgetItem("Medium"));
            break;
        case 3:
            table->setItem(count, 1, new QTableWidgetItem("Hard"));
            break;
        default:
            break;
        }
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, lives);
        table->setItem(count, 2, item);
        table->setItem(count, 3, new QTableWidgetItem(pl1name));
        table->setItem(count, 4, new QTableWidgetItem(pl2name));
        item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, pl1score);
        table->setItem(count, 5, item);
        item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, pl2score);
        table->setItem(count, 6, item);
        item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, time);
        table->setItem(count, 7, item);
    }
};

namespace Ui {
class Records;
}

class Records : public QWidget // окно записей рекордов игроков
{
    Q_OBJECT

public:
    explicit Records(QWidget *parent = nullptr);
    void fill1player(); // заполнение таблицы для 1 игрока
    void fill2players(); // заполнение таблицы для 2 игроков
    void load(); // загрузка из внешнего файла
    std::map<QString,Entry1> map1pl; // map для хранения результатов 1 игрока
    std::map<QString,Entry2> map2pl; // map для хранения результатов 2 игроков
    QStandardItemModel* model;
    QTableWidget* table;
    ~Records();

private slots:
    void on_oneButton_clicked();

    void on_twoButton_clicked();

    void on_backButton_clicked();

private:
    Ui::Records *ui;
};



#endif // RECORDS_H
