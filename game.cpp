#include "game.h"
#include "ui_game.h"
#include <QSound>

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    QWidget::showFullScreen();
    QWidget::setAttribute( Qt::WA_DeleteOnClose, true );
    endScreen = ui->frame_5;
    endScreen->setVisible(false);
    title = ui->label;
    stats = ui->label_2;
    bool mode = true;
    try {
    SettingsDialog dialog(this);
    QString filename = QFileDialog::getOpenFileName();
    if (dialog.exec() == QDialog::Rejected || filename == "") {
        error = true;
    } else {
        dialog.getSettings(mode, difficulty, pl1name, pl2name);
        spriteMap = new QPixmap(":/images/sprites.png");

        QString Path = QCoreApplication::applicationDirPath();
        QString endPath = Path + "/config/config.ini";
        QFileInfo fileinfo(endPath);
        if (fileinfo.isFile()) {
            QSettings* config = new QSettings(endPath, QSettings::IniFormat);
            lives = config->value("lives", "").toInt();
            p1leftkey = config->value("p1left", "").toInt();
            p1downkey = config->value("p1down", "").toInt();
            p1rightkey = config->value("p1right", "").toInt();
            p1upkey = config->value("p1up", "").toInt();
            p2leftkey = config->value("p2left", "").toInt();
            p2downkey = config->value("p2down", "").toInt();
            p2rightkey = config->value("p2right", "").toInt();
            p2upkey = config->value("p2up", "").toInt();
        }
        level = Level(filename, mode, pl1name, pl2name, difficulty, lives);


        level.recreateNavMap();
        for (int x = 0; x < level.enemiesCount; x++) {
            level.enemies[x].setDir(level.getNavMap()[level.enemies[x].getX()][level.enemies[x].getY()].dir);
        }
        animationTimer = new QTimer();
        connect(animationTimer, SIGNAL(timeout()), this, SLOT(nextFrame()));

        timer1 = new QTimer(this);
        timer2 = new QTimer(this);
        untargetTimer1 = new QTimer(this);
        untargetTimer2 = new QTimer(this);
        animationTimer->start(animationSpeed);

        gameTimer.start();
        loaded = true;
    }
    } catch(std::exception const&e) {
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        error = true;
    };

}

Game::~Game()
{
    delete ui;
}

void Game::paintEvent(QPaintEvent *event) {
    if (error) {
        Widget* widget = new Widget();
        widget->show();
        this->close();
    };
    if (loaded) {
        QPainter canv(this);
        canv.setViewport(0, 0, canv.viewport().width()*viewSize, canv.viewport().height()*viewSize);
        canv.fillRect(QRect(0, 0, canv.device()->width(), canv.device()->height()), QColor(44, 47, 51));

        map = level.getMap();
        for (int i = 0; i < level.getWidth(); i++) {
            for (int j = 0; j < level.getHeight(); j++) {
                if (map[i][j] == 1) {
                    canv.drawPixmap(spriteSize*i, spriteSize*j, *spriteMap, 6*spriteSize, 1*spriteSize, spriteSize, spriteSize);
                } else if (map[i][j] == 2) {
                    canv.drawPixmap(spriteSize*i, spriteSize*j, *spriteMap, 6*spriteSize, 0, spriteSize, spriteSize);
                } else if (map[i][j] == 3) {
                    canv.drawPixmap(spriteSize*i, spriteSize*j, *spriteMap, 7*spriteSize, 0, spriteSize, spriteSize);
                }

            }
        }
        if (!level.p1.targetable) {
            canv.setOpacity(0.5);
        }
        canv.drawPixmap(spriteSize*level.p1.getX()+level.p1.movePhase*level.p1.getH(), spriteSize*level.p1.getY()+level.p1.movePhase*level.p1.getV(), *spriteMap, (frame/10)*spriteSize, level.p1.getAnimDir()*spriteSize, spriteSize, spriteSize);
        canv.setOpacity(1);
        if (!level.p2.targetable) {
            canv.setOpacity(0.5);
        }
        if (level.p2enabled) {
            canv.drawPixmap(spriteSize*level.p2.getX()+level.p2.movePhase*level.p2.getH(), spriteSize*level.p2.getY()+level.p2.movePhase*level.p2.getV(), *spriteMap, (3+frame/10)*spriteSize, level.p2.getAnimDir()*spriteSize, spriteSize, spriteSize);
        }
        canv.setOpacity(1);

        for (int x = 0; x < level.enemiesCount; x++) {
            Enemy enemy = level.enemies[x];
            canv.drawPixmap(spriteSize*enemy.getX()+enemy.movePhase*enemy.getH(), spriteSize*enemy.getY()+enemy.movePhase*enemy.getV(), *spriteMap, (enemy.color*2+frame/15)*spriteSize, (4+enemy.getAnimDir())*spriteSize, spriteSize, spriteSize);
        }

        canv.setPen(Qt::white);
        canv.setFont(QFont("Press Start 2P", 5));
        canv.drawText(10, 10, QString("Pl1 [" + level.p1name + "]: ") + QString::number(level.p1Score) + " lives: " + QString::number(level.p1.lives));
        canv.drawText(canv.device()->width()/2/viewSize-15, 10, QString::number(gameTimer.elapsed()/1000.0));
        if (level.p2enabled) {
            canv.drawText(canv.device()->width()/2/viewSize, 20, QString::number(level.score));
            canv.drawText(canv.device()->width()/viewSize-230, 10, QString("Pl2 [" + level.p2name + "]: ") + QString::number(level.p2Score) + " lives: " + QString::number(level.p2.lives));
        }
        canv.end();
    }
}

