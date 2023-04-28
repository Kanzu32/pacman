#include "widget.h"
#include "ui_widget.h"
#include <QMovie>
#include <QSound>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    int id = QFontDatabase::addApplicationFont(":/fonts/font.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font = QFont(family);
    QWidget::showFullScreen();
    QMovie *movie = new QMovie(":/images/gif.gif");
    QLabel* label = ui->label_2;
    label->setMovie(movie);
    movie->start();

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QSound::play(":/music/ok.wav");
    Game* game = new Game();
    game->show();
    this->close();
}


void Widget::on_pushButton_3_clicked()
{
    QSound::play(":/music/close.wav");
    qApp->exit();
}


void Widget::on_pushButton_2_clicked()
{
    QSound::play(":/music/ok.wav");
    Settings* settings = new Settings();
    settings->show();
    this->close();
}


void Widget::on_pushButton_4_clicked()
{
    QSound::play(":/music/ok.wav");
    Records* records = new Records();
    records->show();
    this->close();
}


void Widget::on_pushButton_5_clicked()
{
    QSound::play(":/music/ok.wav");
    Help* help = new Help();
    help->show();
    this->close();
}

