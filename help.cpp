#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    QWidget::showFullScreen();
    textBrowser = ui->textBrowser;
}

Help::~Help()
{
    delete ui;
}

void Help::on_rusButton_clicked()
{
    QSound::play(":/music/ok.wav");
    textBrowser->setText(rusHtml);
}


void Help::on_engButton_clicked()
{
    QSound::play(":/music/ok.wav");
    textBrowser->setText(engHtml);
}


void Help::on_backButton_clicked()
{
    QSound::play(":/music/close.wav");
    Widget* widget = new Widget();
    widget->show();
    this->close();
}