void Game::endGame() {
    if (!QDir(QCoreApplication::applicationDirPath() + "/records").exists()) {
        QDir().mkdir(QCoreApplication::applicationDirPath() + "/records");
    }

    if (level.p2enabled) {
        if (level.p1.lives > 0 && level.p2.lives > 0) {
            title->setText("WIN");
            QSound::play(":/music/win.wav");
        } else {
            title->setText("LOSE");
            QSound::play(":/music/lose.wav");
        }
        stats->setText("Pl1 Score: " + QString::number(level.p1Score) + " Pl2 Score: " + QString::number(level.p2Score) + " Time: " + QString::number(gameTimer.elapsed()/1000.0));

        QString endPath = QCoreApplication::applicationDirPath() + "/records/records2players.txt";
        QFile file(endPath);
        file.open(QIODevice::ReadWrite | QIODevice::Append);
        QTextStream out(&file);
        out << QString(level.mapName + "|" + QString::number(difficulty) + "|" + QString::number(level.maxLives) + "|" + level.p1name + "|" + level.p2name + "|" + QString::number(level.p1Score) + "|" + QString::number(level.p2Score) + "|" + QString::number(gameTimer.elapsed()/1000.0) + '\n');
        file.close();
    } else {
        if (level.p1.lives > 0) {
            title->setText("WIN");
            QSound::play(":/music/win.wav");
        } else {
            title->setText("LOSE");
            QSound::play(":/music/lose.wav");
        }
        stats->setText("Score: " + QString::number(level.p1Score) + " Time: " + QString::number(gameTimer.elapsed()/1000.0));

        QString endPath = QCoreApplication::applicationDirPath() + "/records/records1player.txt";
        QFile file(endPath);
        file.open(QIODevice::ReadWrite | QIODevice::Append);
        QTextStream out(&file);
        out << QString(level.mapName + "|" + QString::number(difficulty) + "|" + QString::number(level.maxLives) + "|" + level.p1name + "|" + QString::number(level.p1Score) + "|" + QString::number(gameTimer.elapsed()/1000.0) + '\n');
        file.close();
    }
    this->setStyleSheet("background-color: black;");
    endScreen->setVisible(true);
}

