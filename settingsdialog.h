#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <widget.h>

class PlayerNameExeption : public std::exception{
    std::string msg;
public:
    const char * what() const noexcept override {
        return msg.c_str();
    }
    PlayerNameExeption(std::string msg) {this->msg = msg;};
};

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    bool mode;
    int difficulty;
    QString pl1name;
    QString pl2name;
    void getSettings(bool& mode, int& difficulty, QString& p1, QString& p2);
    ~SettingsDialog();
private slots:
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_radioButton_7_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();


private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
