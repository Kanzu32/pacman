#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    mode = false;
    difficulty = 1;
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_radioButton_clicked()
{
    ui->lineEdit_2->setEnabled(false);
    mode = false;
}


void SettingsDialog::on_radioButton_2_clicked()
{
    ui->lineEdit_2->setEnabled(true);
    mode = true;
}


void SettingsDialog::on_pushButton_2_clicked()
{
    this->reject();
}

void SettingsDialog::on_radioButton_5_clicked()
{
    difficulty = 1;
}

void SettingsDialog::on_radioButton_6_clicked()
{
    difficulty = 2;
}

void SettingsDialog::on_radioButton_7_clicked()
{
    difficulty = 3;
}


void SettingsDialog::on_pushButton_clicked()
{
    pl2name = ui->lineEdit_2->text();
    pl1name = ui->lineEdit->text();
    this->accept();

}

void SettingsDialog::getSettings(bool& m, int& difficulty, QString& p1, QString& p2) {
    if (pl1name == "" || (mode && pl2name == "")) {
        throw PlayerNameExeption("Player name can't be empty");
    }
    if (pl1name.contains('|') || pl2name.contains('|')) {
        throw PlayerNameExeption("Player name can't contain symbol '|'");
    }
    m = this->mode;
    p1 = this->pl1name;
    p2 = this->pl2name;
    difficulty = this->difficulty;
}