void Game::nextFrame() {
    frame++;
    for (int x = 0; x < level.enemiesCount; x++) {
        if (level.enemies[x].getH() != 0 || level.enemies[x].getV() != 0) {
            level.enemies[x].movePhase += level.enemies[x].speed;
            if (level.enemies[x].movePhase >= spriteSize/2) {
                level.enemies[x].movePhase = -level.enemies[x].movePhase;
                level.enemies[x].move(level.getHeight(), level.getWidth());
            }
        }
        if (abs(level.enemies[x].movePhase) <= 0.1) {
            level.enemies[x].movePhase = 0;
            level.enemies[x].setDir(level.getNavMap()[level.enemies[x].getX()][level.enemies[x].getY()].dir);
        }


    }
    if (level.p1.getH() != 0 || level.p1.getV() != 0) {
        level.p1.movePhase += level.p1.speed;
        if (level.p1.movePhase >= spriteSize/2) {
            level.p1.movePhase = -level.p1.movePhase;
            level.p1.move(level.getHeight(), level.getWidth());
            level.recreateNavMap();
        }
        if (level.p1.getX() > 0 && level.p1.getX() < level.getWidth()-1 && level.p1.getY() > 0 && level.p1.getY() < level.getHeight()-1 && map[level.p1.getX()+level.p1.getH()][level.p1.getY()+level.p1.getV()] == 1 && level.p1.movePhase == 0) {
            level.p1.setDir(0, 0);
        }
        if (map[level.p1.getX()+level.p1.getMH()][level.p1.getY()+level.p1.getMV()] != 1 && level.p1.movePhase == 0 && (level.p1.getMH() != 0 || level.p1.getMV() != 0)) {
            level.p1.setDir(level.p1.getMH(), level.p1.getMV());
        }
        if (map[level.p1.getX()][level.p1.getY()] == 2) {
            level.getMap()[level.p1.getX()][level.p1.getY()] = 0;
            level.p1Score += 10;
            level.score += 10;
            level.coinsCount--;

        }
        if (map[level.p1.getX()][level.p1.getY()] == 3) {
            level.getMap()[level.p1.getX()][level.p1.getY()] = 0;
            level.coinsCount--;
            level.p1Score += 30;
            level.score += 30;
            level.p1.speed = 2.0;
            if (timer1->isActive()) {
                timer1->stop();
            }
            QSound::play(":/music/bonus.wav");
            connect(timer1, SIGNAL(timeout()), this, SLOT(endBonusPl1()));
            timer1->setSingleShot(true);
            timer1->setInterval(untargetTime);
            timer1->start();
        }
    }
    for (int i = 0; i < level.enemiesCount; i++) {
        if (level.p1.targetable && level.p1.getX() == level.enemies[i].getX() && level.p1.getY() == level.enemies[i].getY()) {
            QSound::play(":/music/hit.wav");
            level.p1.toSpawn();
            connect(untargetTimer1, SIGNAL(timeout()), this, SLOT(endUntargetPl1()));
            untargetTimer1->setSingleShot(true);
            untargetTimer1->setInterval(untargetTime);
            untargetTimer1->start();
            level.recreateNavMap();
        }
        if (level.p2enabled && level.p2.targetable && level.p2.getX() == level.enemies[i].getX() && level.p2.getY() == level.enemies[i].getY()) {
            QSound::play(":/music/hit.wav");
            level.p2.toSpawn();
            connect(untargetTimer2, SIGNAL(timeout()), this, SLOT(endUntargetPl2()));
            untargetTimer2->setSingleShot(true);
            untargetTimer2->setInterval(untargetTime);
            untargetTimer2->start();
            level.recreateNavMap();
        }
    }

    if (level.p2enabled && (level.p2.getH() != 0 || level.p2.getV() != 0)) {
        level.p2.movePhase += level.p2.speed;
        if (level.p2.movePhase >= spriteSize/2) {
            level.p2.movePhase = -level.p2.movePhase;
            level.p2.move(level.getHeight(), level.getWidth());
            level.recreateNavMap();
        }
        if (map[level.p2.getX()+level.p2.getH()][level.p2.getY()+level.p2.getV()] == 1 && level.p2.movePhase == 0) {
            level.p2.setDir(0, 0);
        }
        if (map[level.p2.getX()+level.p2.getMH()][level.p2.getY()+level.p2.getMV()] != 1 && level.p2.movePhase == 0 && (level.p2.getMH() != 0 || level.p2.getMV() != 0)) {
            level.p2.setDir(level.p2.getMH(), level.p2.getMV());
        }
        if (map[level.p2.getX()][level.p2.getY()] == 2) {
            level.getMap()[level.p2.getX()][level.p2.getY()] = 0;
            level.coinsCount--;
            level.p2Score += 10;
            level.score += 10;
        }
        if (map[level.p2.getX()][level.p2.getY()] == 3) {
            level.getMap()[level.p2.getX()][level.p2.getY()] = 0;
            level.coinsCount--;
            level.p2Score += 30;
            level.score += 30;
            level.p2.speed = 2.0;
            if (timer2->isActive()) {
                timer2->stop();
            }
            QSound::play(":/music/bonus.wav");
            connect(timer2, SIGNAL(timeout()), this, SLOT(endBonusPl2()));
            timer2->setSingleShot(true);
            timer2->setInterval(bonusTime);
            timer2->start();
        }
    }

    if (loaded && (level.coinsCount <= 0 || level.p1.lives == 0 || level.p2.lives == 0)) {
        loaded = false;
        animationTimer->stop();
        endGame();
    }
    frame = frame%30;
    repaint();
}

void Game::endBonusPl1() {
    level.p1.speed = 1.0;
}

void Game::endBonusPl2() {
    level.p2.speed = 1.0;
}

void Game::endUntargetPl1() {
    level.p1.targetable = true;
    level.recreateNavMap();
}

void Game::endUntargetPl2() {
    level.p2.targetable = true;
    level.recreateNavMap();
}

