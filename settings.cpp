#include "settings.h"
#include "ui_settings.h"
#include <QSound>

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    p1left = ui->label_10;
    p1down = ui->label_11;
    p1right = ui->label_12;
    p1up = ui->label_13;
    p2left = ui->label_15;
    p2down = ui->label_18;
    p2right = ui->label_19;
    p2up = ui->label_17;
    slider = ui->horizontalSlider;
    sliderView = ui->label_22;

    QWidget::showFullScreen();

    QString Path = QCoreApplication::applicationDirPath();
    QString endPath = Path + "/config/config.ini";
    QFileInfo fileinfo(endPath);
    if (fileinfo.isFile()) {
        config = new QSettings(endPath, QSettings::IniFormat);

        sliderView->setNum(config->value("lives", "").toInt());
        slider->setValue(config->value("lives", "").toInt());
        p1leftkey = config->value("p1left", "").toInt();
        p1left->setText(QKeySequence(p1leftkey).toString());
        p1downkey = config->value("p1down", "").toInt();
        p1down->setText(QKeySequence(p1downkey).toString());
        p1rightkey = config->value("p1right", "").toInt();
        p1right->setText(QKeySequence(p1rightkey).toString());
        p1upkey = config->value("p1up", "").toInt();
        p1up->setText(QKeySequence(p1upkey).toString());
        p2leftkey = config->value("p2left", "").toInt();
        p2left->setText(QKeySequence(p2leftkey).toString());
        p2downkey = config->value("p2down", "").toInt();
        p2down->setText(QKeySequence(p2downkey).toString());
        p2rightkey = config->value("p2right", "").toInt();
        p2right->setText(QKeySequence(p2rightkey).toString());
        p2upkey = config->value("p2up", "").toInt();
        p2up->setText(QKeySequence(p2upkey).toString());
    }

}

Settings::~Settings()
{
    delete ui;
}

void Settings::keyPressEvent(QKeyEvent *event) {
    if (input) {
        if (mode == "p1left") {
            p1left->setText(QKeySequence(event->key()).toString());
            p1leftkey = event->key();
        }
        if (mode == "p1down") {
            p1down->setText(QKeySequence(event->key()).toString());
            p1downkey = event->key();
        }
        if (mode == "p1right") {
            p1right->setText(QKeySequence(event->key()).toString());
            p1rightkey = event->key();
        }
        if (mode == "p1up") {
            p1up->setText(QKeySequence(event->key()).toString());
            p1upkey = event->key();
        }
        if (mode == "p2left") {
            p2left->setText(QKeySequence(event->key()).toString());
            p2leftkey = event->key();
        }
        if (mode == "p2down") {
            p2down->setText(QKeySequence(event->key()).toString());
            p2downkey = event->key();
        }
        if (mode == "p2right") {
            p2right->setText(QKeySequence(event->key()).toString());
            p2rightkey = event->key();
        }
        if (mode == "p2up") {
            p2up->setText(QKeySequence(event->key()).toString());
            p2upkey = event->key();
        }
        input = false;
    }

}

void Settings::on_pushButton_3_clicked()
{
    input = true;
    mode = "p1left";
}


void Settings::on_pushButton_4_clicked()
{
    input = true;
    mode = "p1down";
}


void Settings::on_pushButton_5_clicked()
{
    input = true;
    mode = "p1right";
}


void Settings::on_pushButton_6_clicked()
{
    input = true;
    mode = "p1up";
}


void Settings::on_pushButton_7_clicked()
{
    input = true;
    mode = "p2left";
}


void Settings::on_pushButton_9_clicked()
{
    input = true;
    mode = "p2down";
}


void Settings::on_pushButton_10_clicked()
{
    input = true;
    mode = "p2right";
}


void Settings::on_pushButton_8_clicked()
{
    input = true;
    mode = "p2up";
}


void Settings::on_pushButton_clicked()
{
    QSound::play(":/music/close.wav");
    Widget* widget = new Widget();
    widget->show();
    this->close();
}


void Settings::on_pushButton_2_clicked()
{
    QSound::play(":/music/ok.wav");
    QString Path = QCoreApplication::applicationDirPath();
    QString endPath = Path + "/config/config.ini";
    config = new QSettings(endPath, QSettings::IniFormat);
    config->setValue("lives", slider->value());
    config->setValue("p1left", p1leftkey);
    config->setValue("p1down", p1downkey);
    config->setValue("p1right", p1rightkey);
    config->setValue("p1up", p1upkey);
    config->setValue("p2left", p2leftkey);
    config->setValue("p2down", p2downkey);
    config->setValue("p2right", p2rightkey);
    config->setValue("p2up", p2upkey);

}


void Settings::on_horizontalSlider_valueChanged(int value)
{
    sliderView->setNum(value);
}

