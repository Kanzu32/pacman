#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <game.h>
#include <settings.h>
#include <records.h>
#include <help.h>
#include <QFont>
#include <QFontDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    void keyPressEvent(QKeyEvent *event);
    Widget(QWidget *parent = nullptr); //окно главного меню
    ~Widget();



private slots:
    void on_exitButton_clicked();

    void on_helpButton_clicked();

    void on_recordsButton_clicked();

    void on_settingsButton_clicked();

    void on_playButton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