void Game::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    if (key == Qt::Key_Escape) {
        loaded = false;
        Widget* widget = new Widget();
        widget->show();
        this->close();
    }
    if (key == p1leftkey && (level.p1.getH() == 0 ||level.p1.getH() == 1)) {
        if (level.p1.getX() > 0 && (map[level.p1.getX()-1][level.p1.getY()] == 1 || (level.p1.movePhase != 0 && level.p1.getH() != 1))) {
            level.p1.setMDir(-1, 0);
        } else {
            level.p1.setDir(-1, 0);
            level.p1.setMDir(0, 0);
            level.p1.movePhase = -level.p1.movePhase;
        }
    }
    else if (key == p1downkey && (level.p1.getV() == 0 ||level.p1.getV() == -1)) {
        if (level.p1.getY() < level.getHeight()-1 && (map[level.p1.getX()][level.p1.getY()+1] == 1 || (level.p1.movePhase != 0 && level.p1.getV() != -1))) {
            level.p1.setMDir(0, 1);
        } else {
            level.p1.setDir(0, 1);
            level.p1.setMDir(0, 0);
            level.p1.movePhase = -level.p1.movePhase;
        }
    }
    else if (key == p1rightkey && (level.p1.getH() == 0 ||level.p1.getH() == -1)) {
        if (level.p1.getX() < level.getWidth()-1 && (map[level.p1.getX()+1][level.p1.getY()] == 1 || (level.p1.movePhase != 0 && level.p1.getH() != -1))) {
            level.p1.setMDir(1, 0);
        } else {
            level.p1.setDir(1, 0);
            level.p1.setMDir(0, 0);
            level.p1.movePhase = -level.p1.movePhase;
        }
    }
    else if (key == p1upkey && (level.p1.getV() == 0 ||level.p1.getV() == 1)) {
        if (level.p1.getY() > 0 && (map[level.p1.getX()][level.p1.getY()-1] == 1 || (level.p1.movePhase != 0 && level.p1.getV() != 1))) {
            level.p1.setMDir(0, -1);
        } else {
            level.p1.setDir(0, -1);
            level.p1.setMDir(0, 0);
            level.p1.movePhase = -level.p1.movePhase;
        }
    }
    else if (key == p2leftkey && level.p2enabled && (level.p2.getH() == 0 ||level.p2.getH() == 1)) {
        if (level.p2.getX() > 0 && (map[level.p2.getX()-1][level.p2.getY()] == 1 || (level.p2.movePhase != 0 && level.p2.getH() != 1))) {
            level.p2.setMDir(-1, 0);
        } else {
            level.p2.setDir(-1, 0);
            level.p2.setMDir(0, 0);
            level.p2.movePhase = -level.p2.movePhase;
        }
    }
    else if (key == p2downkey && level.p2enabled && (level.p2.getV() == 0 ||level.p2.getV() == -1)) {
        if (level.p2.getY() < level.getHeight()-1 && (map[level.p2.getX()][level.p2.getY()+1] == 1 || (level.p2.movePhase != 0 && level.p2.getV() != -1))) {
            level.p2.setMDir(0, 1);
        } else {
            level.p2.setDir(0, 1);
            level.p2.setMDir(0, 0);
            level.p2.movePhase = -level.p2.movePhase;
        }
    }
    else if (key == p2rightkey && level.p2enabled && (level.p2.getH() == 0 ||level.p2.getH() == -1)) {
        if (level.p2.getX() < level.getWidth()-1 && (map[level.p2.getX()+1][level.p2.getY()] == 1 || (level.p2.movePhase != 0 && level.p2.getH() != -1))) {
            level.p2.setMDir(1, 0);
        } else {
            level.p2.setDir(1, 0);
            level.p2.setMDir(0, 0);
            level.p2.movePhase = -level.p2.movePhase;
        }
    }
    else if (key == p2upkey && level.p2enabled && (level.p2.getV() == 0 ||level.p2.getV() == 1)) {
        if (level.p2.getY() > 0 && (map[level.p2.getX()][level.p2.getY()-1] == 1 || (level.p2.movePhase != 0 && level.p2.getV() != 1))) {
            level.p2.setMDir(0, -1);
        } else {
            level.p2.setDir(0, -1);
            level.p2.setMDir(0, 0);
            level.p2.movePhase = -level.p2.movePhase;
        }
    }
}


void Game::on_againButton_clicked() {
    QSound::play(":/music/ok.wav");
    Game* game = new Game();
    game->show();
    this->close();
}


void Game::on_recordsButton_clicked()
{
    QSound::play(":/music/ok.wav");
    Records* records = new Records();
    records->show();
    this->close();
}


void Game::on_menuButton_clicked()
{
    QSound::play(":/music/close.wav");
    Widget* widget = new Widget();
    widget->show();
    this->close();
}

