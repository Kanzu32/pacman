#ifndef RECORDS_H
#define RECORDS_H

#include <QWidget>
#include <QTableWidget>
#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>
#include <widget.h>
#include <map>

class Entry1 {
public:
    QString map;
    QString pl1name;
    int difficulty;
    int lives;
    int pl1score;
    float time;
    Entry1(QStringList arr) {
        map = arr.at(0);
        difficulty = arr.at(1).toInt();
        lives = arr.at(2).toInt();
        pl1name = arr.at(3);
        pl1score = arr.at(4).toInt();
        time = arr.at(5).toFloat();
    }
    Entry1 () {pl1score = -1;};
    virtual void addTo(QTableWidget* table) {
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

class Entry2: public Entry1 {
public:
    QString pl2name;
    int pl2score;
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

    void addTo(QTableWidget* table) {
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

class Records : public QWidget
{
    Q_OBJECT

public:
    explicit Records(QWidget *parent = nullptr);
    void fill1player();
    void fill2players();
    void load();
    bool twoPlayersMode = false;
    std::map<QString,Entry1> map1pl;
    std::map<QString,Entry2> map2pl;
    QStandardItemModel* model;
    QTableWidget* table;
    ~Records();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Records *ui;
};



#endif // RECORDS_H
