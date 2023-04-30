#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <widget.h>

class PlayerNameExeption : public std::exception{ // ошибка в имени игрока
    std::string msg; // сообщение об ошибке
public:
    const char * what() const noexcept override { // вывод сообщения
        return msg.c_str();
    }
    PlayerNameExeption(std::string msg) {this->msg = msg;};
};

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog // диалоговое окно настроек перед началом игры
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    bool mode; // режим игры 1/2 игрока
    int difficulty; // сложность
    QString pl1name; // имя 1 игрока
    QString pl2name; // имя 2 игрока
    void getSettings(bool& mode, int& difficulty, QString& p1, QString& p2); // получение настроек из диалогового окна
    ~SettingsDialog();
private slots:
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_radioButton_7_clicked();

    void on_continueButton_clicked();

    void on_exitButton_clicked();


private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
