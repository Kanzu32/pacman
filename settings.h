#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QKeyEvent>
#include <QDebug>
#include <QLabel>
#include <widget.h>
#include <QSettings>
#include <QSlider>
namespace Ui {
class Settings;
}

class Settings : public QWidget // окно настроек
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    bool input = false; // активен ли ввод
    QString mode = ""; // какая кнопка настраивается в данный момент
    QLabel *p1left;
    QLabel *p1down;
    QLabel *p1right;
    QLabel *p1up;
    QLabel *p2left;
    QLabel *p2down;
    QLabel *p2right;
    QLabel *p2up;
    QSlider *slider;
    QLabel *sliderView;
    int p1leftkey; // переменные для заданных клавиш
    int p1downkey;
    int p1rightkey;
    int p1upkey;
    int p2leftkey;
    int p2downkey;
    int p2rightkey;
    int p2upkey;
    QSettings* config; // для записи/чтения данных внешнего .ini файла
    ~Settings();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_8_clicked();

    void on_saveButton_clicked();

    void on_backButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

private:
    void keyPressEvent(QKeyEvent *event) override;
    Ui::Settings *ui;
};

#endif // SETTINGS_H
