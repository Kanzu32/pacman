#include "records.h"
#include "ui_records.h"
#include <QDebug>
#include <QSound>

Records::Records(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Records)
{
    ui->setupUi(this);
    QWidget::showFullScreen();
    table = ui->tableWidget;
    table->setStyleSheet("QTableCornerButton::section { background-color: rgb(35, 37, 40); }QTableWidget {color: rgb(216, 216, 216); gridline-color: #fffff8;}QHeaderView::section {color: rgb(216, 216, 216);background-color: rgb(35, 37, 40);gridline-color: #fffff8;padding: 4px;font-size: 14pt;}");
    model = new QStandardItemModel();
    load();
    fill1player();
}

Records::~Records()
{
    delete ui;
}

void Records::load() {
    QString endPath = QCoreApplication::applicationDirPath() + "/records/records1player.txt";
    QFile file(endPath);
    try {
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString data = in.readLine();
        QStringList splited = data.split('|');
        if (splited.size() < 6) {continue;};
        Entry1 entry1 = Entry1(splited);
        auto id = entry1.pl1name + entry1.difficulty + entry1.lives + entry1.map;
        int count = map1pl.count(id);
        if (count == 0 || (count > 0 && map1pl.at(id).pl1score*(1/map1pl.at(id).time) < entry1.pl1score*(1/entry1.time))) {
            map1pl[id] = entry1;
        }
    }
    file.close();


    endPath = QCoreApplication::applicationDirPath() + "/records/records2players.txt";
    QFile file2(endPath);
    file2.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in2(&file2);
    while (!in2.atEnd()) {
        QString data = in2.readLine();
        QStringList splited = data.split('|');
        if (splited.size() < 8) {continue;};
        Entry2 entry2 = Entry2(splited);
        auto id = entry2.pl1name + entry2.pl2name + entry2.difficulty + entry2.lives + entry2.map;
        int count = map1pl.count(id);
        int score = entry2.pl2score + entry2.pl1score;
        if (count == 0 || (count > 0 && (map2pl.at(id).pl1score + map2pl.at(id).pl2score)*(1/map2pl.at(id).time) < score*(1/entry2.time))) {
            map2pl[id] = entry2;
        }
    }
    file2.close();
    } catch (std::exception const&e) {
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        Widget* widget = new Widget();
        widget->show();
        this->close();
    }

}

void Records::fill1player() {
    table->clear();
    table->setSortingEnabled(false);
    table->setRowCount(0);
    table->setColumnCount(6);
    table->setHorizontalHeaderItem(0, new QTableWidgetItem("Map"));
    table->setHorizontalHeaderItem(1, new QTableWidgetItem("Difficulty"));
    table->setHorizontalHeaderItem(2, new QTableWidgetItem("Lives"));
    table->setHorizontalHeaderItem(3, new QTableWidgetItem("Name"));
    table->setHorizontalHeaderItem(4, new QTableWidgetItem("Score"));
    table->setHorizontalHeaderItem(5, new QTableWidgetItem("Time"));
    for (std::pair<QString, Entry1> pair : map1pl) {
        Entry1 entry = pair.second;
        entry.addTo(table);
    }
    table->setSortingEnabled(true);
}

void Records::fill2players() {
    table->clear();
    table->setSortingEnabled(false);
    table->setRowCount(0);
    table->setColumnCount(8);
    table->setHorizontalHeaderItem(0, new QTableWidgetItem("Map"));
    table->setHorizontalHeaderItem(1, new QTableWidgetItem("Difficulty"));
    table->setHorizontalHeaderItem(2, new QTableWidgetItem("Lives"));
    table->setHorizontalHeaderItem(3, new QTableWidgetItem("1 Pl Name"));
    table->setHorizontalHeaderItem(4, new QTableWidgetItem("2 Pl Name"));
    table->setHorizontalHeaderItem(5, new QTableWidgetItem("1 Pl Score"));
    table->setHorizontalHeaderItem(6, new QTableWidgetItem("2 Pl Score"));
    table->setHorizontalHeaderItem(7, new QTableWidgetItem("Time"));
    for (std::pair<QString, Entry2> pair : map2pl) {
        Entry2 entry = pair.second;
        entry.addTo(table);
    }
    table->setSortingEnabled(true);
}

void Records::on_oneButton_clicked()
{
    QSound::play(":/music/ok.wav");
    fill1player();
}


void Records::on_twoButton_clicked()
{
    QSound::play(":/music/ok.wav");
    fill2players();
}


void Records::on_backButton_clicked()
{
    QSound::play(":/music/close.wav");
    Widget* widget = new Widget();
    widget->show();
    this->close();
}

